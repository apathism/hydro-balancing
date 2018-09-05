#include "Wizard.h"
#include "PageIteration.h"
#include "Storage.h"
#include <QVBoxLayout>
#include <QtCore>

PageIteration::PageIteration(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Iterational balancing"));

	table = new QTableWidget;
	table->setSelectionMode(QAbstractItemView::NoSelection);
	button = new QPushButton;

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(table);
	layout->addWidget(button);
	setLayout(layout);
	connect(table, SIGNAL(cellChanged(int, int)),
		this, SLOT(refreshButtonState()));
	connect(button, SIGNAL(pressed()),
		this, SLOT(buttonPressed()));
}

void PageIteration::initializePage()
{
	Storage::logs().clear();
	newIteration();
}

void PageIteration::newIteration()
{
	complete = false;
	iteration = false;
	button->setText(tr("&Evaluate"));
	button->setEnabled(false);
	button->setIcon(QPixmap(":/pics/table-next.png"));
	table->clear();
	table->setColumnCount(Storage::specs().size());
	table->setRowCount(1);
	table->setVerticalHeaderLabels(QStringList() << tr("Deflection"));
	table->resizeColumnsToContents();
	completeChanged();
}

int PageIteration::nextId() const
{
	return Wizard::Page_Final;
}

bool PageIteration::isComplete() const
{
	return complete;
}

void PageIteration::refreshButtonState()
{
	table->resizeColumnsToContents();
	button->setEnabled(getButtonState());
}

bool PageIteration::getButtonState() const
{
	if (iteration)
		return true;
	for (int i=0; i < table->columnCount(); ++i)
	{
		QTableWidgetItem *item = table->item(0, i);
		if (!item) return false;
		bool success;
		item->text().toDouble(&success);
		if (!success)
			return false;
	}
	return true;
}

void PageIteration::buttonPressed()
{
	if (iteration)
	{
		QVector<QString> temp;
		for (int i=0; i < table->columnCount(); ++i)
			temp.push_back(table->item(4, i)->text());
		Storage::logs().push_back(temp);
		newIteration();
		return;
	}
	iteration = 1;
	table->setRowCount(6);
	table->setColumnCount(table->columnCount() + 2);
	table->setVerticalHeaderLabels(QStringList()
		<< tr("Deflection")
		<< tr("Load")
		<< tr("Balance")
		<< tr("Difference")
		<< tr("Reaction")
		<< tr("Status"));
	for (int i=0; i < table->columnCount(); ++i)
		for (int j=0; j < table->rowCount(); ++j)
		{
			if (!table->item(j, i)) table->setItem(j, i, new QTableWidgetItem);
			table->item(j, i)->setTextAlignment(Qt::AlignCenter);
			if (j == 4 && i < Storage::specs().size()) continue;
			table->item(j, i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
	QVector<double> load;
	double avg_load = 0;
	double min_load = INFINITY;
	double max_load = -INFINITY;
	for (int i=0; i<Storage::specs().size(); ++i)
	{
		double value = table->item(0, i)->text().toDouble(0) *
			Storage::specs()[i] + Storage::stable()[i];
		avg_load += value;
		if (value < min_load) min_load = value;
		if (value > max_load) max_load = value;
		load.push_back(value);
		table->item(1, i)->setText(QString::number(value, 'f', Storage::digits()));
	}
	avg_load /= Storage::specs().size();
	table->item(1, Storage::specs().size())->setText(
		QString::number(avg_load, 'f', Storage::digits()));
	table->item(1, Storage::specs().size()+1)->setText(
		PercentDiffStr(max_load, avg_load) + " / " +
		PercentDiffStr(min_load, avg_load));
	complete = true;
	for (int i=0; i<Storage::specs().size(); ++i)
	{
		double fixed = (avg_load - Storage::stable()[i]) / Storage::specs()[i];
		QString fix = QString::number(fixed - table->item(0, i)->text().toDouble(0),
			'f', Storage::digits());
		if (fix.length() && fix[0] != '-') fix = '+' + fix;
		table->item(2, i)->setText(QString::number(fixed, 'f', Storage::digits()));
		table->item(3, i)->setText(fix);
		int diff = PercentDiff(load[i], avg_load);
		if (diff <= Storage::precision() && diff != -1)
			table->item(5, i)->setIcon(QPixmap(":/pics/good.png"));
		else
		{
			table->item(5, i)->setIcon(QPixmap(":/pics/bad.png"));
			complete = false;
		}
		table->item(5, i)->setText(PercentDiffStr(load[i], avg_load));
		table->item(0, i)->setText(QString::number(table->item(0, i)->text().toDouble(0),
			'f', Storage::digits()));
	}
	for (int i=0; i < 3; ++i)
	{
		QVector<QString> temp;
		for (int j=0; j < table->columnCount(); ++j)
			temp.push_back(table->item(i, j)->text());
		Storage::logs().push_back(temp);
	}
	table->setHorizontalHeaderItem(Storage::specs().size(), new QTableWidgetItem(tr("Average")));
	table->setHorizontalHeaderItem(Storage::specs().size()+1, new QTableWidgetItem(tr("Delta")));
	button->setText(tr("&Retry"));
	button->setIcon(QPixmap(":/pics/table-new.png"));
	refreshButtonState();
	completeChanged();
}

int PageIteration::PercentDiff(double x, double y) const
{
	const double eps = 1e-6;
	if (qAbs(y) < eps)
		return (qAbs(x) < eps) ? 0 : -1;
	return qCeil(qAbs(x-y)/qAbs(y) * 100);
}

QString PageIteration::PercentDiffStr(double x, double y) const
{
	int diff = PercentDiff(x, y);
	QString result = (x < y ? "-" : "+");
	if (diff == -1)
		result += QChar(0x221E);
	else
		result += QString::number(diff);
	result += '%';
	return result;
}
