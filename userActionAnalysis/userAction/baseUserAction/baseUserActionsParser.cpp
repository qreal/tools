#include "userAction/baseUserAction/baseUserActionsParser.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QDir>

int const scrollCount = 21;
QString const pathToBaseUserActionXML = "/userAction/baseUserAction/baseUserActions.xml";

BaseUserActionsParser::BaseUserActionsParser()
{

}

BaseUserActionsParser::~BaseUserActionsParser()
{

}

BaseUserActionList BaseUserActionsParser::parse()
{
	BaseUserActionList baseUserActions;

	QDir dir;
	dir.current().cdUp();
	QDomDocument const document = loadDocument(dir.absolutePath() + pathToBaseUserActionXML);
	QDomNodeList const actionList = document.elementsByTagName("userAction");

	for (int i = 0; i < actionList.length(); ++i) {
		QDomNode action = actionList.at(i);
		QDomElement const actionElement = action.toElement();

		QString const actionName = actionElement.attribute("name", "noName");
		QDomNodeList propertiesList = actionElement.elementsByTagName("property");

		QMap<QString, QStringList> properties;

		for (int j = 0; j < propertiesList.length(); ++j) {
			QDomNode property = propertiesList.at(j);
			QDomElement const propertyElement = property.toElement();

			QString const propertyName = propertyElement.attribute("name", "noName");
			QString const type = propertyElement.attribute("type", "noType");

			QStringList values;
			values << "<параметр>";
			if (type == "variants") {
				QDomNodeList const valueList = propertyElement.elementsByTagName("value");

				for (int k = 0; k < valueList.length(); ++k) {
					QDomNode value = valueList.at(k);
					QDomElement const valueElement = value.toElement();
					QString const valueName = valueElement.text();
					values.append(valueName);
				}
			}
			else if (type == "int") {
				for (int i = 1; i < scrollCount; ++i) {
					values.append(QString::number(i));
				}
			}
			else {

			}
			properties.insert(propertyName, values);
		}
		BaseUserAction *baseUserAction = new BaseUserAction(actionName, properties);
		baseUserActions.append(baseUserAction);
	}
	mBaseUserActions << baseUserActions;
	return baseUserActions;
}

QList<BaseUserAction *> BaseUserActionsParser::parseUserLog(const QStringList &userLog)
{
	QList<BaseUserAction *> baseUserActions;
	for (const QString &userAction: userLog) {
		baseUserActions << parseUserActionFromLog(userAction);
	}
    return uniteBaseUserActions(baseUserActions);
}

QList<BaseUserAction *> BaseUserActionsParser::uniteBaseUserActions(const QList<BaseUserAction *> &userLogBaseActions)
{
    QList<BaseUserAction *> unitedBaseUserActions;
    BaseUserAction *previousUserAction = nullptr;
    for (BaseUserAction *userAction: userLogBaseActions) {
        if (userAction->compare(previousUserAction)) {
            previousUserAction = previousUserAction->unite(userAction);
        }
        else {
            if (previousUserAction != nullptr) {
                unitedBaseUserActions << previousUserAction;
            }
            previousUserAction = userAction;
        }
    }
    return unitedBaseUserActions;
}

BaseUserAction *BaseUserActionsParser::parseUserActionFromLog(const QString &userAction)
{
	QStringList userActionNameAndProperties = userAction.split(" — ", QString::SkipEmptyParts);
	if (userActionNameAndProperties.length() != 2) {
		return new BaseUserAction("unrecognized action", QMap<QString, QStringList>());
	}
	QString const actionNameWithOrderedNumber = userActionNameAndProperties.at(0);
	QString const actionName = actionNameWithOrderedNumber.section(" ", 1);
	BaseUserAction *baseUserActionFromList = mBaseUserActions.baseUserActionByName(actionName);
	if (baseUserActionFromList == nullptr) {
		return new BaseUserAction("unrecognized action", QMap<QString, QStringList>());
	}
	BaseUserAction *baseUserActionFromLog = new BaseUserAction(baseUserActionFromList->userActionName()
			, baseUserActionFromList->actionProperties());
	QStringList const userActionProperties = userActionNameAndProperties.at(1).split("|", QString::SkipEmptyParts);
	for (int i = 0; i < (userActionProperties.length() - 1); ++i) {
		QStringList const propertyNameAndValue = userActionProperties.at(i).split(": ", QString::SkipEmptyParts);
		if (propertyNameAndValue.length() != 2) {
			continue;
		}
		QString const propertyName = propertyNameAndValue.at(0);
		QString const propertyValue = propertyNameAndValue.at(1);
		baseUserActionFromLog->setUserActionProperty(propertyName, propertyValue);
	}
	QString const duration = userActionProperties.last();
    int exact = 0;
    if (duration.length() > 1) {
        if (duration.at(1) == '+') {
            QStringList durationValues = duration.split(" ", QString::SkipEmptyParts);
            if (!durationValues.isEmpty()) {
                exact = durationValues.at(0).mid(1).toInt();
                qDebug() << exact;
            }
        }
    }
	qDebug() << duration;
    baseUserActionFromLog->duration()->setExact(exact);
	return baseUserActionFromLog;
}

QDomDocument BaseUserActionsParser::loadDocument(QString const &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug() << "cannot open file " << fileName;
		return QDomDocument();
	}

	QDomDocument doc;
	QString error = "";
	int errorLine = 0;
	int errorCol = 0;

	if (!doc.setContent(&file, false, &error, &errorLine, &errorCol))
	{
		qDebug() << "parse error in " << fileName
				 << " at (" << errorLine << "," << errorCol
				 << "): " << error;
		file.close();
		return QDomDocument();
	}

	file.close();
	return doc;
}
