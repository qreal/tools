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

ComplexUserAction *ComplexUserActionParser::parseAction(const QString &fileName)
{
	QDomDocument const document = loadDocument(fileName);
	QDomNodeList const actionList = document.elementsByTagName("complexUserAction");
	if (actionList.length() != 1) {
		return nullptr;
	}
	QDomNode action = actionList.at(0);
	QDomElement const actionElement = action.toElement();

	QString const actionName = actionElement.attribute("name", "noName");
	QDomNodeList baseActionList = actionElement.elementsByTagName("userAction");

	QList<UserAction *> userActions;
	for (int i = 0; i < baseActionList.length(); ++i) {
		QDomNode baseAction = baseActionList.at(i);
		QDomElement const baseUserActionElement = baseAction.toElement();

		QString const baseUserActionName = baseUserActionElement.attribute("name", "noName");
		BaseUserAction *baseUserActionFromList = mBaseUserActions.baseUserActionByName(baseUserActionName);
		if (baseUserActionElement.isNull()) {
			continue;
		}
		BaseUserAction *baseUserAction = new BaseUserAction(baseUserActionFromList->userActionName(), baseUserActionFromList->actionProperties());
		QDomNodeList const customPropertyList = baseUserActionElement.elementsByTagName("customProperty");

		for (int j = 0; j < customPropertyList.length(); ++j) {
			QDomNode customProperty = customPropertyList.at(i);
			QDomElement const customPropertyElement = customProperty.toElement();
			QString const customPropertyName = customPropertyElement.attribute("name", "");
			QString const customPropertyValue = customPropertyElement.attribute("value", "");
			if (customPropertyName != "" && customPropertyValue != "") {
				baseUserAction->setUserActionProperty(customPropertyName, customPropertyValue);
			}
		}
		userActions << baseUserAction;
	}
	return new ComplexUserAction(actionName, userActions);
}
