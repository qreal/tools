#pragma once

#include <QtCore/QTimer>
#include <QtWidgets/QMainWindow>

#include "communicator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QHostAddress const &server, int updateInterval, QWidget *parent = 0);
	~MainWindow();

public slots:
	void updateValues();
	void setValues(QString const &values);

private:
	Ui::MainWindow *ui;

	Communicator mCommunicator;
	QTimer mUpdateTimer;
};
