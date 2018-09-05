#include "Wizard.h"
#include "PageIntro.h"
#include <QVBoxLayout>

PageIntro::PageIntro(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Introduction"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.png"));

	topLabel = new QLabel(tr("This wizard will help you in weight load balancing of "
		"hydroelectric unit. Please follow the wizard instructions."));
	topLabel->setWordWrap(true);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(topLabel);
	setLayout(layout);
}

int PageIntro::nextId() const
{
	return Wizard::Page_Specification;
}
