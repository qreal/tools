#include "sensorsList.h"

#include <QtWidgets/QHeaderView>

SensorsList::SensorsList(QWidget *parent) :
	QTableWidget(parent)
{
	setColumnCount(3);
	setColumnWidth(1, 80);
	setColumnWidth(2, 80);

	setHorizontalHeaderLabels(QStringList({ tr("Port"), tr("Normalized"), tr("Raw") }));
	verticalHeader()->setVisible(false);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void SensorsList::addPort(QString const &name)
{
	int rowNumber = rowCount();
	insertRow(rowNumber);
	setRowHeight(rowNumber, 20);
	mPortRowMap[name] = rowNumber;

	setItem(rowNumber, 0, new QTableWidgetItem(name));
	setItem(rowNumber, 1, new QTableWidgetItem("N/A"));
	setItem(rowNumber, 2, new QTableWidgetItem("N/A"));
}

void SensorsList::setNormalized(QString const &port, int value)
{
	item(mPortRowMap[port], 1)->setText(QString::number(value));
}

void SensorsList::setRaw(QString const &port, int value)
{
	item(mPortRowMap[port], 2)->setText(QString::number(value));
}
