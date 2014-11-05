#pragma once

#include <QtWidgets/QTableWidget>
#include <QtCore/QMap>

/// Widget for showing data from scalar sensors.
class SensorsList : public QTableWidget
{
	Q_OBJECT
public:
	explicit SensorsList(QWidget *parent = 0);

	void configurePorts(QStringList const &ports);

	void setNormalized(QString const &port, int value);
	void setRaw(QString const &port, int value);

private:
	QMap<QString, int> mPortRowMap;
};
