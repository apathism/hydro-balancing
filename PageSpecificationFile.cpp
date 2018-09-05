#include "Wizard.h"
#include "PageSpecificationFile.h"
#include "Storage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

PageSpecificationFile::PageSpecificationFile(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("File Selection"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.jpg"));

	topLabel = new QLabel(tr("Select file with the specification data you need."));
	topLabel->setWordWrap(true);

	filename = new QLineEdit();
	filename->setEnabled(false);
	button = new QPushButton(tr("Bro&wse"));
	status = new QLabel();
	status->setPixmap(QPixmap(":/pics/bad.png"));

	QVBoxLayout *vlayout = new QVBoxLayout();
	QHBoxLayout *hlayout = new QHBoxLayout();
	hlayout->addWidget(filename);
	hlayout->addWidget(button);
	hlayout->addWidget(status);
	vlayout->addWidget(topLabel);
	vlayout->addLayout(hlayout);
	setLayout(vlayout);

	connect(button, SIGNAL(clicked()), this, SLOT(ChoosePressed()));
	complete = false;
}

int PageSpecificationFile::nextId() const
{
	return Wizard::Page_Precision;
}

void PageSpecificationFile::ChoosePressed()
{
	QString ftemp = QFileDialog::getOpenFileName(this,
		tr("Open Specification File"), QString(),
		tr("Specification Files (*.spec);;All Files (*.*)"));
	if (ftemp == "") return;
	if (!Storage::Load(ftemp))
	{
		QMessageBox::warning(this, tr("Opening Specification File"),
			tr("Unable to open specified file due to invalid format"));
		filename->setText(ftemp);
		Storage::Clear();
		status->setPixmap(QPixmap(":/pics/bad.png"));
		complete = false;
		completeChanged();
		return;
	}
	status->setPixmap(QPixmap(":/pics/good.png"));
	complete = true;
	completeChanged();
	filename->setText(ftemp);
}

bool PageSpecificationFile::isComplete() const
{
	return complete;
}
