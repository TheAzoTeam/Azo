#include "level_one.hpp"

using namespace Azo;

LevelOne::LevelOne() {}

LevelOne::LevelOne(std::string name) {
	this->scene_name = name;

	CreateGameObjects();
}

void LevelOne::Restart() {
	gameObjectMap.clear();

	/*TODO(Roger): Add objects to be recreated one by one,
	here, instead of recalling CreateGameObjects.*/
	CreateGameObjects();

}

// Create new game objects for the level one here. Remember:
// the order used to add they to the scene is important.
void LevelOne::CreateGameObjects() {
	DEBUG("Creating Level One Game Objects.");

	DEBUG("Creating level_one object.");
	mLevelOne = new engine::GameObject("level_one", std::make_pair(0, 0));

	mLevelBackground1 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_one.png", 1);
	mLevelOne->AddComponent(*mLevelBackground1);

	mLevelBackground2 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_two.png", 1, std::make_pair(8188, 0));
	mLevelOne->AddComponent(*mLevelBackground2);

	mLevelBackground3 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_three.png", 1, std::make_pair(16379, 0));
	mLevelOne->AddComponent(*mLevelBackground3);

	mAudioController = new engine::AudioController();
	mLevelTheme = new engine::AudioComponent(*mLevelOne, "audios/banjo.ogg", true, true);
	mAudioController->AddAudio("tema_level_one", *mLevelTheme);
	mLevelOne->AddComponent(*mAudioController);

	this->AddGameObject(*mLevelOne);



	DEBUG("Creating ground.");
	mGround = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->AddGameObject(*mGround);


	DEBUG("Creating obstacle car 1.");
	mObstacleCar1 = new Obstacle("obstacle_car_1", std::make_pair(1135, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*mObstacleCar1);


	DEBUG("Creating spike 1.");
	mSpike1 = new Obstacle("obstacle_spike_1", std::make_pair(1349, 340), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*mSpike1);


	DEBUG("Creating obstacle box 0_1.");
	mObstacleBox01 = new Obstacle("obstacle_box_0_1", std::make_pair(1309, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox01);


	DEBUG("Creating obstacle aerial 1 - box.");
	mObstacleAerial1 = new Obstacle("obstacle_aerial_1", std::make_pair(1350, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial1);


	DEBUG("Creating part 1.");
	mPart1 = new Obstacle("part_1", std::make_pair(1500, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart1);


	DEBUG("Creating obstacle aerial 2 - post.");
	mObstacleAerial2 = new Obstacle("obstacle_aerial_2", std::make_pair(1755, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial2);


	DEBUG("Creating part 1_1.");
	mPart1_1 = new Obstacle("part_1_1", std::make_pair(1890, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart1_1);


	DEBUG("Creating obstacle aerial 3 - post.");
	mObstacleAerial3 = new Obstacle("obstacle_aerial_3", std::make_pair(2030, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial3);


	DEBUG("Creating part 2.");
	mPart2 = new Obstacle("part_2", std::make_pair(2225, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart2);


	DEBUG("Creating obstacle box 1.");
	mObstacleBox1 = new Obstacle("obstacle_box_1", std::make_pair(2225, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox1);


	DEBUG("Creating obstacle box 2.");
	mObstacleBox2 = new Obstacle("obstacle_box_2", std::make_pair(2645, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox2);


	DEBUG("Creating obstacle box 2_1.");
	mObstacleBox21 = new Obstacle("obstacle_box_2_1", std::make_pair(2779, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox21);


	DEBUG("Creating obstacle aerial 4 - box.");
	mObstacleAerial4 = new Obstacle("obstacle_aerial_4", std::make_pair(2820, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial4);


	DEBUG("Creating part 3.")
	mPart3 = new Obstacle("part_3", std::make_pair(2975, 310), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart3);


	DEBUG("Creating obstacle car 2.");
	mObstacleCar2 = new Obstacle("obstacle_car_2", std::make_pair(3040, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*mObstacleCar2);


	DEBUG("Creating part 4.");
	mPart4 = new Obstacle("part_4", std::make_pair(3285, 100), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart4);


	DEBUG("Creating obstacle aerial 5 - post.");
	mObstacleAerial5 = new Obstacle("obstacle_aerial_5", std::make_pair(3510, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial5);


	DEBUG("Creating part 4_1.");
	mPart41 = new Obstacle("part_4_1", std::make_pair(3655, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart41);


	DEBUG("Creating obstacle aerial 6 - post.");
	mObstacleAerial6 = new Obstacle("obstacle_aerial_6", std::make_pair(3675, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial6);


	DEBUG("Creating part 5.");
	mPart5 = new Obstacle("part_5", std::make_pair(3975, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart5);


	DEBUG("Creating obstacle box 3.");
	mObstacleBox3 = new Obstacle("obstacle_box_3", std::make_pair(3975, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox3);


	DEBUG("Creating obstacle rock 1");
	mObstacleRock1 = new Obstacle("obstacle_rock_1", std::make_pair(4300, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock1);


	DEBUG("Creating part 6.");
	mPart6 = new Obstacle("part_6", std::make_pair(4460, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart6);


	DEBUG("Creating obstacle aerial 7 - post.");
	mObstacleAerial7 = new Obstacle("obstacle_aerial_7", std::make_pair(4660, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial7);


	DEBUG("Creating obstacle rock 2");
	mObstacleRock2 = new Obstacle("obstacle_rock_2", std::make_pair(4855, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock2);


	DEBUG("Creating part 7.");
	mPart7 = new Obstacle("part_7", std::make_pair(5015, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart7);


	DEBUG("Creating obstacle aerial 8 - post.");
	mObstacleAerial8 = new Obstacle("obstacle_aerial_8", std::make_pair(5215, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial8);


	DEBUG("Creating part 7_1.");
	mPart7_1 = new Obstacle("part_7_1", std::make_pair(5360, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart7_1);


	DEBUG("Creating obstacle aerial 9 - post.");
	mObstacleAerial9 = new Obstacle("obstacle_aerial_9", std::make_pair(5380, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial9);


	DEBUG("Creating part 8.");
	mPart8 = new Obstacle("part_8", std::make_pair(5570, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart8);


	DEBUG("Creating part 9.");
	mPart9 = new Obstacle("part_9", std::make_pair(6100, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart9);


	DEBUG("Creating obstacle aerial 10 - post.");
	mObstacleAerial10 = new Obstacle("obstacle_aerial_10", std::make_pair(6150, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial10);


	DEBUG("Creating part 10.");
	mPart10 = new Obstacle("part_10", std::make_pair(6340, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart10);


	DEBUG("Creating obstacle car 3.");
	mObstacleCar3 = new Obstacle("obstacle_car_3", std::make_pair(6700, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*mObstacleCar3);


	DEBUG("Creating part 11.");
	mPart11 = new Obstacle("part_11", std::make_pair(6890, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart11);


	DEBUG("Creating obstacle aerial 11 - post.");
	mObstacleAerial11 = new Obstacle("obstacle_aerial_11", std::make_pair(7005, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial11);


	DEBUG("Creating part 12.");
	mPart12 = new Obstacle("part_12", std::make_pair(7160, 370), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart12);


	DEBUG("Creating obstacle aerial 12 - post.");
	mObstacleAerial12 = new Obstacle("obstacle_aerial_12", std::make_pair(7180, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial12);


	DEBUG("Creating part 13.");
	mPart13 = new Obstacle("part_13", std::make_pair(7540, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart13);


	DEBUG("Creating part 14.");
	mPart14 = new Obstacle("part_14", std::make_pair(7830, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart14);


	DEBUG("Creating part 15.");
	mPart15 = new Obstacle("part_15", std::make_pair(8040, 220), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart15);


	DEBUG("Creating part 16.");
	mPart16 = new Obstacle("part_16", std::make_pair(8390, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart16);


	DEBUG("Creating obstacle aerial 13 - post.");
	mObstacleAerial13 = new Obstacle("obstacle_aerial_13", std::make_pair(8570, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial13);


	DEBUG("Creating spike 2.");
	mSpike2 = new Obstacle("obstacle_spike_2", std::make_pair(8880, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*mSpike2);


	DEBUG("Creating obstacle box 4.");
	mObstacleBox4 = new Obstacle("obstacle_box_4", std::make_pair(8820, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox4);


	DEBUG("Creating spike 3.");
	mSpike3 = new Obstacle("obstacle_spike_3", std::make_pair(9120, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*mSpike3);


	DEBUG("Creating obstacle box 5.");
	mObstacleBox5 = new Obstacle("obstacle_box_5", std::make_pair(9117, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleBox5);


	DEBUG("Creating spike 4.");
	mSpike4 = new Obstacle("obstacle_spike_4", std::make_pair(9360, 330), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*mSpike4);


	DEBUG("Creating obstacle box 6.");
	mObstacleBox6 = new Obstacle("obstacle_box_6", std::make_pair(9358, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleBox6);


	DEBUG("Creating obstacle aerial 14 - box.");
	mObstacleAerial14 = new Obstacle("obstacle_aerial_14", std::make_pair(9358, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial14);


	DEBUG("Creating obstacle box 7.");
	mObstacleBox7 = new Obstacle("obstacle_box_7", std::make_pair(9599, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleBox7);


	DEBUG("Creating obstacle aerial 15 - box.");
	mObstacleAerial15 = new Obstacle("obstacle_aerial_15", std::make_pair(9599, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial15);


	DEBUG("Creating part 17.");
	mPart17 = new Obstacle("part_17", std::make_pair(9770, 350), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart17);


	DEBUG("Creating obstacle rock 3");
	mObstacleRock3 = new Obstacle("obstacle_rock_3", std::make_pair(10070, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock3);


	DEBUG("Creating obstacle box 8.");
	mObstacleBox8 = new Obstacle("obstacle_box_8", std::make_pair(10480, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox8);


	DEBUG("Creating part 18.");
	mPart18 = new Obstacle("part_18", std::make_pair(10560, 200), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart18);


	DEBUG("Creating obstacle aerial 16 - post.");
	mObstacleAerial16 = new Obstacle("obstacle_aerial_16", std::make_pair(10730, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial16);


	DEBUG("Creating obstacle rock 4");
	mObstacleRock4 = new Obstacle("obstacle_rock_4", std::make_pair(10930, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock4);


	DEBUG("Creating obstacle rock 5");
	mObstacleRock5 = new Obstacle("obstacle_rock_5", std::make_pair(11180, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock5);


	DEBUG("Creating obstacle aerial 17 - post.");
	mObstacleAerial17 = new Obstacle("obstacle_aerial_17", std::make_pair(11465, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial17);


	DEBUG("Creating obstacle box 9.");
	mObstacleBox9 = new Obstacle("obstacle_box_9", std::make_pair(11850, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox9);


	DEBUG("Creating obstacle box 10.");
	mObstacleBox10 = new Obstacle("obstacle_box_10", std::make_pair(11984, 300), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox10);


	DEBUG("Creating obstacle aerial 18 - box.");
	mObstacleAerial18 = new Obstacle("obstacle_aerial_18", std::make_pair(12025, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial18);


	DEBUG("Creating part 19.");
	mPart19 = new Obstacle("part_19", std::make_pair(12180, 340), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart19);


	DEBUG("Creating obstacle aerial 19 - post.");
	mObstacleAerial19 = new Obstacle("obstacle_aerial_19", std::make_pair(12370, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial19);


	DEBUG("Creating obstacle rock 6");
	mObstacleRock6 = new Obstacle("obstacle_rock_6", std::make_pair(12600, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock6);


	DEBUG("Creating obstacle rock 7");
	mObstacleRock7 = new Obstacle("obstacle_rock_7", std::make_pair(12850, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock7);


	DEBUG("Creating obstacle rock 8");
	mObstacleRock8 = new Obstacle("obstacle_rock_8", std::make_pair(13100, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock8);


	DEBUG("Creating obstacle car 4.");
	mObstacleCar4 = new Obstacle("obstacle_car_4", std::make_pair(13570, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*mObstacleCar4);


	DEBUG("Creating part 20.");
	mPart20 = new Obstacle("part_20", std::make_pair(13860, 70), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart20);


	DEBUG("Creating obstacle car 5.");
	mObstacleCar5 = new Obstacle("obstacle_car_5", std::make_pair(14200, 300), ObstacleType::WESTERN_CAR);
	this->AddGameObject(*mObstacleCar5);


	DEBUG("Creating spike 5.");
	mSpike5 = new Obstacle("obstacle_spike_5", std::make_pair(14414, 340), ObstacleType::WESTERN_SPIKE);
	this->AddGameObject(*mSpike5);


	DEBUG("Creating obstacle box 11.");
	mObstacleBox11 = new Obstacle("obstacle_box_11", std::make_pair(14374, 310), ObstacleType::WESTERN_BOX);
	this->AddGameObject(*mObstacleBox11);


	DEBUG("Creating obstacle aerial 20 - box.");
	mObstacleAerial20 = new Obstacle("obstacle_aerial_20", std::make_pair(14415, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->AddGameObject(*mObstacleAerial20);


	DEBUG("Creating part 21.");
	mPart21 = new Obstacle("part_21", std::make_pair(14565, 80), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart21);


	DEBUG("Creating obstacle aerial 21 - post.");
	mObstacleAerial21 = new Obstacle("obstacle_aerial_21", std::make_pair(14820, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial21);


	DEBUG("Creating obstacle rock 9");
	mObstacleRock9 = new Obstacle("obstacle_rock_9", std::make_pair(15000, 340), ObstacleType::WESTERN_ROCK);
	this->AddGameObject(*mObstacleRock9);


	DEBUG("Creating obstacle aerial 22 - post.");
	mObstacleAerial22 = new Obstacle("obstacle_aerial_22", std::make_pair(15300, 185), ObstacleType::WESTERN_POST);
	this->AddGameObject(*mObstacleAerial22);


	DEBUG("Creating part 22.");
	mPart22 = new Obstacle("part_22", std::make_pair(15530, 140), ObstacleType::MACHINE_PART);
	this->AddGameObject(*mPart22);


	DEBUG("Creating Player.");
	mPlayer = new Player("player", std::make_pair(165, 280));
	this->AddGameObject(*mPlayer);

	CreateEndingScreen();
	AddLevelParents();

	mLevelCode = new LevelOneCode(*mLevelOne);
	mLevelOne->AddComponent(*mLevelCode);

}

void LevelOne::CreateEndingScreen(){
	mWinningScreenObject = new engine::GameObject("winning_screen", std::make_pair(0, 0));
	mWinningScreenObject->m_object_state = engine::ObjectState::DISABLED;

	mWinningScreen = new engine::BackgroundComponent(*mWinningScreenObject, "general_images/tela_vitoria.png");

	mWinningScreenObject->AddComponent(*mWinningScreen);
	this->AddGameObject(*mWinningScreenObject);

	mLosingPartsScreenObject = new engine::GameObject("losing_parts", std::make_pair(0, 0));
	mLosingPartsScreenObject->m_object_state = engine::ObjectState::DISABLED;

	mLosingPartsScreen = new engine::BackgroundComponent(*mLosingPartsScreenObject, "general_images/tela_derrota.png");

	mLosingPartsScreenObject->AddComponent(*mLosingPartsScreen);
	this->AddGameObject(*mLosingPartsScreenObject);

	mLosingDeathScreenObject = new engine::GameObject("losing_death", std::make_pair(0, 0));
	mLosingDeathScreenObject->m_object_state = engine::ObjectState::DISABLED;

	mLosingDeathScreen = new engine::BackgroundComponent(*mLosingDeathScreenObject, "general_images/tela_morte.png");

	mLosingDeathScreenObject->AddComponent(*mLosingDeathScreen);
	this->AddGameObject(*mLosingDeathScreenObject);

	mArrow = new engine::GameObject("arrow", std::make_pair(0, 0));
	mArrow->m_object_state = engine::ObjectState::DISABLED;

	mArrowImage = new engine::ImageComponent(*mArrow, "general_images/arrow.png", 1);

	mArrow->AddComponent(*mArrowImage);
	this->AddGameObject(*mArrow);
}


void LevelOne::AddLevelParents() {
	DEBUG("Adding level parents.");
	mLevelOne->m_parent_list.push_back(mObstacleCar1);
	DEBUG ("A MERDA ROLOU AQUI! - 1");
	mLevelOne->m_parent_list.push_back(mObstacleAerial1);
	mLevelOne->m_parent_list.push_back(mObstacleBox01);
	mLevelOne->m_parent_list.push_back(mSpike1);
	mLevelOne->m_parent_list.push_back(mPart1);
	mLevelOne->m_parent_list.push_back(mObstacleAerial2);
	mLevelOne->m_parent_list.push_back(mPart1_1);
	mLevelOne->m_parent_list.push_back(mObstacleAerial3);
	mLevelOne->m_parent_list.push_back(mPart2);
	mLevelOne->m_parent_list.push_back(mObstacleBox1);
	mLevelOne->m_parent_list.push_back(mObstacleBox2);
	mLevelOne->m_parent_list.push_back(mObstacleAerial4);
	mLevelOne->m_parent_list.push_back(mObstacleBox21);
	mLevelOne->m_parent_list.push_back(mPart3);
	mLevelOne->m_parent_list.push_back(mObstacleCar2);
	mLevelOne->m_parent_list.push_back(mPart4);
	mLevelOne->m_parent_list.push_back(mObstacleAerial5);
	mLevelOne->m_parent_list.push_back(mPart41);
	mLevelOne->m_parent_list.push_back(mObstacleAerial6);
	mLevelOne->m_parent_list.push_back(mPart5);
	mLevelOne->m_parent_list.push_back(mObstacleBox3);
	mLevelOne->m_parent_list.push_back(mObstacleRock1);
	mLevelOne->m_parent_list.push_back(mPart6);
	DEBUG ("A MERDA ROLOU AQUI! - 2");
	mLevelOne->m_parent_list.push_back(mObstacleAerial7);
	mLevelOne->m_parent_list.push_back(mObstacleRock2);
	mLevelOne->m_parent_list.push_back(mPart7);
	mLevelOne->m_parent_list.push_back(mObstacleAerial8);
	mLevelOne->m_parent_list.push_back(mPart7_1);
	mLevelOne->m_parent_list.push_back(mObstacleAerial9);
	mLevelOne->m_parent_list.push_back(mPart8);
	mLevelOne->m_parent_list.push_back(mPart9);
	mLevelOne->m_parent_list.push_back(mObstacleAerial10);
	mLevelOne->m_parent_list.push_back(mPart10);
	mLevelOne->m_parent_list.push_back(mObstacleCar3);
	mLevelOne->m_parent_list.push_back(mPart11);
	mLevelOne->m_parent_list.push_back(mObstacleAerial11);
	mLevelOne->m_parent_list.push_back(mPart12);
	mLevelOne->m_parent_list.push_back(mObstacleAerial12);
	mLevelOne->m_parent_list.push_back(mPart13);
	mLevelOne->m_parent_list.push_back(mPart14);
	mLevelOne->m_parent_list.push_back(mPart15);
	mLevelOne->m_parent_list.push_back(mPart16);
	mLevelOne->m_parent_list.push_back(mObstacleAerial13);
	mLevelOne->m_parent_list.push_back(mSpike2);
	mLevelOne->m_parent_list.push_back(mObstacleBox4);
	mLevelOne->m_parent_list.push_back(mSpike3);
	mLevelOne->m_parent_list.push_back(mObstacleBox5);
	mLevelOne->m_parent_list.push_back(mSpike4);
	mLevelOne->m_parent_list.push_back(mObstacleBox6);
	mLevelOne->m_parent_list.push_back(mObstacleAerial14);
	mLevelOne->m_parent_list.push_back(mObstacleBox7);
	mLevelOne->m_parent_list.push_back(mObstacleAerial15);
	mLevelOne->m_parent_list.push_back(mPart17);
	mLevelOne->m_parent_list.push_back(mObstacleRock3);
	mLevelOne->m_parent_list.push_back(mObstacleBox8);
	mLevelOne->m_parent_list.push_back(mPart18);
	DEBUG ("A MERDA ROLOU AQUI! - 3");
	mLevelOne->m_parent_list.push_back(mObstacleAerial16);
	mLevelOne->m_parent_list.push_back(mObstacleRock4);
	mLevelOne->m_parent_list.push_back(mObstacleRock5);
	mLevelOne->m_parent_list.push_back(mObstacleAerial17);
	mLevelOne->m_parent_list.push_back(mObstacleBox9);
	mLevelOne->m_parent_list.push_back(mObstacleBox10);
	mLevelOne->m_parent_list.push_back(mObstacleAerial18);
	mLevelOne->m_parent_list.push_back(mPart19);
	mLevelOne->m_parent_list.push_back(mObstacleAerial19);
	mLevelOne->m_parent_list.push_back(mObstacleRock6);
	mLevelOne->m_parent_list.push_back(mObstacleRock7);
	mLevelOne->m_parent_list.push_back(mObstacleRock8);
	mLevelOne->m_parent_list.push_back(mObstacleCar4);
	mLevelOne->m_parent_list.push_back(mPart20);
	mLevelOne->m_parent_list.push_back(mObstacleCar5);
	DEBUG ("A MERDA ROLOU AQUI! - 4");
	mLevelOne->m_parent_list.push_back(mObstacleAerial20);
	mLevelOne->m_parent_list.push_back(mObstacleBox11);
	mLevelOne->m_parent_list.push_back(mSpike5);
	mLevelOne->m_parent_list.push_back(mPart21);
	mLevelOne->m_parent_list.push_back(mObstacleAerial21);
	mLevelOne->m_parent_list.push_back(mObstacleRock9);
	mLevelOne->m_parent_list.push_back(mObstacleAerial22);
	mLevelOne->m_parent_list.push_back(mPart22);

	mLevelOne->m_parent_list.push_back(mWinningScreenObject);
	mLevelOne->m_parent_list.push_back(mLosingPartsScreenObject);
	mLevelOne->m_parent_list.push_back(mLosingDeathScreenObject);
	mLevelOne->m_parent_list.push_back(mArrow);

	mLevelOne->m_parent_list.push_back(mPlayer);
	mLevelOne->m_parent_list.push_back(mGround);
	DEBUG ("A MERDA ROLOU AQUI! - 5");
}
