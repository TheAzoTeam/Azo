#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "level_one_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class LevelOne : public engine::Scene {
		private:

			engine::BackgroundComponent *mWinningScreen;
			engine::BackgroundComponent *mLosingPartsScreen;
			engine::BackgroundComponent *mLosingDeathScreen;

			engine::GameObject *mWinningScreenObject;
			engine::GameObject *mLosingPartsScreenObject;
			engine::GameObject *mLosingDeathScreenObject;
			engine::GameObject *mArrow;
			engine::ImageComponent *mArrowImage;

			engine::ImageComponent *mLevelBackground1;
			engine::ImageComponent *mLevelBackground2;
			engine::ImageComponent *mLevelBackground3;

			/*This is the level game object.
			It contains things such as background, theme, etc.*/

			engine::GameObject *mLevelOne;

			// Add new components to level one here.

			engine::AudioController *mAudioController;
			engine::AudioComponent *mLevelTheme;
			LevelOneCode *mLevelCode;

			Player *mPlayer;

			// Add obstacles here
			Obstacle *mObstacleCar1;
			Obstacle *mSpike1;
			Obstacle *mObstacleAerial1;
			Obstacle *mPart1;
			Obstacle *mObstacleAerial2;
			Obstacle *mObstacleAerial3;
			Obstacle *mPart2;
			Obstacle *mObstacleBox1;
			Obstacle *mObstacleBox2;
			Obstacle *mObstacleAerial4;
			Obstacle *mPart3;
			Obstacle *mObstacleCar2;
			Obstacle *mPart4;
			Obstacle *mObstacleAerial5;
			Obstacle *mObstacleAerial6;
			Obstacle *mPart5;
			Obstacle *mObstacleBox3;
			Obstacle *mObstacleRock1;
			Obstacle *mPart6;
			Obstacle *mObstacleAerial7;
			Obstacle *mObstacleRock2;
			Obstacle *mPart7;
			Obstacle *mObstacleAerial8;
			Obstacle *mObstacleAerial9;
			Obstacle *mPart8;
			Obstacle *mPart1_1;
			Obstacle *mPart41;
			Obstacle *mPart7_1;
			Obstacle *mPart9;
			Obstacle *mObstacleAerial10;
			Obstacle *mPart10;
			Obstacle *mObstacleBox01;
			Obstacle *mObstacleBox21;
			Obstacle *mObstacleCar3;
			Obstacle *mPart11;
			Obstacle *mObstacleAerial11;
			Obstacle *mPart12;
			Obstacle *mObstacleAerial12;
			Obstacle *mPart13;
			Obstacle *mPart14;
			Obstacle *mPart15;
			Obstacle *mPart16;
			Obstacle *mObstacleAerial13;
			Obstacle *mSpike2;
			Obstacle *mObstacleBox4;
			Obstacle *mSpike3;
			Obstacle *mObstacleBox5;
			Obstacle *mSpike4;
			Obstacle *mObstacleBox6;
			Obstacle *mObstacleAerial14;
			Obstacle *mObstacleBox7;
			Obstacle *mObstacleAerial15;
			Obstacle *mPart17;
			Obstacle *mObstacleRock3;
			Obstacle *mObstacleBox8;
			Obstacle *mPart18;
			Obstacle *mObstacleAerial16;
			Obstacle *mObstacleRock4;
			Obstacle *mObstacleRock5;
			Obstacle *mObstacleAerial17;
			Obstacle *mObstacleBox9;
			Obstacle *mObstacleBox10;
			Obstacle *mObstacleAerial18;
			Obstacle *mObstacleAerial19;
			Obstacle *mPart19;
			Obstacle *mObstacleRock6;
			Obstacle *mObstacleRock7;
			Obstacle *mObstacleRock8;
			Obstacle *mObstacleCar4;
			Obstacle *mPart20;
			Obstacle *mObstacleCar5;
			Obstacle *mSpike5;
			Obstacle *mObstacleBox11;
			Obstacle *mObstacleAerial20;
			Obstacle *mPart21;
			Obstacle *mObstacleAerial21;
			Obstacle *mObstacleRock9;
			Obstacle *mObstacleAerial22;
			Obstacle *mPart22;
			Obstacle *mGround;

		private:
			//Don't forget to add the new objects using this function.
			void createGameObjects();
			void createEndingScreen();

			/*After adding things that collide (obstacles, for exemple),
			 add they as paren'ts here.*/

			void addLevelParents();
		public:
			LevelOne();
			LevelOne(std::string name);
			void restart();
	};
}

#endif
