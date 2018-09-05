#ifndef __HYDRO_PAGESPECIFICATIONFILE__
#define __HYDRO_PAGESPECIFICATIONFILE__

#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PageSpecificationFile: public QWizardPage
{
	Q_OBJECT
public:
	PageSpecificationFile(QWidget *parent = 0);
	int nextId() const;
	bool isComplete() const;
private:
	QLabel *topLabel;
	QLineEdit *filename;
	QPushButton *button;
	QLabel *status;
	bool complete;

private slots:
	void ChoosePressed();
};

#endif
