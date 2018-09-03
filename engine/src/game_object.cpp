#include "game_object.hpp"
#include "game.hpp"
#include "code_component.hpp"

using namespace engine;


GameObject::GameObject(){
	m_center.first = 0;
	m_center.second = 0;

	m_half_size.first = 0;
	m_half_size.second = 0;
}

GameObject::GameObject(std::string game_object_name, std::pair<double, double> current_position){
	this->m_name = game_object_name;
	this->m_current_position = current_position;
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

AudioController* GameObject::GetAudioController(std::type_index component_type){
	auto component_to_be_found = m_component_map.find(component_type);

	if(component_to_be_found != m_component_map.end()){
		DEBUG("AudioController found. Class name: " << component_to_be_found->second->getClassName());

		return dynamic_cast <AudioController * > (component_to_be_found->second);
	}else{
		ERROR("Audio Controller couldn't be found!");
	}
}

void GameObject::init(){
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;
		if(component->isEnabled()){
			component->init();
		}
	}
}

void GameObject::draw(){
	// DEBUG("GameObject::draw method.");
	//DEBUG("Game object name: " << m_name);
	// DEBUG("Map size: " << m_component_map.size());
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;

		ASSERT(component != NULL, "Component can't be NULL when drawing.");

		if(component->isEnabled()){
			//	DEBUG("Drawing Component. Component Class Name: " << component->getClassName());
			component->draw();
		}
	}

	//DEBUG("Finished Drawing.");
}

void GameObject::updateCode(){
	for(auto each_pair : m_component_map){
		auto component = each_pair.second;
		if(component->isEnabled()){
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

std::pair<double, double> GameObject::CalcBottomLeft(){
	std::pair<double, double> bottom_left;
	bottom_left.first = m_center.first - m_half_size.first;
	bottom_left.second = m_center.second + m_half_size.second;
	return bottom_left;
}

std::pair<double, double> GameObject::CalcBottomRight(){
	std::pair<double, double> bottom_right;
	bottom_right.first = m_center.first + m_half_size.first;
	bottom_right.second = m_center.second + m_half_size.second;
	return bottom_right;
}

std::pair<double, double> GameObject::CalcTopLeft(){
	std::pair<double, double> top_left;
	top_left.first = m_center.first - m_half_size.first;
	top_left.second = m_center.second - m_half_size.second;
	return top_left;
}

std::pair<double, double> GameObject::CalcTopRight(){
	std::pair<double, double> top_right;
	top_right.first = m_center.first + m_half_size.first;
	top_right.second = m_center.second - m_half_size.second;
	return top_right;
}

std::pair<double, double> GameObject::CalcRightUp(){
	return CalcTopRight();
}

std::pair<double, double> GameObject::CalcRightDown(){
	return CalcBottomRight();
}

std::pair<double, double> GameObject::CalcLeftUp(){
	return CalcTopLeft();
}

std::pair<double, double> GameObject::CalcLeftDown(){
	return CalcBottomLeft();
}
