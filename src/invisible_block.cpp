#include "invisible_block.hpp"

using namespace Azo;

InvisibleBlock::~InvisibleBlock(){}

InvisibleBlock::InvisibleBlock(std::string name, 
								std::pair<double, double> positionRelativeToParent,
			       				std::pair<double, double> size){
	DEBUG("Creating Blocks");

	mName = name;
	mPositionRelativeToParent = positionRelativeToParent;
	mSize = size;

	mHalfSize.first = mSize.first / 2.0f;
	mHalfSize.second = mSize.second / 2.0f;

	mCenter = mHalfSize;

	const std::string IMAGE_PATH = "backgrounds/test_invisible_1.png";
	const double ZOOM_FACTOR = 1;
	mImage =  new engine::ImageComponent(*this, IMAGE_PATH, ZOOM_FACTOR);
	this->addComponent(*mImage);
}

void InvisibleBlock::shutdown(){
	mImage->shutdown();
	mImage = NULL;
}