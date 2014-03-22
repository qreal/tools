#pragma once
#include <QDialog>
#include <QtCore/QMap>
#include <QCloseEvent>

#include "userAction/userActionProperty/duration.h"

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PropertiesDialog(QWidget *parent = 0);
	~PropertiesDialog();

	void setLabelsAndProperties(QMap<QString, QStringList> const &properties
			, QMap<QString, QString> const &conProperties
			, int const &repeatCountValue
			, bool isKeyActionValue
			, Duration *durationValue
			, QStringList const &disabledProperties);
	void initDefaultValues();
	QMap<QString, QString> conProperties();
	int repeatCount();
	bool isKeyAction();
	Duration *duration();

private slots:
	void saveProperties();

private:
	Ui::PropertiesDialog *ui;
	QMap<QString, QString> mConProperties;
	int mRepeatCount;
	bool mIsKeyAction;
	Duration *mDuration;
};
