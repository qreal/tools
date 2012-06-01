#pragma once
#include "GeometricForms.h"

class RecognizerInterface
{
public:
	virtual void setIdealGestures(const QList<Entity> & objects) = 0;
	virtual QString recognizeObject(PathVector const & gesture) = 0;
};
