#include "invisible_block.hpp"

using namespace Azo;

InvisibleBlock::InvisibleBlock(){}

InvisibleBlock::~InvisibleBlock(){}

InvisibleBlock::InvisibleBlock(std::string name, std::pair<double, double> positionRelativeToParent,
			       std::pair<double, double> size){
	DEBUG("Creating Blocks");

	mName = name;
	mPositionRelativeToParent = positionRelativeToParent;
	mSize = size;

	mHalfSize.first = mSize.first / 2.0f;
	mHalfSize.second = mSize.second / 2.0f;

	mCenter = mHalfSize;

	m_image =  new engine::ImageComponent(*this, "backgrounds/test_invisible_1.png", 1);
	this->addComponent(*m_image);
}

void InvisibleBlock::shutdown(){
	m_image->shutdown();
	m_image = NULL;
}