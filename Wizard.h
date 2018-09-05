#ifndef __HYDRO_WIZARD__
#define __HYDRO_WIZARD__

#include <QWizard>

class Wizard: public QWizard
{
	Q_OBJECT

public:
	enum
	{
		Page_Intro,
		Page_Specification,
		Page_Specification_File,
		Page_Specification_Data,
		Page_Precision,
		Page_Iteration_Info,
		Page_Iteration,
		Page_Final
	};

	Wizard(QWidget *parent = 0);
};

#endif
