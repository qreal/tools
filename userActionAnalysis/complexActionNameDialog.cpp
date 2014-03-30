#include "complexActionNameDialog.h"
#include "ui_complexActionNameDialog.h"
#include <QtWidgets/QMessageBox>
#include <QtGui/QFont>

ComplexActionNameDialog::ComplexActionNameDialog(QWidget *parent, const QStringList &baseActionNames) :
	QDialog(parent),
	ui(new Ui::ComplexActionNameDialog)
{
	ui->setupUi(this);
	mScenarioForm = new ScenarioActionsStatusForm(this, baseActionNames);
	connect(ui->pushButton, &QPushButton::clicked, this, &ComplexActionNameDialog::saveComplexActionName);
}

ComplexActionNameDialog::~ComplexActionNameDialog()
{
	delete mScenarioForm;
	delete ui;
}

void ComplexActionNameDialog::openDialog(bool isScenario)
{
	ui->lineEdit->clear();
//	if (isScenario) {
	ui->verticalLayout->addWidget(mScenarioForm);
//	}
	show();
}

void ComplexActionNameDialog::initReservedNames(const QStringList &actionNames)
{
	mReservedNames << actionNames;
}

void ComplexActionNameDialog::addReservedName(const QString &actionName)
{
	mReservedNames << actionName;
}

const QString ComplexActionNameDialog::complexActionName()
{
	return mComplexActionName;
}

void ComplexActionNameDialog::saveComplexActionName()
{
	QString const text = ui->lineEdit->text();
	if (text.isEmpty()) {
		QMessageBox::warning(this, QString::fromUtf8("Предупреждение")
							 , QString::fromUtf8("Название действия не может быть пустой строкой, напишите хоть что-нибудь.")
							 , QMessageBox::Ok);
		return;
	}
	else {
		if (mReservedNames.contains(text)) {
			QMessageBox::warning(this, QString::fromUtf8("Предупреждение")
								 , QString::fromUtf8("Действие с таким названием уже есть, нужно другое.")
								 , QMessageBox::Ok);
			return;
		}
		else {
			mComplexActionName = text;
			mReservedNames << mComplexActionName;
			accept();
		}
	}
}
