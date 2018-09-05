#ifndef __HYDRO_PAGEFINAL__
#define __HYDRO_PAGEFINAL__

#include <QWizardPage>
#include <QLabel>
#include <QPushButton>

class PageFinal: public QWizardPage
{
	Q_OBJECT
public:
	PageFinal(QWidget *parent = 0);
	int nextId() const;
private:
	QLabel *topLabel;
	QPushButton *saveLogsButton;
private slots:
	void SaveLogs();
};

#endif
