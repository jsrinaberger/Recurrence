#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

enum SaturationType {
	Analog = 0,
	SoftClip = 1,
	HardClip = 2
};

class Saturator
{
private:
	SaturationType mSaturationType;

	float mDrive;
	float mTone;
	float mMix;

	bool mIsActive;

	int mSampleRate;


public:

	Saturator();
	Saturator(SaturationType saturationType, float drive, float tone, float mix, int sampleRate);

	void setSaturationType(SaturationType saturationType);
	void setSaturationType(float* saturationType);
	SaturationType getSaturationType();

	void setDrive(float drive);
	float getDrive();

	void setTone(float tone);
	float getTone();

	void setMix(float mix);
	float getMix();

	void setIsActive(bool isActive);
	bool getIsActive();

	void setSampleRate(int sampleRate);
	int getSampleRate();

	void updateParameters(float* saturationType, float* drive, float* tone, float* mix, float* isActive);

	void process(AudioBuffer<float>& buffer);
};