#include "simpleformsinitializer.h"
#include "QMap"
#include "cmath"

QMap<QString, PathVector> SimpleFormsInitializer::initialForms()
{
	QMap<QString, PathVector> forms;
	PointVector square;
	square << QPoint(-10, -10) << QPoint(-10, 10)
		<< QPoint(10, 10) << QPoint(10, -10) << QPoint(-10, -10);
	PathVector squareGesture;
	squareGesture << square;
	forms["square"] = squareGesture;
	PointVector rhombus;
	rhombus << QPoint(-10, 0) << QPoint(0, -10)
		<< QPoint(10, 0) << QPoint(0, 10) << QPoint(-10, 0);
	PathVector rhombusGesture;
	rhombusGesture << rhombus;
	forms["rhombus"] = rhombusGesture;
	PointVector triangle;
	triangle << QPoint(-20, -20) << QPoint(0, 20)
		<< QPoint(20, -20) << QPoint(-20, -20);
	PathVector triangleGesture;
	triangleGesture << triangle;
	forms["triangle"] = triangleGesture;
	PointVector circle;
	double pi = 3.14;
	for (int i = 0; i <= 16; i ++) {
	  circle << QPoint(50 * cos(i * pi * 0.125), 50 * sin(i * pi * 0.125));
	}
	PathVector circleGesture;
	circleGesture << circle;
	forms["circle"] = circleGesture;
	PointVector acceptTimeEventAction;
	acceptTimeEventAction << QPoint(0, 0) << QPoint(100, 0) << QPoint(100, 60)
		<< QPoint(0, 60) << QPoint(15, 30) << QPoint(0, 0);
	PathVector acceptTimeEventActionPath;
	acceptTimeEventActionPath << acceptTimeEventAction;
	forms["acceptTimeEventAction"] = acceptTimeEventActionPath;
	PointVector sendSignalAction;
	sendSignalAction << QPoint(1, 1) << QPoint(84, 1) << QPoint(99, 30)
		<< QPoint(84, 59) << QPoint(1, 59) << QPoint(1, 1);
	PathVector sendSignalActionPath;
	sendSignalActionPath << sendSignalAction;
	forms["sendSignalAction"] = sendSignalActionPath;
	return forms;
}
