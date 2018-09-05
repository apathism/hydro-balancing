#include <QApplication>
#include <QLocale>
#include <QLibraryInfo>
#include <QTranslator>
#include "Wizard.h"

int main(int argc, char* argv[])
{
	QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));
	QApplication app(argc, argv);
	QTranslator t1, t2;
	t1.load("qt_" + QLocale::system().name(),
		QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	t2.load("hydro_" + QLocale::system().name());
	app.installTranslator(&t1);
	app.installTranslator(&t2);
	Wizard wizard;
	wizard.show();
	return app.exec();
}
