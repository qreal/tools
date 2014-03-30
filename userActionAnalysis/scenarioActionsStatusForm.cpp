#include "scenarioActionsStatusForm.h"
#include "ui_scenarioActionsStatusForm.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

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
	for (QObject *object: ui->verticalLayout->children()) {
		QHBoxLayout *layout = dynamic_cast<QHBoxLayout *>(object);
		if (layout) {
			for (QObject *child: layout->children()) {
				QString baseActionName;
				ActionStatus status = ActionStatus::good;
				QLabel *label = dynamic_cast<QLabel *>(child);
				if (label) {
					baseActionName = label->text();
				}
				else {
					QRadioButton *radioButton = dynamic_cast<QRadioButton *>(child);
					if (radioButton && radioButton->isChecked()) {
						if (radioButton->objectName().contains("good")) {
							status = ActionStatus::good;
						}
						else if (radioButton->objectName().contains("bad")) {
							status = ActionStatus::neutral;
						}
						else if (radioButton->objectName().contains("angry"))
							status = ActionStatus::bad;
					}
				}
				mActionStatus.insert(baseActionName, status);
			}
		}
	}
	return mActionStatus;
}
