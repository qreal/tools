#include "simpleformsinitializer.h"
#include "QMap"

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
	return forms;
}
