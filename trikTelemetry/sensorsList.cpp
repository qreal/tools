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
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

void SensorsList::configurePorts(QStringList const &ports)
{
	setRowCount(ports.length());
	for (int row = 0; row < ports.length(); ++row) {
		setRowHeight(row, 20);
		mPortRowMap[ports.at(row)] = row;

		setItem(row, 0, new QTableWidgetItem(ports.at(row)));
		setItem(row, 1, new QTableWidgetItem(tr("N/A")));
		setItem(row, 2, new QTableWidgetItem(tr("N/A")));
	}
}

void SensorsList::setNormalized(QString const &port, int value)
{
	item(mPortRowMap[port], 1)->setText(QString::number(value));
}

void SensorsList::setRaw(QString const &port, int value)
{
	item(mPortRowMap[port], 2)->setText(QString::number(value));
}
