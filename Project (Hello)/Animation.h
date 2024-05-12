#pragma once

#include <vector>

struct FrameData {
	int id;
	int x;
	int y;
	int width;
	int height;
	float displayTimeSeconds;
};

class Animation
{
public:
	Animation();

	void addFrame(int textureID, int x, int y,
				  int width, int height, float ft);

	const FrameData* getCurrentFrame() const;

	bool updateFrame(float dt);

	/*
		When we transition to an animation 
		e.g: from IDLE to WALK
	*/
	void reset();

private:
	void incrementFrame();

	std::vector<FrameData> frames;
	int currentFrameIndex;
	float currentFrameTime;
};

