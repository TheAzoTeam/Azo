#include "game_object.hpp"
#include "game.hpp"
#include "code_component.hpp"

using namespace engine;


GameObject::GameObject(){
	mCenter.first = 0;
	mCenter.second = 0;
	mHalfSize.first = 0;
	mHalfSize.second = 0;
}


GameObject::GameObject(std::string gameObjectName, std::pair<double, double> currentPosition){
	this->mName = gameObjectName;
	this->mCurrentPosition = currentPosition;
}


void GameObject::addComponent(Component &component){
	std::pair <std::type_index, Component *> componentPair(typeid(component), &component);
	mComponentMap.insert(componentPair);
}


AnimationController* GameObject::getAnimationController(std::type_index componentType){
	auto componentToBeFound = mComponentMap.find(componentType);

	if (componentToBeFound != mComponentMap.end()){
		DEBUG("AnimationController found. Class name: " << componentToBeFound->second->getClassName());
		return dynamic_cast <AnimationController * > (componentToBeFound->second);
	} else {
		ERROR("Animation Controller couldn't be found!");
	}
}


AudioController* GameObject::getAudioController(std::type_index componentType){
	auto componentToBeFound = mComponentMap.find(componentType);

	if (componentToBeFound != mComponentMap.end()){
		DEBUG("AudioController found. Class name: " << componentToBeFound->second->getClassName());

		return dynamic_cast <AudioController * > (componentToBeFound->second);
	} else {
		ERROR("Audio Controller couldn't be found!");
	}
}


void GameObject::init(){
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;
		if (component->isEnabled()){
			component->init();
		}
	}
}


void GameObject::draw(){
	// DEBUG("GameObject::draw method.");
	//DEBUG("Game object name: " << m_name);
	// DEBUG("Map size: " << m_component_map.size());
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;

		ASSERT(component != NULL, "Component can't be NULL when drawing.");

		if (component->isEnabled()){
			//	DEBUG("drawing Component. Component Class Name: " << component->GetClassName());
			component->draw();
		}
	}

	//DEBUG("Finished drawing.");
}


void GameObject::updateCode(){
	for (auto eachPair : mComponentMap){
		auto component = eachPair.second;
		if (component->isEnabled()){
			component->updateCode();
		}
	}
}


void GameObject::shutdown(){
	// for(auto each_pair : m_component_map){
	//      auto component = each_pair.second;
	//      component->shutdown();
	// }
}


std::pair<double, double> GameObject::calcBottomLeft(){
	std::pair<double, double> bottomLeft;
	bottomLeft.first = mCenter.first - mHalfSize.first;
	bottomLeft.second = mCenter.second + mHalfSize.second;
	return bottomLeft;
}


std::pair<double, double> GameObject::calcBottomRight(){
	std::pair<double, double> bottomRight;
	bottomRight.first = mCenter.first + mHalfSize.first;
	bottomRight.second = mCenter.second + mHalfSize.second;
	return bottomRight;
}


std::pair<double, double> GameObject::calcTopLeft(){
	std::pair<double, double> topLeft;
	topLeft.first = mCenter.first - mHalfSize.first;
	topLeft.second = mCenter.second - mHalfSize.second;
	return topLeft;
}


std::pair<double, double> GameObject::calcTopRight(){
	std::pair<double, double> topRight;
	topRight.first = mCenter.first + mHalfSize.first;
	topRight.second = mCenter.second - mHalfSize.second;
	return topRight;
}


std::pair<double, double> GameObject::calcRightUp(){
	return calcTopRight();
}


std::pair<double, double> GameObject::calcRightDown(){
	return calcBottomRight();
}


std::pair<double, double> GameObject::calcLeftUp(){
	return calcTopLeft();
}


std::pair<double, double> GameObject::calcLeftDown(){
	return calcBottomLeft();
}