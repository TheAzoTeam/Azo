#include "invisible_block.hpp"

using namespace Azo;

InvisibleBlock::InvisibleBlock(){}

InvisibleBlock::~InvisibleBlock(){}

InvisibleBlock::InvisibleBlock(std::string name, std::pair<double, double> position_relative_to_parent,
			       std::pair<double, double> size){
	DEBUG("Creating Blocks");

	mName = name;
	m_position_relative_to_parent = position_relative_to_parent;
	mSize = size;

	mHalfSize.first = mSize.first / 2.0f;
	mHalfSize.second = mSize.second / 2.0f;

	mCenter = mHalfSize;

	m_image =  new engine::ImageComponent(*this, "backgrounds/test_invisible_1.png", 1);
	this->addComponent(*m_image);
}

void InvisibleBlock::Shutdown(){
	m_image->Shutdown();
	m_image = NULL;
}