#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Narrative.h"

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
std::vector<Entity> players;
std::vector<std::shared_ptr<Enemy>> enemies;
std::vector<int> menuImages;
std::vector<std::shared_ptr<Map>> maps;
int activeMapIndex = 0;
bool menuActive = true;
bool playClicked = false;
bool creditsClicked = false;
bool exitClicked = false;
bool gameActive = false;
bool mute = false;
int activeMenuIndex = 0;
bool musicPlaying = false;
int activeNarrativeIndex = 0;
int activePlayerIndex = 0;
// Scale Position
float scaleX = 2.4;
float scaleY = 1.8;
int deathCounter = 0;
std::vector<std::shared_ptr<Narrative>> narratives;
std::unique_ptr<KalaJahangir> kalajahangir;
std::unique_ptr<KopaSamsu> kopasamsu;
bool kalaJahangirSpawned = false;
bool kopaSamsuSpawned = false;
bool jahangirDead = false;
bool kopaDead = false;
bool lvl1enemySpawned = false;
bool narrative2Active = false;
bool narrative3Active = false;
bool lvl1Completed = false;
bool lvl2Completed = false;
void playBGM()
{
	if (!mute && !musicPlaying)
	{
		PlaySound("music\\eot", NULL, SND_ASYNC | SND_LOOP);
		musicPlaying = true;
	}
	else if (mute)
	{
		PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
		musicPlaying = false;
	}
}





void checkMenu()
{
	if (activeMenuIndex == 0)
	{
		iShowImage(0, 0, 1920, 1080, menuImages[0]);
	}
	if (activeMenuIndex == 1)
	{
		iShowImage(0, 0, 1920, 1080, menuImages[1]);
	}
	if (activeMenuIndex == 2)
	{
		iShowImage(0, 0, 1920, 1080, menuImages[2]);
	}
	if (activeMenuIndex == 3)
	{
		iShowImage(0, 0, 1920, 1080, menuImages[3]);
	}
}

void iDraw() {
	iClear();
	if (menuActive) {
		checkMenu();
	}
	else if (narratives[activeNarrativeIndex]->narrativeActive) {
		maps[activeMapIndex]->render();
		players[activePlayerIndex].render();
		narratives[activeNarrativeIndex]->renderDialogue();
	}
	else if (gameActive) {
		maps[activeMapIndex]->render();
		players[activePlayerIndex].render();
		if (!enemies.empty())
		{
			for (auto& enemy : enemies) {
				if (!enemy->getDead())
					enemy->render();
			}
		}
		if (kalaJahangirSpawned)
		{
			kalajahangir->render();
		}
		if (kopaSamsuSpawned)
		{
			kopasamsu->render();
		}
	}
}







/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if ((mx > 360 * 2.4 && my > 388 * 1.8) && (mx < 440 * 2.4 && my < 406 * 1.8))
	{
		activeMenuIndex = 0;
	}
	else if ((mx > 323 * 2.4 && my > 309 * 1.8) && (mx < 470 * 2.4 && my < 331 * 1.8))
	{
		activeMenuIndex = 1;
	}
	else if ((mx > 357 * 2.4 && my > 232 * 1.8) && (mx < 440 * 2.4 && my < 255 * 1.8))
	{
		activeMenuIndex = 2;
	}
	else
	{
		activeMenuIndex = 3;
	}
}



void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if ((mx > 360 * 2.4 && my > 388 * 1.8) && (mx < 440 * 2.4 && my < 406 * 1.8) ||
			(mx > 323 * 2.4 && my > 309 * 1.8) && (mx < 470 * 2.4 && my < 331 * 1.8) ||
			(mx > 357 * 2.4 && my > 232 * 1.8) && (mx < 440 * 2.4 && my < 255 * 1.8) || ((mx > 56 * 2.4 && my > 72 * 1.8) && (mx <93 * 2.4 && my <100 * 1.8)))
		{
			PlaySound("music\\click", NULL, SND_ASYNC);
			musicPlaying = false;
		}
		if ((mx > 360 * 2.4 && my > 388 * 1.8) && (mx < 440 * 2.4 && my < 406 * 1.8))
		{
			menuActive = false;
			gameActive = true;
			musicPlaying = true;
		}
		std::cout << mx << "," << my << "\n";
		if ((mx > 56 * 2.4 && my > 72 * 1.8) && (mx < 93 * 2.4 && my < 100 * 1.8))
		{
			switch (mute)
			{
			case false:
				mute = true;
				std::cout << "muted sound\n";
				break;
			case true:
				mute = false;
				std::cout << "unmuted sound\n";
				break;
			}
		}
	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}

}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key) {
	if (narratives[activeNarrativeIndex]->narrativeActive)
	{
		if (key == ' ') // Spacebar advances the dialogue
		{
			narratives[activeNarrativeIndex]->nextDialogue();

			if (!narratives[activeNarrativeIndex]->narrativeActive)
			{
				gameActive = true; // Resume game after narrative ends
			}
		}
	}
	if (key >= '1' && key <= '4') {
		// Store the current player's position before switching
		const Pos currentPos = players[activePlayerIndex].getPosition();

		// Change active player
		const int newIndex = key - '1';

		// Set the new player's position to the last player's position
		players[newIndex].setPosition(currentPos.getX(), currentPos.getY());

		// Update the active player index
		activePlayerIndex = newIndex;
	}
}
/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/


void iSpecialKeyboard(unsigned char key) {
	if (!narratives[activeNarrativeIndex]->narrativeActive)
	{
		if (key == GLUT_KEY_RIGHT) {
			players[activePlayerIndex].moveRight();
		}
		else if (key == GLUT_KEY_LEFT) {
			players[activePlayerIndex].moveLeft();
		}
		if (key == GLUT_KEY_UP)
		{
			players[activePlayerIndex].jump(45.0f, 35.0f*1.8);
		}
		if (key == GLUT_KEY_HOME)
		{
			// Call attack on the active player
			players[activePlayerIndex].attack();

			// Now check for collision with all enemies
			if (!enemies.empty())
			{
				for (auto& enemy : enemies) {
					if (players[activePlayerIndex].isColliding(*enemy)) {
						enemy->takeDamage(20);
						std::cout << "Player hit enemy\n";
					}
				}
			}
			if (narrative3Active)
			{
				if (!kalajahangir->isDead) {
					if (players[activePlayerIndex].isColliding(*kalajahangir))
					{
						kalajahangir->takeDamage(20);
					}
				}
			}
			if (kopasamsu && !kopasamsu->isDead)
			{
				if (players[activePlayerIndex].isColliding(*kopasamsu))
				{
					kopasamsu->takeDamage(25);
				}
			}
		}
	}
}

void keyUp(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT)
	{
		players[activePlayerIndex].stopMoving();
	}
}

void keyDown(int key, int x, int y)
{

}

void handleJahangir()
{
	kalajahangir->updateAnimation(0.08, players[activePlayerIndex]);
	kalajahangir->moveTowardsPlayer(players[activePlayerIndex].getPosition());
	kalajahangir->checkForAttack(players[activePlayerIndex]);

	if (kalajahangir->isDead)
	{
		std::vector<KalaJahangir> vec;
		vec.emplace_back(*kalajahangir);
		for (auto it = vec.begin(); it != vec.end();)
		{
			it = vec.erase(it);
		}
	}
}
void handleKopa()
{
	kopasamsu->updateAnimation(0.05, players[activePlayerIndex]);
	kopasamsu->moveTowardsPlayer(players[activePlayerIndex].getPosition());
	kopasamsu->checkForAttack(players[activePlayerIndex]);

	if (kopasamsu->isDead)
	{
		std::vector<KopaSamsu> vec;
		vec.emplace_back(*kopasamsu);
		for (auto it = vec.begin(); it != vec.end();)
		{
			it = vec.erase(it);
		}
	}
}

bool initMap2 = false;
bool lvl2Narrative1Active = false;
bool lvl2Narrative2Active = false;
bool lvl2Narrative3Active = false;
bool lvl2Narrative4Active = false;
void update() {
	playBGM();
	// Spawn enemies if narrative is active and they haven't been spawned yet
	if (narratives[activeNarrativeIndex]->narrativeActive && !lvl1enemySpawned) {
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(300 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeleton", 100, 2, true, 5, 15, 7, 115)); // Melee skeleton
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(500 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeleton", 100, 2, true, 5, 15, 7, 115));  // Ranged skeleton
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(700 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeleton", 100, 2, true, 5, 15, 7, 115)); // Melee skeleton
		lvl1enemySpawned = true;
	}

	// Update the player's animation
	players[activePlayerIndex].updateAnimation(0.1);

	// Iterate through all enemies (both melee and ranged)
	if (!narratives[activeNarrativeIndex]->narrativeActive)
	{
		if (!enemies.empty())
		{
			for (auto& enemy : enemies) {
				if (!enemy->getDead()) {
					// Update animation for both melee and ranged enemies
					enemy->updateAnimation(0.1, players[activePlayerIndex]);

					// Move towards the player
					enemy->moveTowardsPlayer(players[activePlayerIndex].getPosition());

					if (enemy->isRanged) {
						// Handle ranged attack
						enemy->rangedAttack(0.016);
						enemy->updateProjectiles(players[activePlayerIndex]);
					}
					else {
						// Handle melee attack
						enemy->checkForAttack(players[activePlayerIndex]);
					}
				}

				// Count deaths
				if (enemy->getDead() && !enemy->deathCounted) {
					deathCounter++;
					enemy->deathCounted = true;
				}
			}
		}
	}

	// Print total kills
	std::cout << "Total enemies killed : " << deathCounter << std::endl;
	//LEVEL, WAVE HANDLING STARTS FROM HERE
	if (deathCounter >= 3 && !narrative2Active)
	{
		narrative2Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative2();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(400 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeletonmelee", 100, 2, false, 6, 4, 15, 163, 3, 5));
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(600 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeletonmelee", 100, 2, false, 6, 4, 15, 163, 3, 5));
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(200 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8), "res/skeletonmelee", 100, 2, false, 6, 4, 15, 163, 3, 5));
	}
	if (deathCounter >= 6 && !narrative3Active)
	{
		narrative3Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative3();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);

		// Update after adding to ensure it always remains valid
		activeNarrativeIndex = narratives.size() - 1;
		if (!kalajahangir) {
			kalajahangir = std::make_unique<KalaJahangir>("Enforcer", Pos(400 * 2.4, 150 * 1.8),
				Dim(128 * 2.4, 128 * 1.8), "res/kalajahangir",
				100, 2, false, 4, 6, 15, 154, 5, 15, 10);
			kalaJahangirSpawned = true;
		}
		std::cout << "Kala Jahangir spawn position: " << kalajahangir->getPosition().getX() << ", " << kalajahangir->getPosition().getY() << std::endl;
	}
	if (kalajahangir && !kalajahangir->isDead && !narratives[activeNarrativeIndex]->narrativeActive)
	{
		handleJahangir();
	}
	else if (kalajahangir->isDead && !lvl1Completed)
	{
		lvl1Completed = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative4();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		for (auto& player : players) player.reset();
	}

	if (lvl1Completed && !initMap2)
	{
		initMap2 = true;
		maps.emplace_back(std::make_shared<Map>("Level2", "res/maps/lvl2.png"));
		activeMapIndex++;
		deathCounter = 0;
	}
	if (initMap2 && !lvl2Narrative1Active)
	{
		lvl2Narrative1Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel2Narrative1();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		enemies.emplace_back(std::make_unique<Enemy>("Enforcer", Pos(300 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
			"res/Satyr", 100, 2, false, 12, 4, 12, 58, 3, 5));
		enemies.emplace_back(std::make_unique<Enemy>("Enforcer", Pos(200 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
			"res/Satyr", 100, 2, false, 12, 4, 12, 58, 3, 5));
		enemies.emplace_back(std::make_unique<Enemy>("Enforcer", Pos(100 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
			"res/Satyr", 100, 2, false, 12, 4, 12, 58, 3, 5));
	}
	if (initMap2 && deathCounter >= 3)
	{
		if (!lvl2Narrative2Active)
		{
			lvl2Narrative2Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel2Narrative2();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(100 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
				"res/SatyrRanged", 100, 2, true, 12, 4, 7, 58, 3, 5));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(700 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
				"res/SatyrRanged", 100, 2, true, 12, 4, 7, 58, 3, 5));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(400 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 1.8),
				"res/SatyrRanged", 100, 2, true, 12, 4, 7, 58, 3, 5));
		}
	}
	if (initMap2 && deathCounter >= 6)
	{
		if (!lvl2Narrative3Active)
		{
			lvl2Narrative3Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel2Narrative3();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			kopasamsu = std::make_unique<KopaSamsu>("Enforcer", Pos(400 * 2.4, 150 * 1.8), Dim(128 * 2.4, 128 * 2.4), "res/kopasamsu", 100, 2, false, 12, 15, 6, 100, 9, 20, 22);
			kopaSamsuSpawned = true;
		}
	}
	if (kopasamsu && !kopasamsu->isDead && !narratives[activeNarrativeIndex]->narrativeActive)
	{
		handleKopa();
	}
	if (kopasamsu->isDead && !lvl2Completed)
	{
		lvl2Completed = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel2Narrative4();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		for (auto& player : players) player.reset();
	}
}


int main() {
	iSetTimer(100, update);
	iInitialize(1920, 1080, "Project Title");
	std::shared_ptr<Narrative> narrative = std::make_unique<Narrative>();
	maps.emplace_back(std::make_shared<Map>("Level1", "res/maps/lvl1.jpg"));
	players.emplace_back("Omee", Pos(100 * 2.4, 150 * 1.8), Dim(64 * 2.4, 64 * 1.8), "res/player1movement");
	players.emplace_back("Aiyan", Pos(100 * 2.4, 150 * 1.8), Dim(64 * 2.4, 64 * 1.8), "res/player2movement");
	players.emplace_back("Tirtha", Pos(100 * 2.4, 150 * 1.8), Dim(64 * 2.4, 64 * 1.8), "res/player3movement");
	players.emplace_back("Razi", Pos(100 * 2.4, 150 * 1.8), Dim(64 * 2.4, 64 * 1.8), "res/player4movement");
	menuImages.emplace_back(iLoadImage("res/playHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/creditsHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/exitHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/menu.png"));
	narrative->loadLevel1Narrative();
	narrative->narrativeActive = true; // Start the narrative
	narratives.emplace_back(narrative);
	glutSpecialUpFunc(keyUp);
	iStart();
	return 0;
}