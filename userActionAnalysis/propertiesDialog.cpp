#include "propertiesDialog.h"
#include "ui_propertiesDialog.h"

int const noSuchIndex = -1;
int const twoProperties = 2;
int const oneProperty = 1;
int const firstPropertyIndex = 0;
int const secondPropertyIndex = 1;

PropertiesDialog::PropertiesDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PropertiesDialog)
{
	ui->setupUi(this);
	connect(ui->saveButton, &QPushButton::clicked, this, &PropertiesDialog::saveProperties);
}

PropertiesDialog::~PropertiesDialog()
{
	delete ui;
}

void PropertiesDialog::setLabelsAndProperties(const QMap<QString, QStringList> &properties, QMap<QString, QString> const &conProperties, QStringList const &disabledProperties)
{
	mConProperties.clear();
	ui->comboBoxProperty1->clear();
	ui->comboBoxProperty2->clear();
	ui->comboBoxProperty1->setEnabled(true);
	ui->comboBoxProperty2->setEnabled(true);
	int propertiesCount = properties.count();
	if (propertiesCount == oneProperty) {
		QString const name = properties.keys().at(firstPropertyIndex);
		ui->labelProperty1->setText(name);
		ui->comboBoxProperty1->addItems(properties.values().at(firstPropertyIndex));
		int const currentIndex = ui->comboBoxProperty1->findText(conProperties.value(name));
		if (currentIndex != noSuchIndex) {
			ui->comboBoxProperty1->setCurrentIndex(currentIndex);
		}

		ui->labelProperty1->show();
		ui->comboBoxProperty1->show();
		ui->labelProperty2->hide();
		ui->comboBoxProperty2->hide();

		if (disabledProperties.contains(name)) {
			ui->comboBoxProperty1->setDisabled(true);
		}
	}
	else if (propertiesCount == twoProperties) {
		QString const name1 = properties.keys().at(firstPropertyIndex);
		QString const name2 = properties.keys().at(secondPropertyIndex);

		ui->labelProperty1->setText(properties.keys().at(firstPropertyIndex));
		ui->comboBoxProperty1->addItems(properties.values().at(firstPropertyIndex));
		int const currentIndex1 = ui->comboBoxProperty1->findText(conProperties.value(name1));
		if (currentIndex1 != noSuchIndex) {
			ui->comboBoxProperty1->setCurrentIndex(currentIndex1);
		}

		ui->labelProperty2->setText(properties.keys().at(secondPropertyIndex));
		ui->comboBoxProperty2->addItems(properties.values().at(secondPropertyIndex));
		int const currentIndex2 = ui->comboBoxProperty2->findText(conProperties.value(name2));
		if (currentIndex2 != noSuchIndex) {
			ui->comboBoxProperty2->setCurrentIndex(currentIndex2);
		}

		ui->labelProperty1->show();
		ui->comboBoxProperty1->show();
		ui->labelProperty2->show();
		ui->comboBoxProperty2->show();

		if (disabledProperties.contains(name1)) {
			ui->comboBoxProperty1->setDisabled(true);
		}
		if (disabledProperties.contains(name2)) {
			ui->comboBoxProperty2->setDisabled(true);
		}
	}
	else {
		ui->labelProperty1->hide();
		ui->comboBoxProperty1->hide();
		ui->labelProperty2->hide();
		ui->comboBoxProperty2->hide();
	}
}

QMap<QString, QString> PropertiesDialog::conProperties()
{
	return mConProperties;
}

void PropertiesDialog::saveProperties()
{
	mConProperties.insert(ui->labelProperty1->text(), ui->comboBoxProperty1->currentText());
	if (!ui->comboBoxProperty2->isHidden()) {
		mConProperties.insert(ui->labelProperty2->text(), ui->comboBoxProperty2->currentText());
	}
	accept();
}

