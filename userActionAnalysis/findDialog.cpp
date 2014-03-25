#include "findDialog.h"
#include "ui_findDialog.h"

int const noSuchIndex = -1;
int const twoProperties = 2;
int const oneProperty = 1;
int const firstPropertyIndex = 0;
int const secondPropertyIndex = 1;

FindDialog::FindDialog(QWidget *parent) :
	QDialog(parent)
	, ui(new Ui::FindDialog)
	, mAction(nullptr)
{
	ui->setupUi(this);
	connect (ui->findButton, &QPushButton::clicked, this, &FindDialog::sendCustomAction);
}

void FindDialog::open(BaseUserAction *action)
{
	QString const actionName = action->userActionName();
	QMap<QString, QStringList> const properties = action->actionProperties();
	mAction = new BaseUserAction(actionName, properties);
	ui->comboBoxProperty1->clear();
	ui->comboBoxProperty2->clear();
	int propertiesCount = properties.count();
	if (propertiesCount == oneProperty) {
		QString const name = properties.keys().at(firstPropertyIndex);
		ui->labelProperty1->setText(name);
		ui->comboBoxProperty1->addItems(properties.value(name));

		ui->labelProperty1->show();
		ui->comboBoxProperty1->show();
		ui->labelProperty2->hide();
		ui->comboBoxProperty2->hide();
	}
	else if (propertiesCount == twoProperties) {
		QString const name1 = properties.keys().at(firstPropertyIndex);
		QString const name2 = properties.keys().at(secondPropertyIndex);

		ui->labelProperty1->setText(name1);
		ui->comboBoxProperty1->addItems(properties.value(name1));
		ui->labelProperty2->setText(name2);
		ui->comboBoxProperty2->addItems(properties.value(name2));

		ui->labelProperty1->show();
		ui->comboBoxProperty1->show();
		ui->labelProperty2->show();
		ui->comboBoxProperty2->show();
	}
	else {
		ui->labelProperty1->hide();
		ui->comboBoxProperty1->hide();
		ui->labelProperty2->hide();
		ui->comboBoxProperty2->hide();
	}
}


FindDialog::~FindDialog()
{
	delete mAction;
	delete ui;
}

void FindDialog::sendCustomAction()
{
	mAction->setUserActionProperty(ui->labelProperty1->text(), ui->comboBoxProperty1->currentText());
	if (!ui->comboBoxProperty2->isHidden()) {
		mAction->setUserActionProperty(ui->labelProperty2->text(), ui->comboBoxProperty2->currentText());
	}
	emit actionToFind(mAction->actionToString());
	accept();
}
