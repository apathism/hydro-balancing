#include "Wizard.h"
#include "PageIterationInfo.h"
#include <QVBoxLayout>

PageIterationInfo::PageIterationInfo(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Balancing Tips"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.jpg"));

	topLabel = new QLabel(tr("Now it's time to apply the iterational algorithm. On a first "
		"step you should specify the variation of disks. After pressing \"Evaluate\" "
		"button you'll be able to view fixed variation. On a second step you can either "
		"run another iteration by clicking the corresponding button or finish the balancing."));
	topLabel->setWordWrap(true);

	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	setLayout(layout);
}

int PageIterationInfo::nextId() const
{
	return Wizard::Page_Iteration;
}

