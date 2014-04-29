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
    QString const actionToRegExpString();

    bool compare(BaseUserAction *otherBaseUserAction);
    BaseUserAction* unite(BaseUserAction *otherBaseUserAction);

private:
	QMap<QString, QStringList> mProperties;
	QMap<QString, QString> mCustomProperties;
};
