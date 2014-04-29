#include "userAction/baseUserAction/baseUserAction.h"

#include <QtCore/QDebug>

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
            QString const value = customActionProperties().value(property);
            property = property + ": " + value + "|";
        }
        result += property;
        ++i;
    }
    return result.toUtf8();
}

const QString BaseUserAction::actionToRegExpString()
{
    QString result = "_" + userActionName();
    QMap<QString, QStringList> actionPropertiesMap = actionProperties();
    if (actionPropertiesMap.isEmpty()) {
        return result;
    }
    result += " — ";
    QMap<QString, QStringList>::const_iterator i = actionPropertiesMap.constBegin();
    while (i != actionPropertiesMap.constEnd()) {
        QString property = i.key();
        if (customActionProperties().keys().contains(property)) {
            QString const value = customActionProperties().value(property);
            if (value == QString::fromUtf8("<параметр>")) {
                property = property + ": .+|";
            }
            else {
                property = property + ": " + value + "|";
            }
        }
        else {
            property = property + ": .+|";
        }
        result += property;
        ++i;
    }
    if (isKeyAction()) {
        if (repeatCount() == 2) {
            result = "(" + result + ")+";
        }
    }
    else {
        if (repeatCount() == 2) {
            result = "(" + result + ")*";
        }
        else {
            result = "(" + result + ")?";
        }
    }
    return result.toUtf8();
}

bool BaseUserAction::compare(BaseUserAction *otherBaseUserAction)
{
    if (otherBaseUserAction == nullptr) {
        return false;
    }
    return ((userActionName() == otherBaseUserAction->userActionName())
            && (customActionProperties() == otherBaseUserAction->customActionProperties()));
}

BaseUserAction *BaseUserAction::unite(BaseUserAction *otherBaseUserAction)
{
    if (compare(otherBaseUserAction)) {
        duration()->setExact(duration()->exact() + otherBaseUserAction->duration()->exact());
        delete otherBaseUserAction;
    }
    return this;
}
