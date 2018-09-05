#ifndef __HYDRO_PAGESPECIFICATION__
#define __HYDRO_PAGESPECIFICATION__

#include <QWizardPage>
#include <QLabel>
#include <QRadioButton>

class PageSpecification: public QWizardPage
{
	Q_OBJECT
public:
	PageSpecification(QWidget *parent = 0);
	int nextId() const;
private:
	QLabel *topLabel;
	QRadioButton *specManually;
	QRadioButton *specFile;
};

#endif
