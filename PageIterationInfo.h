#ifndef __HYDRO_PAGEITERATIONINFO__
#define __HYDRO_PAGEITERATIONINFO__

#include <QWizardPage>
#include <QLabel>

class PageIterationInfo: public QWizardPage
{
	Q_OBJECT
public:
	PageIterationInfo(QWidget *parent = 0);
	int nextId() const;
private:
	QLabel *topLabel;
};

#endif
