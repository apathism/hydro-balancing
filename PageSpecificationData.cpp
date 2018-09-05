#include "Wizard.h"
#include "PageSpecificationData.h"
#include "Storage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

PageSpecificationData::PageSpecificationData(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Specification Data: Manual Input"));

	topLabel = new QLabel(tr("On this step you should input specification data "
		"for each record."));
	topLabel->setWordWrap(true);

	table = new QTableWidget(3, 1);
	table->setVerticalHeaderLabels(QStringList()
		<< tr("Deflection")
		<< tr("Load")
		<< tr("Stable"));
	table->setSelectionMode(QAbstractItemView::NoSelection);

	add = new QPushButton(QPixmap(":/pics/add.png"), tr("&Add"));
	remove = new QPushButton(QPixmap(":/pics/remove.png"), tr("&Remove"));
	save = new QPushButton(QPixmap(":/pics/save.png"), tr("&Save"));
	save->setEnabled(false);

	connect(add, SIGNAL(pressed()), this, SLOT(addColumn()));
	connect(remove, SIGNAL(pressed()), this, SLOT(removeColumn()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveData()));
	connect(table, SIGNAL(cellChanged(int, int)), this,
		SLOT(cellChanged(int, int)));

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(add);
	hlayout->addWidget(remove);
	hlayout->addWidget(save);

	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(topLabel);
	vlayout->addWidget(table);
	vlayout->addLayout(hlayout);
	setLayout(vlayout);

	table->resizeColumnsToContents();
}

int PageSpecificationData::nextId() const
{
	return Wizard::Page_Precision;
}

void PageSpecificationData::addColumn()
{
	table->insertColumn(table->columnCount());
	table->resizeColumnsToContents();
	stateChanged();
}

void PageSpecificationData::removeColumn()
{
	if (table->currentColumn() == -1) return;
	table->removeColumn(table->currentColumn());
	table->resizeColumnsToContents();
	stateChanged();
}

bool PageSpecificationData::isComplete() const
{
	return Storage::Load(*table);
}

void PageSpecificationData::cellChanged(int, int)
{
	table->resizeColumnsToContents();
	stateChanged();
}

void PageSpecificationData::saveData()
{
	QString ftemp = QFileDialog::getSaveFileName(this,
		tr("Save Specification file"), QString(),
		tr("Specification files (*.spec);;All Files (*.*)"));
	if (ftemp == "") return;
	if (!Storage::Save(ftemp))
	{
		QMessageBox::warning(this, tr("Saving Specification Data"),
			tr("Unable to save specification data file"));
	}
}

void PageSpecificationData::stateChanged()
{
	save->setEnabled(Storage::Load(*table));
	completeChanged();
}
