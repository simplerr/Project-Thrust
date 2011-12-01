#ifndef KEYFRAMES_H
#define KEYFRAMES_H

#include <string>
#include <vector>
#include "Vector.h"
#include "Enums.h"
using namespace std;

struct Keyframe
{
	Keyframe::Keyframe()	{
		time = UNDEFINED;
		rotation = UNDEFINED;
		scale = UNDEFINED;
		pos = Vector(UNDEFINED, UNDEFINED);
	}
	float time;
	float rotation;
	float scale;
	Vector pos;
};

class KeyAnimation
{
public:
	KeyAnimation(string sourceFile, string animation);
	~KeyAnimation();

	void loadAnimation();
	void start();
	bool interpolate(float dt);

	void	setLength(float length);
	float	getRotation();
	float	getScale();
	Vector	getMovement();
	float	getElapsed();
	float	getLength();
private:
	vector<Keyframe> mKeyframes;
	string mFile;
	string mAnimation;
	float  mLength;
	float  mElapsed;
	Vector mLastPos;
};

#endif