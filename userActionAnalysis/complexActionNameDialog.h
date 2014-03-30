#pragma once

#include "scenarioActionsStatusForm.h"

#include <QDialog>

namespace Ui {
class ComplexActionNameDialog;
}

class ComplexActionNameDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ComplexActionNameDialog(QWidget *parent = 0, QStringList const &baseActionNames = QStringList());
	~ComplexActionNameDialog();
	void openDialog(bool isScenario);
	void initReservedNames(QStringList const &actionNames);
	void addReservedName(QString const &actionName);
	QString const complexActionName();
	bool isScenario();
	QMap<QString, ActionStatus> actionStatus() const;

public slots:
	void saveComplexActionName();

private:
	Ui::ComplexActionNameDialog *ui;
	QString mComplexActionName;
	QStringList mReservedNames;
	ScenarioActionsStatusForm *mScenarioForm;
	QMap<QString, ActionStatus> mActionStatus;
	bool mIsScenario;
};
