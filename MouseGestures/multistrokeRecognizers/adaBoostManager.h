#pragma once
#include "abstractRecognizer.h"
#include "GeometricForms.h"
#include "recognizerInterface.h"

class AdaBoostManager : public RecognizerInterface
{
public:
    AdaBoostManager();
    double getMaxDistance(QString const &);
    bool isMultistroke();
    double getDistance(QList<double *> const & key1, QList<double *> const & key2);
    void setKey(PathVector const & path);
    void setIdealGestures(const QList<Entity> & objects);
    void learn(QList<Entity> const & trainingSet);

private:
    QString recognizeObject(PathVector const & gesture);
    QString recognizeObject();
    double listSum(QList<double> list);
    QList<AbstractRecognizer *> mRecognizers;
    QList<double> mRecognizersWeights;
    GesturesManager * mGesturesManager;
    QList<Entity> mObjects;// Ideal gestures (name - path)
    QString mLastGesture;
    PathVector mGesture;
};
