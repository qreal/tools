#include "sensors3dList.h"

#include <QtWidgets/QHeaderView>

Sensors3DList::Sensors3DList(QWidget *parent) :
	QTableWidget(parent)
{
	setColumnCount(4);
	setColumnWidth(1, 50);
	setColumnWidth(2, 50);
	setColumnWidth(3, 50);

	setRowCount(2);
	setRowHeight(0, 20);
	setRowHeight(1, 20);

	setHorizontalHeaderLabels(QStringList({ tr("Port"), tr("X"), tr("Y"), tr("Z") }));
	horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	verticalHeader()->setVisible(false);

	for (int row = 0; row < 2; ++row) {
		for (int column = 1; column < 4; ++column) {
			setItem(row, column, new QTableWidgetItem(tr("N/A")));
		}
	}

	setItem(0, 0, new QTableWidgetItem(tr("Accelerometer")));
	setItem(1, 0, new QTableWidgetItem(tr("Gyroscope")));
}

void Sensors3DList::setValues(QString const &sensor, QVector<int> const &values)
{
	int row = sensor == "accelerometer" ? 0 : 1;
	for (int i = 0; i < 3; ++i) {
		item(row, i + 1)->setText(QString::number(values[i]));
	}
}
