#pragma once
#include "abstractRecognizer.h"
#include "geometricForms.h"

class RectangleGesturesManager : public GesturesRecognizer<double *>
{
public:
	RectangleGesturesManager();
	double maxDistance(QString const &objectName) const;
	bool isMultistroke() const;
	double distance(double * const & key1, double * const & key2) const;
	double * key(PathVector const & path) const;
};
