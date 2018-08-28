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

GameObject::GameObject(std::string game_object_name, std::pair<double, double> current_position){
	this->mName = game_object_name;
	this->mCurrentPosition = current_position;
}

void GameObject::AddComponent(Component &component){
	std::pair <std::type_index, Component *> component_pair(typeid(component), &component);
	m_component_map.insert(component_pair);
}

AnimationController* GameObject::GetAnimationController(std::type_index component_type){
	auto component_to_be_found = m_component_map.find(component_type);

	if(component_to_be_found != m_component_map.end()){
		DEBUG("AnimationController found. Class name: " << component_to_be_found->second->getClassName());
		return dynamic_cast <AnimationController * > (component_to_be_found->second);
	}else{
		ERROR("Animation Controller couldn't be found!");
	}
}

AudioController* GameObject::getAudioController(std::type_index component_type){
	auto component_to_be_found = m_component_map.find(component_type);

	if(component_to_be_found != m_component_map.end()){
		DEBUG("AudioController found. Class name: " << component_to_be_found->second->getClassName());

		return dynamic_cast <AudioController * > (component_to_be_found->second);
	}else{
		ERROR("Audio Controller couldn't be found!");
	}
}

void GameObject::Init(){
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;
		if(component->IsEnabled()){
			component->Init();
		}
	}
}

void GameObject::Draw(){
	// DEBUG("GameObject::Draw method.");
	//DEBUG("Game object name: " << mName);
	// DEBUG("Map size: " << m_component_map.size());
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;

		ASSERT(component != NULL, "Component can't be NULL when drawing.");

		if(component->IsEnabled()){
			//	DEBUG("Drawing Component. Component Class Name: " << component->getClassName());
			component->Draw();
		}
	}

	//DEBUG("Finished Drawing.");
}

void GameObject::updateCode(){
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;
		if(component->IsEnabled()){
			component->updateCode();
		}
	}
}

void GameObject::Shutdown(){
	// for(auto each_pair : m_component_map){
	//      auto component = each_pair.second;
	//      component->Shutdown();
	// }
}

std::pair<double, double> GameObject::calcBottomLeft(){
	std::pair<double, double> bottom_left;
	bottom_left.first = mCenter.first - mHalfSize.first;
	bottom_left.second = mCenter.second + mHalfSize.second;
	return bottom_left;
}

std::pair<double, double> GameObject::CalcBottomRight(){
	std::pair<double, double> bottom_right;
	bottom_right.first = mCenter.first + mHalfSize.first;
	bottom_right.second = mCenter.second + mHalfSize.second;
	return bottom_right;
}

std::pair<double, double> GameObject::CalcTopLeft(){
	std::pair<double, double> top_left;
	top_left.first = mCenter.first - mHalfSize.first;
	top_left.second = mCenter.second - mHalfSize.second;
	return top_left;
}

std::pair<double, double> GameObject::calcTopRight(){
	std::pair<double, double> top_right;
	top_right.first = mCenter.first + mHalfSize.first;
	top_right.second = mCenter.second - mHalfSize.second;
	return top_right;
}

std::pair<double, double> GameObject::CalcRightUp(){
	return calcTopRight();
}

std::pair<double, double> GameObject::CalcRightDown(){
	return CalcBottomRight();
}

std::pair<double, double> GameObject::CalcLeftUp(){
	return CalcTopLeft();
}

std::pair<double, double> GameObject::CalcLeftDown(){
	return calcBottomLeft();
}
