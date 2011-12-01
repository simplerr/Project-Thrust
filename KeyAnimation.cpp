#include <Windows.h>
#include "KeyAnimation.h"
#include "Enums.h"
#include "tinymxl\tinystr.h"
#include "tinymxl\tinyxml.h"

KeyAnimation::KeyAnimation(string sourceFile, string animation)
{
	setLength(2.0f);
	mFile = sourceFile;
	mAnimation = animation;
	mElapsed = 9999.0f;
	mLastPos = Vector(0, 0);
}
	
KeyAnimation::~KeyAnimation()
{

}

void KeyAnimation::start()
{
	mElapsed = 0.0f;
}
	
bool KeyAnimation::interpolate(float dt)
{
	if(mElapsed + (dt / mLength) < 1)	{	
		mElapsed += (dt / mLength);
		return true;
	}
	else
		return false;
}

void KeyAnimation::loadAnimation()
{
	// Load animation file
	TiXmlDocument document = TiXmlDocument(mFile.c_str());
	document.LoadFile();

	TiXmlElement* root = document.FirstChildElement();
	TiXmlElement* animation = root->FirstChildElement(mAnimation.c_str());

	// Get the animation length
	mLength = atof(animation->FirstChildElement("Length")->GetText());

	// Loop through all keyframes and load them into the keyframe list
	for(TiXmlElement* keyframe = animation->FirstChildElement("Keyframe"); keyframe != NULL; keyframe = keyframe->NextSiblingElement("Keyframe"))
	{
		// XML Elements
		TiXmlElement* rotationElement = keyframe->FirstChildElement("Rotation");
		TiXmlElement* scaleElement = keyframe->FirstChildElement("Scale");
		TiXmlElement* xElement = keyframe->FirstChildElement("X");
		TiXmlElement* yElement = keyframe->FirstChildElement("Y");

		// Get the keyframes time (0 - 1)
		Keyframe frame;
		frame.time = atof(keyframe->FirstAttribute()->Value());

		// Load attributes into the keyframe
		if(rotationElement != NULL)		
			frame.rotation = atof(rotationElement->GetText());

		if(scaleElement != NULL)
			frame.scale = atof(scaleElement->GetText());

		if(xElement != NULL)
			frame.pos.x = atof(xElement->GetText());

		if(yElement != NULL)
			frame.pos.y = atof(yElement->GetText());
		
		// Add the new keyframe to the list
		mKeyframes.push_back(frame);
	}
}

void KeyAnimation::setLength(float length)
{
	mLength = length;
}

float KeyAnimation::getRotation()
{
	// Find out which keyframes we're between
	Keyframe k1;
	Keyframe k2;

	// The first frame
	int i;
	for(i = mKeyframes.size()-1; i >= 0; i--)	{
		if(mElapsed >= mKeyframes[i].time && mKeyframes[i].rotation != UNDEFINED)	{
			k1 = mKeyframes[i];
			break;
		}
	}

	// The second frame
	for(int j = i+1; j < mKeyframes.size(); j++)	{
		if(mElapsed <= mKeyframes[j].time && mKeyframes[j].rotation != UNDEFINED)	{
			k2 = mKeyframes[j];
			break;
		}
	}

	// Elapsed time betweem the two found keyframes
	// How far we've come between k1 and k2 (percentage since the division)
	float diffTime = (mElapsed - k1.time) / (k2.time - k1.time);
	
	// Return the calculated rotation
	return k1.rotation + (k2.rotation - k1.rotation) * diffTime;
}
	
Vector KeyAnimation::getMovement()
{
	// Find out which keyframes we're between
	Keyframe k1;
	Keyframe k2;

	// The first frame
	int i;
	for(i = mKeyframes.size()-1; i >= 0; i--)	{
		if(mElapsed >= mKeyframes[i].time && mKeyframes[i].pos.x != UNDEFINED)	{
			k1 = mKeyframes[i];
			break;
		}
	}

	// The second frame
	for(int j = i+1; j < mKeyframes.size(); j++)	{
		if(mElapsed <= mKeyframes[j].time && mKeyframes[j].pos.x != UNDEFINED)	{
			k2 = mKeyframes[j];
			break;
		}
	}

	// Elapsed time betweem the two found keyframes
	// How far we've come between k1 and k2 (percentage since the division)
	float diffTime = (mElapsed - k1.time) / (k2.time - k1.time);
	
	// Return the calculated position
	Vector position;
	position.x  = k1.pos.x + (k2.pos.x - k1.pos.x) * diffTime;
	position.y  = k1.pos.y + (k2.pos.y - k1.pos.y) * diffTime;

	Vector movement = position - mLastPos;
	if(position.x > 90)
		int adas = 1;

	mLastPos = position;

	return movement;
}

float KeyAnimation::getScale()
{
	return 1.0f;
}

float KeyAnimation::getElapsed()
{
	return mElapsed;
}

float KeyAnimation::getLength()
{
	return mLength;
}