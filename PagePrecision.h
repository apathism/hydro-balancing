#ifndef __HYDRO_PAGEPRECISION__
#define __HYDRO_PAGEPRECISION__

#include <QWizardPage>
#include <QLabel>
#include <QSpinBox>

class PagePrecision: public QWizardPage
{
	Q_OBJECT
public:
	PagePrecision(QWidget *parent = 0);
	int nextId() const;
private:
	QLabel *topLabel;
	QLabel *digitsLabel;
	QLabel *precisionLabel;
	QSpinBox *digits;
	QSpinBox *precision;
private slots:
	void UpdateStorage();
};

#endif
