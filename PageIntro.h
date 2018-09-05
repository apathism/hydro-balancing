#ifndef __HYDRO_PAGEINTRO__
#define __HYDRO_PAGEINTRO__

#include <QWizardPage>
#include <QLabel>

class PageIntro: public QWizardPage
{
	Q_OBJECT
public:
	PageIntro(QWidget *parent = 0);
	int nextId() const;
private:
	QLabel *topLabel;
};

#endif
