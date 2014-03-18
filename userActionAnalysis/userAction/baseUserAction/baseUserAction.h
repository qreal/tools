#pragma once

#include <QtCore/QMap>
#include <QtCore/QStringList>

#include "userAction/userAction.h"

class BaseUserAction : public UserAction
{

public:
	BaseUserAction(QString const &name, QMap<QString, QStringList> const &properties);
	~BaseUserAction();
	QMap<QString, QStringList> actionProperties() const;
	QMap<QString, QString> customActionProperties() const;
	void setUserActionProperty(QString const &propertyName, QString const &propertyValue);
	QString const actionToString();

private:
	QMap<QString, QStringList> mProperties;
	QMap<QString, QString> mCustomProperties;
};
