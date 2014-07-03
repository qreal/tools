#include "widget.h"
#include "ui_widget.h"

#include "preferencesDialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    PreferencesDialog * dialog = new PreferencesDialog();
    dialog->init(nullptr, nullptr, nullptr, nullptr);
    ui->widgetSettings->layout()->addWidget(dialog);
    dialog->setParent(ui->widgetSettings);
//    ui->widgetSettings = dialog;
//    dialog->show();
}
