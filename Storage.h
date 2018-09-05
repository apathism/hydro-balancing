#ifndef __HYDRO_STORAGE__
#define __HYDRO_STORAGE__

#include <QVector>
#include <QTableWidget>

class Storage
{
	Storage();
public:
	static bool Load(const QString&);
	static bool Load(const QTableWidget&);
	static bool Save(const QString&);
	static bool SaveLogs(const QString&);
	static void Clear();

	static int& precision();
	static int& digits();
	static const QVector<double>& specs();
	static const QVector<double>& stable();
	static QVector< QVector<QString> >& logs();
};

#endif
