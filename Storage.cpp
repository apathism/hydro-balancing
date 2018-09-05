#include "Storage.h"
#include <QFile>
#include <QTextStream>

static const int maxsize = 32;
static QVector<double> Specs;
static QVector<double> Stable;
static QVector< QVector<QString> > Logs;
static int Precision;
static int Digits;

typedef unsigned int uint;

bool Storage::Load(const QString &filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		return false;
	int size;
	if (file.read((char*)&size, sizeof(size)) < (uint)sizeof(size))
		return false;
	if (size <= 0 || size > maxsize)
		return false;
	double* buffer = new double[size * 2];
	if (file.read((char*) buffer, sizeof(double)*size*2) < (uint)sizeof(double)*size*2)
	{
		delete[] buffer;
		return false;
	}
	file.close();
	Clear();
	for (int i=0; i<size; ++i)
		Specs.push_back(buffer[i]);
	for (int i=size; i<2*size; ++i)
		Stable.push_back(buffer[i]);
	delete[] buffer;
	return true;
}

#define PUSHTO(x,y,t) { *((t*)(x))=y; x+=sizeof(t); }

bool Storage::Save(const QString &filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		return false;
	int size = sizeof(double) * Specs.size() + sizeof(double) * Stable.size()
		+ sizeof(int);
	char* buffer = new char[size];
	char* temp = buffer;
	PUSHTO(temp, Specs.size(), int);
	for (int i=0; i<Specs.size(); ++i)
		PUSHTO(temp, Specs[i], double);
	for (int i=0; i<Stable.size(); ++i)
		PUSHTO(temp, Stable[i], double);
	if (file.write(buffer, size) < size)
	{
		delete[] buffer;
		return false;
	}
	delete[] buffer;
	file.close();
	return true;
}

void Storage::Clear()
{
	Specs.clear();
	Stable.clear();
	Logs.clear();
}

bool Storage::Load(const QTableWidget &widget)
{
	const double eps = 0.005;
	if (widget.columnCount() < 1 || widget.columnCount() > maxsize)
		return false;
	for (int i=0; i < widget.columnCount(); ++i)
		for (int j=0; j < widget.rowCount(); ++j)
		{
			QTableWidgetItem *item = widget.item(j, i);
			if (!item) return false;
			bool success;
			double value = item->text().toDouble(&success);
			if (!success) return false;
			if (value < eps && j != 2)
				return false;
		}
	Clear();
	for (int i=0; i < widget.columnCount(); ++i)
	{
		double deflection = widget.item(0, i)->text().toDouble(0);
		double load = widget.item(1, i)->text().toDouble(0);
		double stable = widget.item(2, i)->text().toDouble(0);
		Specs.push_back((load - stable) / deflection);
		Stable.push_back(stable);
	}
	return true;
}

int& Storage::precision()
{
	return Precision;
}

int& Storage::digits()
{
	return Digits;
}

const QVector<double>& Storage::specs()
{
	return Specs;
}

QVector< QVector<QString> >& Storage::logs()
{
	return Logs;
}

const QVector<double>& Storage::stable()
{
	return Stable;
}

bool Storage::SaveLogs(const QString &filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;
	QTextStream out(&file);
	out <<
		QObject::tr("Step") << '\t' <<
		QObject::tr("Option") << '\t';
	for (int i=1; i<=Specs.size(); ++i)
		out << QString::number(i) << '\t';
	out <<
		QObject::tr("Average") << '\t' <<
		QObject::tr("Difference") << '\t';
	out << endl;
	for (int i=0; i<Logs.size(); ++i)
	{
		out << i/4 + 1 << '\t';
		switch (i % 4)
		{
			case 0:
				out << QObject::tr("Deflection") << '\t';
				break;
			case 1:
				out << QObject::tr("Load") << '\t';
				break;
			case 2:
				out << QObject::tr("Balance") << '\t';
				break;
			case 3:
				out << QObject::tr("Reaction") << '\t';
				break;
			default:
				out << QObject::tr("NaN") << '\t';
		}
		for (int j=0; j<Logs[i].size(); ++j)
			out << Logs[i][j] << '\t';
		out << endl;
	}
	out << flush;
	file.close();
	return true;
}
