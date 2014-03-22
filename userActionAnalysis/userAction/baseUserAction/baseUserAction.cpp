#include "userAction/baseUserAction/baseUserAction.h"

BaseUserAction::BaseUserAction(const QString &name, const QMap<QString, QStringList> &properties)
	: UserAction(name)
	, mProperties (properties)
{
}

BaseUserAction::~BaseUserAction()
{
}

QMap<QString, QStringList> BaseUserAction::actionProperties() const
{
	return mProperties;
}

QMap<QString, QString> BaseUserAction::customActionProperties() const
{
	return mCustomProperties;
}

void BaseUserAction::setUserActionProperty(const QString &propertyName, const QString &propertyValue)
{
	if (mProperties.keys().contains(propertyName)) {
		if (mProperties.value(propertyName).contains(propertyValue)) {
			mCustomProperties.insert(propertyName, propertyValue);
		}
	}
}

const QString BaseUserAction::actionToString()
{
	QString result = userActionName();
	QMap<QString, QStringList> actionPropertiesMap = actionProperties();
	if (actionPropertiesMap.isEmpty()) {
		return result;
	}
	result += " — ";
	QMap<QString, QStringList>::const_iterator i = actionPropertiesMap.constBegin();
	while (i != actionPropertiesMap.constEnd()) {
		QString property = i.key();
		if (customActionProperties().keys().contains(property)) {
			property = property + ": " + customActionProperties().value(property) + "|";
		}
		else {
			property = property + ": " + i.value().at(0) + "|";
		}
		result += property;
		++i;
	}
	return result;
}
