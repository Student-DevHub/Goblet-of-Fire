#include "Animation.h"

Animation::Animation()
	: frames(0), currentFrameIndex(0), currentFrameTime(0)
{
}

void Animation::addFrame(int textureID, int x, int y, int width, int height, float ft) {
	FrameData frame{ textureID, x, y, width, height, ft };
	frames.push_back(frame);
}

const FrameData* Animation::getCurrentFrame() const
{
	if (frames.size() > 0) {
		return &frames[currentFrameIndex];
	}
	return nullptr;
}

bool Animation::updateFrame(float dt)
{
	if (frames.size() <= 0) { return false; }

	currentFrameTime += dt;
	if (currentFrameTime >= frames[currentFrameIndex].displayTimeSeconds) {
		currentFrameTime = 0;
		incrementFrame();
		return true;
	}
	return false;
}

void Animation::reset()
{
	currentFrameIndex = 0;
	currentFrameTime = 0;
}

void Animation::incrementFrame()
{
	currentFrameIndex = (currentFrameIndex + 1) % frames.size();
}
