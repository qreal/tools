#include "baseUserActionList.h"

BaseUserActionList::BaseUserActionList()
	: QList<BaseUserAction *>()
{
}

QMap<QString, QStringList> BaseUserActionList::propertiesByBaseUserActionName(const QString &baseUserActionName)
{
	for (int i = 0; i < length(); ++i) {
		BaseUserAction *baseUserAction = at(i);
		if (baseUserAction->userActionName() == baseUserActionName) {
			return baseUserAction->actionProperties();
		}
	}
	return QMap<QString, QStringList>();
}

QStringList BaseUserActionList::propertyValuesByName(const QString &baseUserActionName, const QString &propertyName)
{
	QMap<QString, QStringList> properties = propertiesByBaseUserActionName(baseUserActionName);
	return properties.value(propertyName);
}

BaseUserActionList BaseUserActionList::baseUserActionsWithProperty(const QString &propertyName)
{
	BaseUserActionList result;
	for (int i = 0; i < length(); ++i) {
		BaseUserAction *baseUserAction = at(i);
		if (baseUserAction->actionProperties().keys().contains(propertyName)) {
			result << baseUserAction;
		}
	}
	return result;

}

QStringList BaseUserActionList::baseUserActionNames()
{
	QStringList baseUserActionNames;
	for (int i = 0; i < length(); ++i) {
		BaseUserAction *baseUserAction = at(i);
		baseUserActionNames << baseUserAction->userActionName();
	}
	return baseUserActionNames;
}

BaseUserAction *BaseUserActionList::baseUserActionByName(const QString &name)
{
	BaseUserActionList result;
	for (int i = 0; i < length(); ++i) {
		BaseUserAction *baseUserAction = at(i);
		if (baseUserAction->userActionName() == name) {
			result << baseUserAction;
		}
	}
	if (result.length() == 1) {
		return result.first();
	}
	else {
		return nullptr;
	}
}
