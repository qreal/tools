#include "userAction/complexUserAction/complexUserActionGenerator.h"

#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>

ComplexUserActionGenerator::ComplexUserActionGenerator(const BaseUserActionList &baseUserActionList
		, ComplexUserActionList const &complexUserActionList)
{
	if (mComplexActionsDir.current().cdUp()) {
		if (mComplexActionsDir.cd("userAction/complexUserAction/XMLcomplexUserActions")) {
			int const count = mComplexActionsDir.count();
			mComplexActionsCount = count;
		}
		else {
			mComplexActionsCount = 0;
		}
	}
	else {
		mComplexActionsCount = 0;
	}
	mBaseUserActions << baseUserActionList;
	mComplexUserActions << complexUserActionList;
}


ComplexUserActionGenerator::~ComplexUserActionGenerator()
{

}

void ComplexUserActionGenerator::generateComplexAction(const QString &name, const QList<RuleElement *> &userActions)
{
	mComplexActionsCount++;
	mProperties.clear();
	mCustomProperties.clear();
	mUserActions.clear();

	QString const documentName = "complexUserAction" + QString::number(mComplexActionsCount);
	QDomDocument document(documentName);
	QDomElement complexUserAction = document.createElement("complexUserAction");
	complexUserAction.setAttribute("name", name);
	document.appendChild(complexUserAction);

	for (RuleElement *userAction: userActions) {
		addComplexAction(userAction, document, complexUserAction);
	}

	QString const dir = mComplexActionsDir.absolutePath();
	if (!QDir(dir).exists()) {
		QDir(dir).mkpath(dir);
	}

	QFile file(dir + "/" + documentName + ".xml");
	if (file.open(QFile::WriteOnly | QFile::Truncate)) {
		QTextStream stream(&file);
		document.save(stream, 1);
	}
	file.close();
	QMessageBox::information(nullptr, QString::fromUtf8("Сохранение")
							 , QString::fromUtf8("Составное действие успешно сохранено."),
							 QMessageBox::Ok);
	ComplexUserAction *newComplexUserAction = new ComplexUserAction(name, mUserActions);
	mComplexUserActions << newComplexUserAction;
	emit newComplexActionCreated(newComplexUserAction);
}

QDomElement ComplexUserActionGenerator::userActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList)
{
	if (userAction->isBaseAction()) {
		return baseUserActionElement(userAction, document, userActionList);
	}

	QDomElement complexUserActionElement = document.createElement("complexUserAction");
	QList<UserAction *> complexUserActionList;
	QString const name = userAction->content();
	complexUserActionElement.setAttribute("name", name);
	for (RuleElement *userActionFromList: userAction->list()) {
		complexUserActionElement.appendChild(userActionElement(userActionFromList, document, complexUserActionList));
	}
	ComplexUserAction *complexUserAction = new ComplexUserAction(name, complexUserActionList);
	userActionList.append(complexUserAction);
	return complexUserActionElement;
}

QDomElement ComplexUserActionGenerator::baseUserActionElement(RuleElement *userAction, QDomDocument &document, QList<UserAction *> &userActionList)
{
	QDomElement baseUserActionElement = document.createElement("baseUserAction");
	QStringList const userActionNameAndProperties = userAction->content().split(" — ", QString::SkipEmptyParts);
		if (userActionNameAndProperties.length() != 2) {
			return QDomElement();
		}
		QString const userActionName = userActionNameAndProperties.at(0);
		baseUserActionElement.setAttribute("name", userActionName);
		BaseUserAction *baseUserActionFromList = mBaseUserActions.baseUserActionByName(userActionName);
		if (baseUserActionFromList != nullptr) {

			BaseUserAction *baseUserAction = new BaseUserAction(baseUserActionFromList->userActionName(), baseUserActionFromList->actionProperties());

			QString const userActionProperties = userActionNameAndProperties.at(1);
			QMap<QString, QString> properties = userActionPropertiesMap(userActionProperties);

			QMap<QString, QString>::const_iterator i = properties.constBegin();
			while (i != properties.constEnd()) {
				QString const propertyName = i.key();
				QString const propertyValue = i.value();
				if (propertyValue == QString::fromUtf8("<параметр>")) {
					QDomElement property = document.createElement("flexibleProperty");
					property.setAttribute("name", propertyName);
					property.setAttribute("value", "?");

					QStringList const propertyValues = mBaseUserActions.propertyValuesByName(userActionName, propertyName);
					mProperties.insert(propertyName, propertyValues);

					baseUserActionElement.appendChild(property);
				}
				else {
					QDomElement customProperty = document.createElement("customProperty");
					customProperty.setAttribute("name", propertyName);
					customProperty.setAttribute("value", propertyValue);

					mCustomProperties.insert(propertyName, propertyValue);
					baseUserAction->setUserActionProperty(propertyName, propertyValue);

					baseUserActionElement.appendChild(customProperty);
				}
				++i;
			}
			userActionList.append(baseUserAction);
		}
		else {
			qDebug() << "base action was't unique or has't found at all.";
		}
		return baseUserActionElement;
}

void ComplexUserActionGenerator::addComplexAction(RuleElement *userAction, QDomDocument &document, QDomElement &complexUserActionElement)
{
	complexUserActionElement.appendChild(userActionElement(userAction, document, mUserActions));
}

QMap<QString, QString> ComplexUserActionGenerator::userActionPropertiesMap(const QString &userActionProperties)
{
	QStringList const properties = userActionProperties.split("|", QString::SkipEmptyParts);
	QMap<QString, QString> userActionPropertiesMap;
	for (const QString property: properties) {
		QStringList const propertyNameValue = property.split(": ", QString::SkipEmptyParts);
		if (propertyNameValue.length() != 2) {
			continue;
		}
		QString const propertyName = propertyNameValue.at(0);
		QString const propertyValue = propertyNameValue.at(1);
		userActionPropertiesMap.insert(propertyName, propertyValue);
	}
	return userActionPropertiesMap;
}
