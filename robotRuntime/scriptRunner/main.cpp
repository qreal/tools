#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>
#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace trikControl;
using namespace scriptRunner;

Q_DECLARE_METATYPE(Motor*)

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QStringList args = app.arguments();

	qDebug() << "Running " + args.join(" ");

	if (args.count() != 2) {
		qDebug() << "Usage: scriptRunner <QtScript file>";
		return 1;
	}

	QString const scriptFileName = args[1];

	QFile file(scriptFileName);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!file.isOpen()) {
		throw "File open operation failed";
	}

	QTextStream input;
	input.setDevice(&file);
	input.setCodec("UTF-8");
	QString script = input.readAll();
	file.close();

	Brick brick;

	QScriptEngine engine;

	qScriptRegisterMetaType(&engine, motorToScriptValue, motorFromScriptValue);

	QScriptValue brickProxy = engine.newQObject(&brick);
	engine.globalObject().setProperty("brick", brickProxy);

	engine.evaluate(script);

	return 0;
}
