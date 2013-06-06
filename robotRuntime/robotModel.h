#include <QtCore/QObject>
#include <QtCore/QString>

namespace robotRuntime {

class RobotModel : public QObject
{
    Q_OBJECT

public slots:
    void motorOn(QString const &port, int power);
    void beep();
};

}
