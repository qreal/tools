#pragma once

#include <QtWidgets/QTableWidget>
#include <QtCore/QMap>

class SensorsList : public QTableWidget
{
	Q_OBJECT
public:
	explicit SensorsList(QWidget *parent = 0);

	void addPort(QString const &name);
	void setNormalized(QString const &port, int value);
	void setRaw(QString const &port, int value);

signals:

private:
	QMap<QString, int> mPortRowMap;
};
