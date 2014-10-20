#pragma once

#include <QtWidgets/QTableWidget>

class Sensors3DList : public QTableWidget
{
	Q_OBJECT
public:
	explicit Sensors3DList(QWidget *parent = 0);

	void setValues(QString const &sensor, QVector<int> const &values);
};
