#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QMap>
#include "constants.h"

namespace Ui {
class ScenarioActionsStatusForm;
}

class ScenarioActionsStatusForm : public QWidget
{
	Q_OBJECT
public:
	explicit ScenarioActionsStatusForm(QWidget *parent = 0, QStringList const &baseActionNames = QStringList());
	~ScenarioActionsStatusForm();

	QMap<QString, ActionStatus> saveContent();
	void clearSelection();

private:
	Ui::ScenarioActionsStatusForm *ui;
	QMap<QString, ActionStatus> mActionStatus;
	int mCount;

	void addBaseAction(QString const &baseActionName);
};
