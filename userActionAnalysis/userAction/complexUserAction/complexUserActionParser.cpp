#include "userAction/complexUserAction/complexUserActionParser.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QDir>

int const scrollCount = 21;

ComplexUserActionParser::ComplexUserActionParser(BaseUserActionList baseUserActions)
	: mBaseUserActions(baseUserActions)
{

}

ComplexUserActionParser::~ComplexUserActionParser()
{

}

ComplexUserActionList ComplexUserActionParser::parse()
{
	ComplexUserActionList complexActions;

	QDir dir;
	dir.current().cdUp();
	dir.cdUp();
	dir.setPath("userAction/complexUserAction/XMLcomplexUserActions");
	QStringList filters;
	filters << "*.xml";
	QStringList const complexActionFileNames = dir.entryList(filters);
	QStringList complexActionFiles;
	for (const QString &actionFileName: complexActionFileNames) {
		complexActionFiles << dir.absolutePath() + "/" + actionFileName;
	}
	for (const QString &actionFile: complexActionFiles) {
		ComplexUserAction *complexUserAction = parseAction(actionFile);
		if (complexUserAction != nullptr) {
			complexActions << complexUserAction;
		}
	}
	return complexActions;
}

ComplexUserActionList ComplexUserActionParser::parseScenarios()
{
	ComplexUserActionList scenarios;

	QDir dir;
	dir.current().cdUp();
	dir.cdUp();
	dir.setPath("userAction/userScenario");
	QStringList filters;
	filters << "*.xml";
	QStringList const scenarioFileNames = dir.entryList(filters);
	QStringList scenarioFiles;
	for (const QString &actionFileName: scenarioFileNames) {
		scenarioFiles << dir.absolutePath() + "/" + actionFileName;
	}
	for (const QString &actionFile: scenarioFiles) {
		ComplexUserAction *scenario = parseAction(actionFile, true);
		if (scenario != nullptr) {
			scenarios << scenario;
		}
	}
	return scenarios;
}

QDomDocument ComplexUserActionParser::loadDocument(QString const &fileName)
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

ComplexUserAction *ComplexUserActionParser::parseAction(const QString &fileName, bool isScenario)
{
	QString mainTagName = (isScenario) ? "scenario" : "mainComplexUserAction";
	QDomDocument const document = loadDocument(fileName);
	QDomNodeList const actionList = document.elementsByTagName(mainTagName);
	if (actionList.length() != 1) {
		return nullptr;
	}
	QDomNode action = actionList.at(0);
	QDomElement const actionElement = action.toElement();

	QString const actionName = actionElement.attribute("name", "noName");
	QDomNodeList userActionList = actionElement.childNodes();

	QList<UserAction *> userActions;
	for (int i = 0; i < userActionList.length(); ++i) {
		QDomNode userAction = userActionList.at(i);
		QDomElement const userActionElement = userAction.toElement();
		if (userActionElement.tagName() == "baseUserAction") {
			BaseUserAction *baseAction = parseBaseUserAction(userActionElement);
			if (baseAction != nullptr) {
				userActions.append(baseAction);
			}
		}
		else if (userActionElement.tagName() == "complexUserAction") {
			ComplexUserAction *complexAction = parseComplexUserAction(userActionElement);
			if (complexAction != nullptr) {
				complexAction->setRepeatCount(userActionElement.attribute("repeatCount", "1").toInt());
				complexAction->setIsKeyAction(userActionElement.attribute("isKeyAction", "true") == "true");
				userActions.append(complexAction);
			}
		}
		else if (userActionElement.tagName() == "redTapeInstruction") {
			UserAction *redTapeInstruction = parseRedTapeInstruction(userActionElement);
			if (redTapeInstruction != nullptr) {
				userActions.append(redTapeInstruction);
			}
		}
	}
	QMap<QString, ActionStatus> actionStatus;
	if (isScenario) {
		QDomNodeList const actionStatusList = action.toElement().elementsByTagName("actionStatus");
		if (actionStatusList.length() == 1) {
			QDomElement actionStatusElement = actionStatusList.at(0).toElement();
			QDomNodeList const children = actionStatusElement.elementsByTagName("baseActionStatus");
			for (int i = 0; i < children.length(); ++i) {
				QDomElement child = children.at(i).toElement();
				QString const name = child.attribute("name", "");
				QString const value = child.attribute("value", "");
				ActionStatus status = ActionStatus::good;
				if (value == "bad") {
					status = ActionStatus::bad;
				}
				else if (value == "neutral") {
					status = ActionStatus::neutral;
				}
				actionStatus.insert(name, status);
			}
		}
	}
	ComplexUserAction *newComplexUserAction = new ComplexUserAction(actionName, userActions);
	newComplexUserAction->setUserActionsStatus(actionStatus);
	return newComplexUserAction;
}

BaseUserAction *ComplexUserActionParser:: parseBaseUserAction(QDomElement const &element)
{
	QString const baseUserActionName = element.attribute("name", "noName");
	BaseUserAction *baseUserActionFromList = mBaseUserActions.baseUserActionByName(baseUserActionName);
	if (baseUserActionFromList == nullptr) {
		return nullptr;
	}
	BaseUserAction *baseUserAction = new BaseUserAction(baseUserActionName, baseUserActionFromList->actionProperties());

	QDomNodeList const repeatCountList = element.elementsByTagName("RepeatCount");
	if (repeatCountList.length() == 1) {
		QDomElement repeatCountElement = repeatCountList.at(0).toElement();
		int const repeatCount = (repeatCountElement.text() == "1") ? 1 : 2;
		baseUserAction->setRepeatCount(repeatCount);
	}

	QDomNodeList const isKeyActionList = element.elementsByTagName("IsKeyAction");
	if (isKeyActionList.length() == 1) {
		QDomElement isKeyActionElement = isKeyActionList.at(0).toElement();
		bool const isKeyAction = (isKeyActionElement.text() == "true");
		baseUserAction->setIsKeyAction(isKeyAction);
	}

	QDomNodeList const durationList = element.elementsByTagName("Duration");
	if (durationList.length() == 1) {
		QDomElement durationElement = durationList.at(0).toElement();
		QDomNodeList durationChildren = durationElement.childNodes();
		int from = 0;
		int to = 0;
		for (int k = 0; k < durationChildren.length(); ++k) {
			QDomElement durationChildElement = durationChildren.at(k).toElement();
			if (durationChildElement.tagName() == "From") {
				from = durationChildElement.text().toInt();
			}
			else if (durationChildElement.tagName() == "To") {
				to = durationChildElement.text().toInt();
			}
		}
		baseUserAction->setDuration(from, to);
	}

	QDomNodeList const customPropertyList = element.elementsByTagName("customProperty");

	for (int j = 0; j < customPropertyList.length(); ++j) {
		QDomNode customProperty = customPropertyList.at(j);
		QDomElement const customPropertyElement = customProperty.toElement();
		QString const customPropertyName = customPropertyElement.attribute("name", "");
		QString const customPropertyValue = customPropertyElement.attribute("value", "");
		if (customPropertyName != "" && customPropertyValue != "") {
			baseUserAction->setUserActionProperty(customPropertyName, customPropertyValue);
		}
	}
	return baseUserAction;
}

ComplexUserAction *ComplexUserActionParser::parseComplexUserAction(const QDomElement &element)
{
	QString const actionName = element.attribute("name", "noName");
	QDomNodeList userActionList = element.childNodes();

	QList<UserAction *> userActions;
	for (int i = 0; i < userActionList.length(); ++i) {
		QDomNode userAction = userActionList.at(i);
		QDomElement const userActionElement = userAction.toElement();
		if (userActionElement.tagName() == "baseUserAction") {
			BaseUserAction *baseAction = parseBaseUserAction(userActionElement);
			if (baseAction != nullptr) {
				userActions.append(baseAction);
			}
		}
		else if (userActionElement.tagName() == "complexUserAction") {
			ComplexUserAction *complexAction = parseComplexUserAction(userActionElement);
			if (complexAction != nullptr) {
				complexAction->setRepeatCount(userActionElement.attribute("repeatCount", "1").toInt());
				complexAction->setIsKeyAction(userActionElement.attribute("isKeyAction", "true") == "true");
				userActions.append(complexAction);
			}
		}
		else if (userActionElement.tagName() == "redTapeInstruction") {
			UserAction *redTapeInstruction = parseRedTapeInstruction(userActionElement);
			if (redTapeInstruction != nullptr) {
				userActions.append(redTapeInstruction);
			}
		}
	}
	return new ComplexUserAction(actionName, userActions);
}

UserAction *ComplexUserActionParser::parseRedTapeInstruction(const QDomElement &element)
{
	return new UserAction(element.attribute("name", ""));
}
