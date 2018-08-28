#include "invisible_block.hpp"

using namespace Azo;

InvisibleBlock::InvisibleBlock(){}

InvisibleBlock::~InvisibleBlock(){}

InvisibleBlock::InvisibleBlock(std::string name, std::pair<double, double> positionRelativeToParent,
			       std::pair<double, double> size){
	DEBUG("Creating Blocks");

	mName = name;
	mPositionRelativeToParent = positionRelativeToParent;
	m_size = size;

	mHalfSize.first = m_size.first / 2.0f;
	mHalfSize.second = m_size.second / 2.0f;

	mCenter = mHalfSize;

	m_image =  new engine::ImageComponent(*this, "backgrounds/test_invisible_1.png", 1);
	this->AddComponent(*m_image);
}

void InvisibleBlock::shutDown(){
	m_image->shutDown();
	m_image = NULL;
}