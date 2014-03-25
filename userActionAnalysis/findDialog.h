#pragma once

#include <QDialog>

#include "userAction/baseUserAction/baseUserAction.h"

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
	Q_OBJECT

public:
	explicit FindDialog(QWidget *parent = 0);
	~FindDialog();
	void open(BaseUserAction *action);

signals:
	void actionToFind(QString const &action);

private slots:
	void sendCustomAction();

private:
	Ui::FindDialog *ui;
	BaseUserAction *mAction;
};
