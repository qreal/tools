#pragma once
#include <QDialog>
#include <QtCore/QMap>
#include <QCloseEvent>

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PropertiesDialog(QWidget *parent = 0);
	~PropertiesDialog();

	void setLabelsAndProperties(QMap<QString, QStringList> const &properties, QMap<QString, QString> const &conProperties
			, QStringList const &disabledProperties);
	QMap<QString, QString> conProperties();

private slots:
	void saveProperties();

private:
	Ui::PropertiesDialog *ui;
	QMap<QString, QString> mConProperties;
};
