#include <math.h>
#include "adaboostmanager.h"
#include "GeometricForms.h"
#include "multistrokeGesturesManagers.h"
#include "rectanglegesturesmanager.h"
#include "nearestposgridgesturesmanager.h"
#include "QDebug"

AdaBoostManager::AdaBoostManager()
{
    mRecognizers.append(new AbstractRecognizer(new RectangleGesturesManager()));
    mRecognizers.append(new AbstractRecognizer(new NearestPosGridGesturesManager()));
    //mRecognizers.append(new AbstractRecognizer(new LevenshteinXYSortGesturesManager()));
    for(int i = 0; i < mRecognizers.length(); ++ i) {
        mRecognizersWeights.append(0);
    }
}

QString AdaBoostManager::recognizeObject(PathVector const & gesture)
{
    double maxProbability = 0;
    QString resultantObject = mObjects[0].first;
    foreach (Entity object, mObjects) {
        double probability = 0;
        for(int i = 0; i < mRecognizers.length(); ++ i) {
            QString answer = mRecognizers[i]->recognizeObject(gesture);
            if (answer == object.first) {
                probability += mRecognizersWeights[i];
            }
        }
        if (probability > maxProbability) {
            maxProbability = probability;
            resultantObject = object.first;
        }
    }
    return resultantObject;
}

void AdaBoostManager::setIdealGestures(const QList<Entity> & objects)
{
    mObjects = objects;
}

double AdaBoostManager::listSum(QList<double> list)
{
    double sum = 0;
    foreach(double i, list) {
        sum += i;
    }
    return sum;
}

void AdaBoostManager::learn(QList<Entity> const & trainingSet)
{
    QList<double> alphas; //weights for the classifiers
    for (int i = 0; i < mRecognizers.length(); ++ i) {
        alphas.append(0);
    }
    int n = trainingSet.length();
    //Initialize the observation weights
    QList<double> weights;
    for(int i = 0; i < n; ++ i) {
        weights.append(static_cast<double>(1) / n);
    }
    foreach (AbstractRecognizer * recognizer, mRecognizers)
    {
        recognizer->setIdealGestures(mObjects);
        //Calculate the error
        double error = 0;
        foreach(Entity sample, trainingSet) {
            if (recognizer->recognizeObject(sample.second) != sample.first)
                error += weights.at(trainingSet.indexOf(sample));
        }
        error = error / listSum(weights);
        if (error > 0.5) {
            continue;
        }
        //Compute the weight for the classifier
        alphas[mRecognizers.indexOf(recognizer)] = log((1 - error) / error);
        //Set the new weights for the training data
        for(int i = 0; i < weights.length(); ++ i) {
            Entity sample = trainingSet[i];
            if (recognizer->recognizeObject(sample.second) != sample.first)
                weights[i] = weights[i] * exp(alphas[mRecognizers.indexOf(recognizer)]);
        }
        //Re-normalize the weights for the training data
        double weightsSum = listSum(weights);
        for(int i = 0; i < weights.length(); ++ i) {
            weights[i] = weights[i] / weightsSum;
        }
    }

    mRecognizersWeights = alphas;
}
