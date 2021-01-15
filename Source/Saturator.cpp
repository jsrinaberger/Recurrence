#include "Saturator.h"

Saturator::Saturator()
{
	mSaturationType = Analog;

	mDrive = 50;
	mTone = 50;
	mMix = 50;

	mIsActive = false;

	mSampleRate = 44100;
}

Saturator::Saturator(SaturationType saturationType, float drive, float tone, float mix, int sampleRate)
{
	mSaturationType = saturationType;

	mDrive = drive;
	mTone = tone;
	mMix = mix;

	mIsActive = false;

	mSampleRate = sampleRate;
}

void Saturator::setSaturationType(SaturationType saturationType)
{
	mSaturationType = saturationType;
}

void Saturator::setSaturationType(float* saturationType)
{
	mSaturationType = static_cast<SaturationType>((int)(*saturationType));
}

SaturationType Saturator::getSaturationType()
{
	return mSaturationType;
}

void Saturator::setDrive(float drive)
{
	mDrive = drive;
}

float Saturator::getDrive()
{
	return mDrive;
}

void Saturator::setTone(float tone)
{
	mTone = tone;
}

float Saturator::getTone()
{
	return mTone;
}

void Saturator::setMix(float mix)
{
	mMix = mix;
}

float Saturator::getMix()
{
	return mMix;
}

void Saturator::setIsActive(bool isActive)
{
	mIsActive = isActive;
}

bool Saturator::getIsActive()
{
	return mIsActive;
}

void Saturator::setSampleRate(int sampleRate)
{
	mSampleRate = sampleRate;
}

int Saturator::getSampleRate()
{
	return mSampleRate;
}

void Saturator::updateParameters(float* saturationType, float* drive, float* tone, float* mix, float* isActive)
{
	mSaturationType = static_cast<SaturationType>((int)(*saturationType));

	mDrive = *drive;
	mTone = *tone;
	mMix = *mix;

	mIsActive = *isActive > 0.5;
}

void Saturator::process(AudioBuffer<float>& buffer)
{

}
