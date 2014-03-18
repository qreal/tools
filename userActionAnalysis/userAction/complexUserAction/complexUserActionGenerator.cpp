#include "userAction/complexUserAction/complexUserActionGenerator.h"

#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>

ComplexUserActionGenerator::ComplexUserActionGenerator(const BaseUserActionList &baseUserActionList)
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
}


ComplexUserActionGenerator::~ComplexUserActionGenerator()
{

}

void ComplexUserActionGenerator::generateComplexAction(const QString &name, const QStringList &userActions)
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

	for (const QString userAction: userActions) {
		complexUserAction.appendChild(userActionElement(userAction, document));
	}
	QDomElement propertiesElement = document.createElement("properties");
	complexUserAction.appendChild(propertiesElement);
	QMap<QString, QStringList>::const_iterator i = mProperties.constBegin();
	while (i != mProperties.constEnd()) {
		QDomElement propertyElement = document.createElement("property");
		propertyElement.setAttribute("name", i.key());
		QStringList const values = i.value();
		for (QString const value: values) {
			if (value == QString::fromUtf8("<параметр>")) {
				continue;
			}
			QDomElement valueElement = document.createElement("value");
			QDomText text = document.createTextNode(value);
			valueElement.appendChild(text);
			propertyElement.appendChild(valueElement);
		}
		propertiesElement.appendChild(propertyElement);
		++i;
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
	emit newComplexActionCreated(newComplexUserAction);
}

QDomElement ComplexUserActionGenerator::userActionElement(const QString &userAction, QDomDocument &document)
{
	QDomElement userActionElement = document.createElement("userAction");
	QStringList const userActionNameAndProperties = userAction.split(" — ", QString::SkipEmptyParts);
	if (userActionNameAndProperties.length() != 2) {
		return QDomElement();
	}
	QString const userActionName = userActionNameAndProperties.at(0);
	userActionElement.setAttribute("name", userActionName);
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

				userActionElement.appendChild(property);
			}
			else {
				QDomElement customProperty = document.createElement("customProperty");
				customProperty.setAttribute("name", propertyName);
				customProperty.setAttribute("value", propertyValue);

				mCustomProperties.insert(propertyName, propertyValue);
				baseUserAction->setUserActionProperty(propertyName, propertyValue);

				userActionElement.appendChild(customProperty);
			}
			++i;
		}
		mUserActions << baseUserAction;
	}
	else {
		qDebug() << "base action was't unique or has't found at all.";
	}
	return userActionElement;
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
