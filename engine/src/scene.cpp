#include "scene.hpp"

using namespace engine;

Scene::Scene(){}

Scene::Scene(std::string sceneName){
	this->sceneName = sceneName;
}

void Scene::init(){
	for (auto eachKey : mKeyList){
		gameObjectMap[eachKey]->init();
	}
}

void Scene::shutdown(){
	for (auto eachKey : mKeyList){
		gameObjectMap[eachKey]->shutdown();
	}

	deleteKeyList();
}

void Scene::deleteKeyList(){
	mKeyList.erase(mKeyList.begin(), mKeyList.end());
}


void Scene::draw(){
	for (auto eachKey : mKeyList){
		if(gameObjectMap[eachKey]->mObjectState == ObjectState::ENABLED){
			gameObjectMap[eachKey]->draw();
		}
	}
}

void Scene::updateCode(){
	for(auto eachKey : mKeyList){
		if (gameObjectMap[eachKey]->mObjectState == ObjectState::ENABLED){
			gameObjectMap[eachKey]->updateCode();
		}
	}
}

void Scene::restart(){}

void Scene::addGameObject(GameObject &gameObject){
	auto gameObjectName = gameObject.mName;

	if (gameObjectMap.find(gameObjectName) != gameObjectMap.end()){
		ERROR("Game object already exists!");
	}

	gameObjectMap[gameObjectName] = &gameObject;
	mKeyList.push_back(gameObjectName);
}

GameObject & Scene::getGameObject(std::string &gameObjectName){
	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}

	return *gameObjectMap[gameObjectName];
}

void Scene::removeGameObject(std::string &gameObjectName){
	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	}
	
	gameObjectMap.erase(gameObjectName);
	mKeyList.remove(gameObjectName);
}
