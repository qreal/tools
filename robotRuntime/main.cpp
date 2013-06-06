#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QStringList>

#include <QtScript/QScriptEngine>

#include "robotModel.h"

using namespace robotRuntime;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args = app.arguments();

    qDebug() << "Running " + args.join(" ");

    if (args.count() != 2) {
        qDebug() << "Usage: qtScriptRunner <QtScript file>";
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

    RobotModel robotModel;

    QScriptEngine engine;
    QScriptValue robotModelProxy = engine.newQObject(&robotModel);
    engine.globalObject().setProperty("robotModel", robotModelProxy);

    qDebug() << "Result: " << engine.evaluate(script).toString();

    return 0;
}
