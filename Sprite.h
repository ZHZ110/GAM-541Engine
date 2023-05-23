#pragma once

#include <string>
#include "IComponent.h"

class Texture;

class Sprite : public IComponent {
public:
	Sprite(GameObject* parent);
	void registerComponent();
	const std::string& getName();
	std::string textureName;
	virtual void frameUpdate(float dt) {}
	Texture* getSpriteSource();
	void setSpriteSource(Texture* source);
	int getRows();
	int getCols();
	int getCurrFrame();
	int getTotalFrames();
	void setRows(int nRows);
	void setCols(int nCols);
	void setTotalFrames(int frameCount);
	void setCurrFrame(int currentFrame);
private:
	int numRows;
	int numCols;
	int currFrame;
	int totalFrames;
	Texture* spriteSource;
};