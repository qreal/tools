#include "runner.h"

#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>
#include <trikControl/motor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)

void Runner::run(QString const &script)
{
	Brick brick;

	QScriptEngine engine;

	qScriptRegisterMetaType(&engine, motorToScriptValue, motorFromScriptValue);

	QScriptValue brickProxy = engine.newQObject(&brick);
	engine.globalObject().setProperty("brick", brickProxy);

	engine.evaluate(script);
}
