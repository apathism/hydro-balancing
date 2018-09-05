#ifndef __HYDRO_PAGEITERATION__
#define __HYDRO_PAGEITERATION__

#include <QWizardPage>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

class PageIteration: public QWizardPage
{
	Q_OBJECT
public:
	PageIteration(QWidget *parent = 0);
	void initializePage();
	int nextId() const;
	bool isComplete() const;
private:
	QTableWidget *table;
	QPushButton *button;
	bool iteration;
	bool complete;

	bool getButtonState() const;
	int PercentDiff(double, double) const;
	QString PercentDiffStr(double, double) const;
private slots:
	void refreshButtonState();
	void newIteration();
	void buttonPressed();
};

#endif
