#pragma once
#include "abstractRecognizer.h"
#include "geometricForms.h"

class MixedGesturesManager : public GesturesRecognizer<MixedKey>
{
public:
	MixedGesturesManager();
	double maxDistance(QString const &) const;
	bool isMultistroke() const;
	double distance(MixedKey const & key1,
		MixedKey const & key2) const;
	MixedKey key(PathVector const &path) const;
};

class MixedClassifier
{
public:
	MixedClassifier(const PathVector &path)
	{
		MixedGesturesManager gManager;
		mKey = gManager.key(path);
	}

	MixedClassifier(){}

	double distance(const MixedClassifier &classifier)
	{
		MixedKey key = classifier.key();
		MixedGesturesManager gManager;
		return gManager.distance(key, mKey);
	}
	MixedClassifier getPoint(MixedClassifier const & centre, double centreWeight)
	{
		double * key1 = centre.key().first;
		double * key2 = centre.key().second;
		double * finalKey1 = new double[gridSize * gridSize];
		double * finalKey2 = new double[gridSize * gridSize];
		for (int i = 0; i < gridSize * gridSize; i ++)
		{
			finalKey1[i] = (key1[i] * centreWeight + mKey.first[i]) / (centreWeight + 1);
			finalKey2[i] = (key2[i] * centreWeight + mKey.second[i]) / (centreWeight + 1);
		}
		return MixedClassifier(MixedKey(finalKey1, finalKey2));
	}

	MixedKey key() const
	{
		return mKey;
	}

private:
	MixedClassifier(MixedKey const & key)
	{
		mKey = key;
	}
	MixedKey mKey;
};
