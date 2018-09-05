#include "Wizard.h"
#include "PageSpecification.h"
#include <QVBoxLayout>

PageSpecification::PageSpecification(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Specification Data Source"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.jpg"));

	topLabel = new QLabel(tr("Select the source of the specification data. It can"
		" be contained in a simple text file or can be entered manually."));
	topLabel->setWordWrap(true);

	specManually = new QRadioButton(tr("Input specification data &manually"));
	specFile = new QRadioButton(tr("Use specification &file"));
	specManually->setChecked(true);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	layout->addWidget(specManually);
	layout->addWidget(specFile);
	setLayout(layout);
}

int PageSpecification::nextId() const
{
	if (specFile->isChecked())
		return Wizard::Page_Specification_File;
	return Wizard::Page_Specification_Data;
}
