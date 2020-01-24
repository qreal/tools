#include "nearestPosGridGesturesManager.h"
#include "curveKeyBuilder.h"
#include "stdlib.h"

NearestPosGridGesturesManager::NearestPosGridGesturesManager()
{
}

double NearestPosGridGesturesManager::maxDistance(QString const &) const
{
	return 1000;
}
bool NearestPosGridGesturesManager::isMultistroke() const
{
	return true;
}

double NearestPosGridGesturesManager::distance(double * const &key1,
		double * const &key2) const
{
	double norm = 0;
	double sum = 0;
	for (int i = 0; i < gridSize * gridSize; i ++) {
	  double dif = abs(key1[i] - key2[i]);
		sum += dif;
		norm = std::max(norm, dif);
	}
	//return norm / (gridSize * gridSize);
	return norm + sum / (gridSize * gridSize);
}

double * NearestPosGridGesturesManager::key(PathVector const &path) const
{
	Key key = KeyBuilder::key(path, gridSize, gridSize);
	double * finalKey = new double[gridSize * gridSize];
	for (int i = 0; i < gridSize * gridSize; i ++) {
		finalKey[i] = gridSize;
	}
	if (key.isEmpty()) {
		return finalKey;
	}
	for (int i = 0; i < gridSize; i ++) {
		for (int j = 0; j < gridSize; j ++) {
			double dist = abs(key.at(0).first - i) + abs(key.at(0).second - j);
			foreach (SquarePos const &pos, key) {
			  double norm = abs(pos.first - i) + abs(pos.second - j);
				dist = std::min(dist, norm);
			}
			finalKey[i * gridSize + j] = dist;
		}
	}
	return finalKey;
}


