#include "complexActionNameDialog.h"
#include "ui_complexActionNameDialog.h"
#include <QtWidgets/QMessageBox>

ComplexActionNameDialog::ComplexActionNameDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ComplexActionNameDialog)
{
	ui->setupUi(this);
	connect(ui->pushButton, &QPushButton::clicked, this, &ComplexActionNameDialog::saveComplexActionName);
}

ComplexActionNameDialog::~ComplexActionNameDialog()
{
	delete ui;
}

void ComplexActionNameDialog::openDialog()
{
	ui->lineEdit->clear();
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
