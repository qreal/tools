#pragma once
#include "server/server.h"

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void init();

private slots:
	void addNewClient(QString newClient);

private:
    Ui::Widget *ui;
	Server *server;
};

