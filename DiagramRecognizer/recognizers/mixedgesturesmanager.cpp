#include "mixedgesturesmanager.h"
#include "rectanglegesturesmanager.h"
#include "nearestposgridgesturesmanager.h"
#include "curveKeyBuilder.h"

double const weight1 = 0.2;
double const weight2 = 1 - weight1;

MixedGesturesManager::MixedGesturesManager()
{
}

double MixedGesturesManager::maxDistance(QString const &) const
{
	return 1000;
}
bool MixedGesturesManager::isMultistroke() const
{
	return true;
}

double MixedGesturesManager::distance(QPair<double *,double *> const & key1,
		 MixedKey const & key2) const
{
	double dist1 =
		(new RectangleGesturesManager())->distance(key1.first, key2.first);
	double dist2 =
		(new NearestPosGridGesturesManager)->distance(key1.second, key2.second);
	return dist1 * weight1 + dist2 * weight2;
}

MixedKey MixedGesturesManager::key(
		PathVector const & path) const
{
	double * key1 = (new RectangleGesturesManager())->key(path);
	double * key2 = (new NearestPosGridGesturesManager)->key(path);
	return MixedKey(key1, key2);
}


