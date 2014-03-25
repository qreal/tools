#pragma once

#include <QtCore/QList>
#include <QtCore/QMap>

#include <userAction/baseUserAction/baseUserAction.h>

class BaseUserActionList : public QList<BaseUserAction *>
{
public:
	BaseUserActionList();
	QMap<QString, QStringList> propertiesByBaseUserActionName(QString const &baseUserActionName);
	QStringList propertyValuesByName(QString const &baseUserActionName, QString const &propertyName);
	BaseUserActionList baseUserActionsWithProperty(QString const &propertyName);
	QStringList baseUserActionNames();
	BaseUserAction *baseUserActionByName(QString const &name);
};
