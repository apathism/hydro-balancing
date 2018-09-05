#ifndef __HYDRO_PAGESPECIFICATIONDATA__
#define __HYDRO_PAGESPECIFICATIONDATA__

#include <QWizardPage>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

class PageSpecificationData: public QWizardPage
{
	Q_OBJECT
public:
	PageSpecificationData(QWidget* = 0);
	int nextId() const;
	bool isComplete() const;
private:
	QLabel *topLabel;
	QTableWidget *table;
	QPushButton *add;
	QPushButton *remove;
	QPushButton *save;

	void stateChanged();
private slots:
	void addColumn();
	void removeColumn();
	void saveData();
	void cellChanged(int, int);
};

#endif
