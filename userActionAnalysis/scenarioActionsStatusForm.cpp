#include "scenarioActionsStatusForm.h"
#include "ui_scenarioActionsStatusForm.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtCore/QDebug>

ScenarioActionsStatusForm::ScenarioActionsStatusForm(QWidget *parent, const QStringList &baseActionNames)
	: QWidget(parent)
	, ui(new Ui::ScenarioActionsStatusForm)
{
	ui->setupUi(this);
	mActionStatus.clear();
	mCount = 0;

	for (QString const &baseActionName: baseActionNames) {
		addBaseAction(baseActionName);
	}
}

ScenarioActionsStatusForm::~ScenarioActionsStatusForm()
{
	delete ui;
}

void ScenarioActionsStatusForm::addBaseAction(const QString &baseActionName)
{
	QLabel *baseActionLabel = new QLabel(baseActionName, this);
	QRadioButton *good = new QRadioButton(this);
	good->setObjectName("good" + QString::number(mCount));
	good->setChecked(true);
	QRadioButton *bad = new QRadioButton(this);
	good->setObjectName("bad" + QString::number(mCount));
	QRadioButton *angry = new QRadioButton(this);
	good->setObjectName("angry" + QString::number(mCount));
	QButtonGroup *group = new QButtonGroup(this);
	group->addButton(good);
	group->addButton(bad);
	group->addButton(angry);

	ui->gridLayout->addWidget(baseActionLabel);
	ui->gridLayout->addWidget(good);
	ui->gridLayout->addWidget(bad);
	ui->gridLayout->addWidget(angry);

	mCount++;
}

QMap<QString, ActionStatus> ScenarioActionsStatusForm::saveContent()
{
	mActionStatus.clear();
	if (ui->gridLayout->columnCount() != 4) {
		qDebug() << "columns != 4 (";
		return mActionStatus;
	}
	int const labelColumn = 0;
	int const goodColumn = 1;
	int const badColumn = 2;
	int const angryColumn = 3;
	for (int i = 0; i < ui->gridLayout->rowCount(); ++i) {
		if (i == 0) {
			continue;
		}
		QLabel *label = dynamic_cast<QLabel *>(ui->gridLayout->itemAtPosition(i, labelColumn)->widget());
		if (!label) {
			continue;
		}
		QString const name = label->text();
		ActionStatus status = ActionStatus::good;
		QRadioButton *goodRadioButton = dynamic_cast<QRadioButton *>(ui->gridLayout->itemAtPosition(i, goodColumn)->widget());
		if (!goodRadioButton) {
			continue;
		}
		if (goodRadioButton->isChecked()) {
			mActionStatus.insert(name, status);
			continue;
		}

		QRadioButton *badRadioButton = dynamic_cast<QRadioButton *>(ui->gridLayout->itemAtPosition(i, badColumn)->widget());
		if (!badRadioButton) {
			continue;
		}
		if (badRadioButton->isChecked()) {
			status = ActionStatus::neutral;
			mActionStatus.insert(name, status);
			continue;
		}

		QRadioButton *angryRadioButton = dynamic_cast<QRadioButton *>(ui->gridLayout->itemAtPosition(i, angryColumn)->widget());
		if (!angryRadioButton) {
			continue;
		}
		if (angryRadioButton->isChecked()) {
			status = ActionStatus::bad;
			mActionStatus.insert(name, status);
		}
	}
	return mActionStatus;
}

void ScenarioActionsStatusForm::clearSelection()
{
	//todo;
}
