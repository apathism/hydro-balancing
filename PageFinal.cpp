#include "Wizard.h"
#include "PageFinal.h"
#include "Storage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

PageFinal::PageFinal(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Conclusion"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.png"));

	topLabel = new QLabel(tr("After the balancing you're able to save your "
		"specification data and/or the balancing logs."));
	topLabel->setWordWrap(true);

	saveLogsButton = new QPushButton(QPixmap(":/pics/table-save.png"),
		tr("Save &Logs"));

	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(topLabel);
	vlayout->addWidget(saveLogsButton);
	setLayout(vlayout);

	connect(saveLogsButton, SIGNAL(clicked()), this, SLOT(SaveLogs()));
}

int PageFinal::nextId() const
{
	return -1;
}

void PageFinal::SaveLogs()
{
	QString ftemp = QFileDialog::getSaveFileName(this,
		tr("Save Balancing Logs File"), QString(),
		tr("Text Files (*.txt);;All Files (*.*)"));
	if (ftemp == "") return;
	if (!Storage::SaveLogs(ftemp))
	{
		QMessageBox::warning(this, tr("Saving Balacing Logs"),
			tr("Unable to save balancing logs text data file"));
	}
}
