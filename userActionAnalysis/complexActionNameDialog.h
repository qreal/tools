#pragma once

#include <QDialog>

namespace Ui {
class ComplexActionNameDialog;
}

class ComplexActionNameDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ComplexActionNameDialog(QWidget *parent = 0);
	~ComplexActionNameDialog();
	void openDialog();
	void initReservedNames(QStringList const &actionNames);
	void addReservedName(QString const &actionName);
	QString const complexActionName();

public slots:
	void saveComplexActionName();

private:
	Ui::ComplexActionNameDialog *ui;
	QString mComplexActionName;
	QStringList mReservedNames;
};
