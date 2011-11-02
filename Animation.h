#ifndef ANIMATION_H
#define ANIMATION_H

#include "d3dUtil.h"
#include "enums.h"
#include "Object.h"

/// All objects that should be animated should HAVE this class as a member
class Animation {
public:
	Animation(int frameWidth, int frameHeight, float timePerFrame, int totalFrames, int colums);
	~Animation();

	void animate(float dt);

	void pause()			{mPaused = true;}
	void resume()			{mPaused = false;}
	Rect getSourceRect()	{return mSourceRect;}

	void setFrame(int currentFrame);
private:
	Rect mSourceRect;

	int mFrameWidth;
	int mFrameHeight;
	int mCurrentFrame;
	int mTotalFrames;
	int mColums;
	float mTimePerFrame;
	float mDeltaSum;
	bool mPaused;
};	// Class

#endif