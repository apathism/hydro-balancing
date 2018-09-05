#include "Wizard.h"
#include "PageIntro.h"
#include "PageSpecification.h"
#include "PageSpecificationFile.h"
#include "PageSpecificationData.h"
#include "PagePrecision.h"
#include "PageIterationInfo.h"
#include "PageIteration.h"
#include "PageFinal.h"

Wizard::Wizard(QWidget *parent): QWizard(parent)
{
	setPage(Page_Intro, new PageIntro);
	setPage(Page_Specification, new PageSpecification);
	setPage(Page_Specification_File, new PageSpecificationFile);
	setPage(Page_Specification_Data, new PageSpecificationData);
	setPage(Page_Precision, new PagePrecision);
	setPage(Page_Iteration_Info, new PageIterationInfo);
	setPage(Page_Iteration, new PageIteration);
	setPage(Page_Final, new PageFinal);
	setStartId(Page_Intro);
	setButtonText(QWizard::CancelButton, tr("Exit"));
	setWizardStyle(ClassicStyle);
	setOption(QWizard::DisabledBackButtonOnLastPage);
	setWindowTitle(tr("Calculation of load balancing"));
}
