#include "Storage.h"
#include "Wizard.h"
#include "PagePrecision.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

PagePrecision::PagePrecision(QWidget *parent): QWizardPage(parent)
{
	setTitle(tr("Calculations Precision"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/pics/logo.jpg"));

	topLabel = new QLabel(tr("Please, set up the precision of calculations you need. You "
		"should determine two integers: number of significant digits after the decimal "
		"point and the critical difference between real and average load (in percents)."));
	topLabel->setWordWrap(true);

	digitsLabel = new QLabel(tr("Number of digits:"));
	digits = new QSpinBox();
	digits->setMinimum(0);
	digits->setMaximum(7);
	digits->setValue(2);

	precisionLabel = new QLabel(tr("Critical difference (in %):"));
	precision = new QSpinBox();
	precision->setMinimum(0);
	precision->setMaximum(100);
	precision->setValue(5);
	UpdateStorage();
	connect(digits, SIGNAL(valueChanged(int)),
		this, SLOT(UpdateStorage()));
	connect(precision, SIGNAL(valueChanged(int)),
		this, SLOT(UpdateStorage()));

	QHBoxLayout *hlayout1 = new QHBoxLayout;
	hlayout1->addWidget(digitsLabel);
	hlayout1->addWidget(digits);

	QHBoxLayout *hlayout2 = new QHBoxLayout;
	hlayout2->addWidget(precisionLabel);
	hlayout2->addWidget(precision);

	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->addWidget(topLabel);
	vlayout->addLayout(hlayout1);
	vlayout->addLayout(hlayout2);
	setLayout(vlayout);
}

int PagePrecision::nextId() const
{
	return Wizard::Page_Iteration_Info;
}

void PagePrecision::UpdateStorage()
{
	Storage::precision() = precision->value();
	Storage::digits() = digits->value();
}
