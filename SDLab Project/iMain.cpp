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
int gameOverSprite;
bool menuActive = true;
bool playClicked = false;
bool creditsClicked = false;
bool exitClicked = false;
bool gameActive = false;
bool mute = false;
int activeMenuIndex = 0;
bool gameOver = false;
bool musicPlaying = false;
bool gameEnd = false;
int activeNarrativeIndex = 0;
int activePlayerIndex = 0;
bool credsClicked = false;
int credsImage;
int gameEndSprite;
// Scale Position
float scaleX = 1;
float scaleY = 1;
int deathCounter = 0;
std::vector<std::shared_ptr<Narrative>> narratives;
std::unique_ptr<KalaJahangir> kalajahangir;
std::unique_ptr<KopaSamsu> kopasamsu;
std::unique_ptr<ChakkuMojumder> chakku;
std::unique_ptr<Boltu> boltu;
std::unique_ptr<Omega> omega;
bool kalaJahangirSpawned = false;
bool kopaSamsuSpawned = false;
bool jahangirDead = false;
bool kopaDead = false;
bool boltuChakkuSpawned = false;
bool omegaSpawned = false;
bool initMap3 = false;
bool lvl1enemySpawned = false;
bool narrative2Active = false;
bool narrative3Active = false;
bool lvl1Completed = false;
bool lvl2Completed = false;
bool initMap2 = false;
bool lvl1NarrativeAdded = false;
bool lvl2Narrative1Active = false;
bool lvl2Narrative2Active = false;
bool lvl2Narrative3Active = false;
bool lvl2Narrative4Active = false;
bool lvl3Narrative1Active = false;
bool lvl3Narrative2Active = false;
bool lvl3Narrative3Active = false;
bool lvl3Narrative4Active = false;
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
		iShowImage(0, 0, 800, 600, menuImages[0]);
	}
	if (activeMenuIndex == 1)
	{
		iShowImage(0, 0, 800, 600, menuImages[1]);
	}
	if (activeMenuIndex == 2)
	{
		iShowImage(0, 0, 800, 600, menuImages[2]);
	}
	if (activeMenuIndex == 3)
	{
		iShowImage(0, 0, 800, 600, menuImages[3]);
	}
}

void iDraw() {
	iClear();
	if (menuActive) {
		checkMenu();
		if (credsClicked)
		{
			iShowImage(0, 0, 800, 600, credsImage);
		}
	}
	else if (narratives[activeNarrativeIndex]->narrativeActive) {
		maps[activeMapIndex]->render();
		players[activePlayerIndex].render();
		narratives[activeNarrativeIndex]->renderDialogue();
	}
	else if (gameActive) {
		if (gameOver)
		{
			iShowImage(0, 0, 800, 600, gameOverSprite);
			return;
		}
		if (gameEnd)
		{
			iShowImage(0, 0, 800, 600, gameEndSprite);
			return;
		}
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
		if (boltu && chakku && boltuChakkuSpawned)
		{
			boltu->render();
			chakku->render();
		}
		if (omega && omegaSpawned)
		{
			omega->render();
		}
	}
}

void checkPlayerDeath()
{
	if (players[activePlayerIndex].isDead && activePlayerIndex != 3)
	{
		const Pos currentPos = players[activePlayerIndex].getPosition();
		players[activePlayerIndex].setPosition(currentPos.getX(),currentPos.getY());
		activePlayerIndex++;
	}
	else if (players[activePlayerIndex].isDead && activePlayerIndex == 3)
	{
		const Pos currentPos = players[activePlayerIndex].getPosition();
		players[activePlayerIndex].setPosition(currentPos.getX(), currentPos.getY());
		activePlayerIndex = 0;
	}
	if (players[0].isDead && players[1].isDead && players[2].isDead && players[3].isDead && !gameOver)
	{
		gameOver = true;
		PlaySound("Music/gameover", NULL, SND_ASYNC);
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
	if ((mx > 360 && my > 388) && (mx < 440  && my < 406 ))
	{
		activeMenuIndex = 0;
	}
	else if ((mx > 323  && my > 309 ) && (mx < 470  && my < 331 ))
	{
		activeMenuIndex = 1;
	}
	else if ((mx > 357 && my > 232 ) && (mx < 440  && my < 255 ))
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
		if ((mx > 360  && my > 388 ) && (mx < 440 * 1 && my < 406 * 1) ||
			(mx > 323 * 1 && my > 309 * 1) && (mx < 470 * 1 && my < 331 * 1) ||
			(mx > 357 * 1 && my > 232 * 1) && (mx < 440 * 1 && my < 255 * 1) || ((mx > 56 * 1 && my > 72 * 1) && (mx <93 * 1 && my <100 * 1)))
		{
			PlaySound("music\\click", NULL, SND_ASYNC);
			musicPlaying = false;
		}
		if ((mx > 360 * 1 && my > 388 * 1) && (mx < 440 * 1 && my < 406 * 1))
		{
			menuActive = false;
			gameActive = true;
			musicPlaying = true;
		}
		else if ((mx > 323 * 1 && my > 309 * 1) && (mx < 470 * 1 && my < 331 * 1))
		{
			credsClicked = true;
		}
		std::cout << mx << "," << my << "\n";
		if ((mx > 56 * 1 && my > 72 * 1) && (mx < 93 * 1 && my < 100 * 1))
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
	if (key == 27)
	{
		credsClicked = false;
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

bool attackPressed = false;
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
			players[activePlayerIndex].jump(45.0f, 35.0f*1);
		}
		if (key == GLUT_KEY_INSERT)
		{
			players[activePlayerIndex].isBlocking = true;
		}
		if (key == GLUT_KEY_HOME && !attackPressed && players[activePlayerIndex].attackTimer == 0)
		{
			attackPressed = true;
			// Call attack on the active player
			if (!players[activePlayerIndex].isRanged)
			{
				players[activePlayerIndex].attack();
			}
			else if (players[activePlayerIndex].isRanged) players[activePlayerIndex].shoot();
			// Now check for collision with all enemies
			if (!enemies.empty())
			{
				for (auto& enemy : enemies) {
					if (players[activePlayerIndex].isColliding(*enemy)) {
						if ((players[activePlayerIndex].name == "Omee" && enemy->name == "Shooter") || (players[activePlayerIndex].name == "Aiyan" && enemy->name == "Duelist") ||
							(players[activePlayerIndex].name == "Tirtha" && enemy->name == "Tactician") || (players[activePlayerIndex].name == "Razi" && enemy->name == "Enforcer"))
						{
							if (players[activePlayerIndex].fp() <= 100)
							players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 15);
							enemy->takeDamage(20);
						}
						else
						{
							if (players[activePlayerIndex].fp() <= 100)
							players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 5);
							enemy->takeDamage(5);
						}
						std::cout << "Player hit enemy\n";
					}
				}
			}
			if (narrative3Active)
			{
				if (!kalajahangir->isDead) {
					if (players[activePlayerIndex].isColliding(*kalajahangir))
					{
						if (players[activePlayerIndex].name == "Aiyan")
						{
							players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 25);
							kalajahangir->takeDamage(20);
						}
						else
						{
							players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 10);
							kalajahangir->takeDamage(1);
						}
					}
				}
			}
			if (kopasamsu && !kopasamsu->isDead)
			{
				if (players[activePlayerIndex].isColliding(*kopasamsu))
				{
					if (players[activePlayerIndex].name == "Razi")
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 25);
						kopasamsu->takeDamage(20);
					}
					else
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 10);
						kopasamsu->takeDamage(1);
					}
				}
			}
			if (chakku && !chakku->isDead)
			{
				if (players[activePlayerIndex].isColliding(*chakku))
				{
					if (players[activePlayerIndex].name == "Tirtha")
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 25);
						chakku->takeDamage(25);
					}
					else
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 10);
						chakku->takeDamage(2);
					}
				}
			}
			if (boltu && !boltu->isDead)
			{
				if (players[activePlayerIndex].isColliding(*boltu))
				{
					if (players[activePlayerIndex].name == "Omee")
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 25);
						boltu->takeDamage(25);
					}
					else
					{
						players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 10);
						boltu->takeDamage(3);
					}
				}
			}
			if (omega && !omega->isDead)
			{
				if (players[activePlayerIndex].isColliding(*omega))
				{
					players[activePlayerIndex].setFP(players[activePlayerIndex].fp() + 10);
					omega->takeDamage(3);
				}
			}
		}
		if (key == GLUT_KEY_END)
		{
			for (auto& enemy : enemies)
			{
				players[activePlayerIndex].specialAttack(*enemy);
			}
			if (kalajahangir && !kalajahangir->isDead)
			{
				players[activePlayerIndex].specialAttack(*kalajahangir);
			}
			if (kopasamsu && !kopasamsu->isDead)
			{
				players[activePlayerIndex].specialAttack(*kopasamsu);
			}
			if (chakku && !chakku->isDead)
			{
				players[activePlayerIndex].specialAttack(*chakku);
			}
			if (boltu && !boltu->isDead)
			{
				players[activePlayerIndex].specialAttack(*boltu);
			}
			if (omega && !omega->isDead)
			{
				players[activePlayerIndex].specialAttack(*omega);
			}
		}
	}
	if (gameOver)
	{
		if (key == GLUT_KEY_PAGE_DOWN)
		{
			gameOver = false;
			gameActive = false;
			menuActive = true;
		}
	}
}

void keyUp(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT || key == GLUT_KEY_INSERT)
	{
		players[activePlayerIndex].stopMoving();
	}
	if (key == GLUT_KEY_HOME) attackPressed = false;
}

void keyDown(int key, int x, int y)
{

}

void handleJahangir()
{
	kalajahangir->updateAnimation(0.06, players[activePlayerIndex]);
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
	kopasamsu->updateAnimation(0.02, players[activePlayerIndex]);
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
void handleChakku()
{
	chakku->updateAnimation(0.05, players[activePlayerIndex]);
	chakku->moveTowardsPlayer(players[activePlayerIndex].getPosition());
	chakku->checkForAttack(players[activePlayerIndex]);
}
void handleBoltu()
{
	boltu->updateAnimation(0.06, players[activePlayerIndex]);
	boltu->moveTowardsPlayer(players[activePlayerIndex].getPosition());
	boltu->rangedAttack(0.025);
	boltu->updateProjectiles(players[activePlayerIndex]);
}
void handleOmega()
{
	omega->updateAnimation(0.03, players[activePlayerIndex]);
	omega->moveTowardsPlayer(players[activePlayerIndex].getPosition());
	omega->checkForAttack(players[activePlayerIndex]);
}
bool initMap4 = false;
bool level4Narrative1Active = false;
bool lvl4Narrative2Active = false;
bool lvl4Narrative3Active = false;
bool lvl4Narrative4Active = false;
bool lastNarrative = false;

void update()
{
	if (gameOver)
	{
		return;
	}
	playBGM();
	if (!lvl1NarrativeAdded)
	{
		lvl1NarrativeAdded = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative();
		narrative->narrativeActive = true; // Start the narrative
		narratives.emplace_back(narrative);
	}

	// Spawn enemies if narrative is active and they haven't been spawned yet
	if (narratives[activeNarrativeIndex]->narrativeActive && !lvl1enemySpawned) {
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeleton", 100, 2, true, 5, 15, "music/skeleton",7, 48)); // Melee skeleton
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(500 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeleton", 100, 2, true, 5, 15, "music/skeleton",7, 48));  // Ranged skeleton
		enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(700 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeleton", 100, 2, true, 5, 15, "music/skeleton",7, 48)); // Melee skeleton
		lvl1enemySpawned = true;
	}

	// Update the player's animation
	players[activePlayerIndex].updateAnimation(0.1);

	// Update player projectiles
	for (auto& projectile : players[activePlayerIndex].projectiles) {
		if (!projectile.isActive) continue; // Skip inactive projectiles

		// Check for collisions with all alive enemies
		bool collisionOccurred = false;

		// Check collisions with regular enemies
		for (auto& enemy : enemies) {
			if (enemy->getDead()) continue; // Skip dead enemies

			if (enemy->checkProjectileCollisions({ projectile }, players[activePlayerIndex])) {
				collisionOccurred = true;
				break; // Stop checking other enemies if a collision occurred
			}
		}

		// Check collisions with kalajahangir (if it exists and is alive)
		if (kalajahangir && !kalajahangir->getDead()) {
			if (kalajahangir->checkProjectileCollisions({ projectile }, players[activePlayerIndex])) {
				collisionOccurred = true;
			}
		}
		if (kopasamsu && !kopasamsu->getDead()) {
			if (kopasamsu->checkProjectileCollisions({ projectile }, players[activePlayerIndex])) {
				collisionOccurred = true;
			}
		}
		if (chakku && !chakku->getDead()) {
			if (chakku->checkProjectileCollisions({ projectile }, players[activePlayerIndex])) {
				collisionOccurred = true;
			}
		}
		if (boltu && !boltu->getDead()) {
			if (boltu->checkProjectileCollisions({ projectile }, players[activePlayerIndex])) {
				collisionOccurred = true;
			}
		}
		if (omega && !omega->getDead())
		{
			if (omega->checkProjectileCollisions({projectile}, players[activePlayerIndex]))
			{
				collisionOccurred = true;
			}
		}
		// Deactivate the projectile if it collided with an alive enemy or kalajahangir
		if (collisionOccurred) {
			projectile.isActive = false;
		}
	}

	// Iterate through all enemies (both melee and ranged)
	if (!narratives[activeNarrativeIndex]->narrativeActive) {
		if (!enemies.empty()) {
			for (auto& enemy : enemies) {
				if (!enemy->getDead()) {
					// Update animation for both melee and ranged enemies
					enemy->updateAnimation(0.06, players[activePlayerIndex]);

					// Move towards the player
					enemy->moveTowardsPlayer(players[activePlayerIndex].getPosition());

					if (enemy->isRanged) {
						// Handle ranged attack
						enemy->rangedAttack(0.025);
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

	// LEVEL, WAVE HANDLING STARTS FROM HERE
	if (deathCounter >= 3 && !narrative2Active) {
		narrative2Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative2();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(400 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeletonmelee", 100, 2, false, 6, 4, "music/spear",15, 68, 3, 5));
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(600 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeletonmelee", 100, 2, false, 6, 4,"music/spear", 15, 68, 3, 5));
		enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeletonmelee", 100, 2, false, 6, 4, "music/spear",15, 68, 3, 5));
	}

	if (deathCounter >= 6 && !narrative3Active) {
		narrative3Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative3();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);

		// Update after adding to ensure it always remains valid
		activeNarrativeIndex = narratives.size() - 1;
		if (!kalajahangir) {
			kalajahangir = std::make_unique<KalaJahangir>("Enforcer", Pos(400 * 1, 150 * 1),
				Dim(128 * 1, 128 * 1), "res/kalajahangir",
				100, 2, false, 4, 6, 15, 64, 1, 15, 10,"music/jahangir");
			kalaJahangirSpawned = true;
		}
		std::cout << "Kala Jahangir spawn position: " << kalajahangir->getPosition().getX() << ", " << kalajahangir->getPosition().getY() << std::endl;
	}

	if (kalajahangir && !kalajahangir->isDead && !narratives[activeNarrativeIndex]->narrativeActive) {
		handleJahangir();
	}
	else if (kalajahangir->isDead && !lvl1Completed) {
		lvl1Completed = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel1Narrative4();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		for (auto& player : players) player.reset();
	}

	if (lvl1Completed && !initMap2 && !narratives[activeNarrativeIndex]->narrativeActive) {
		initMap2 = true;
		maps.emplace_back(std::make_shared<Map>("Level2", "res/maps/lvl2.png"));
		activeMapIndex++;
		deathCounter = 0;
	}

	if (initMap2 && !lvl2Narrative1Active) {
		lvl2Narrative1Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel2Narrative1();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
			"res/Satyr", 100, 2, false, 12, 4, "music/Satyr",12, 58, 3, 5));
		enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
			"res/Satyr", 100, 2, false, 12, 4, "music/Satyr",12, 58, 3, 5));
		enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(100 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
			"res/Satyr", 100, 2, false, 12, 4, "music/Satyr",12, 58, 3, 5));
	}
	if (initMap2 && deathCounter >= 3) {
		if (!lvl2Narrative2Active) {
			lvl2Narrative2Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel2Narrative2();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(100 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/SatyrRanged", 100, 2, true, 12, 4, "music/Satyr", 7, 58, 3, 5));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(700 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/SatyrRanged", 100, 2, true, 12, 4, "music/Satyr", 7, 58, 3, 5));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(400 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/SatyrRanged", 100, 2, true, 12, 4, "music/Satyr", 7, 58, 3, 5));
		}
	}

	if (initMap2 && deathCounter >= 6) {
		if (!lvl2Narrative3Active) {
			lvl2Narrative3Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel2Narrative3();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			kopasamsu = std::make_unique<KopaSamsu>("Enforcer", Pos(400 * 1, 150 * 1), Dim(256 * 1, 256 * 1), "res/kopasamsu", 100, 2, false, 12, 15, 6, 100, 9, 20, 22,"Music/kopa");
			kopaSamsuSpawned = true;
		}
	}

	if (kopasamsu && !kopasamsu->isDead && !narratives[activeNarrativeIndex]->narrativeActive) {
		handleKopa();
	}

	if (kopasamsu->isDead && !lvl2Completed) {
		lvl2Completed = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel2Narrative4();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		for (auto& player : players) player.reset();
	}

	if (lvl2Completed && !initMap3 && !narratives[activeNarrativeIndex]->narrativeActive) {
		initMap3 = true;
		maps.emplace_back(std::make_shared<Map>("Level3", "res/maps/lvl3.png"));
		activeMapIndex++;
		deathCounter = 0;
	}
	if (initMap3 && !lvl3Narrative1Active)
	{
		lvl3Narrative1Active = true;
		std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
		narrative->loadLevel3Narrative1();
		narrative->narrativeActive = true;
		narratives.emplace_back(narrative);
		activeNarrativeIndex++;
		enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(100 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
			"res/Ogre", 100, 6, false, 6, 12, "Music/ogre",6, 77, 9, 10));
		enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(500 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
			"res/wizard", 100, 2, true, 6, 4, "Music/borka",7, 77, 3, 8));
	}
	if (initMap3 && deathCounter >= 2)
	{
		if (!lvl3Narrative2Active)
		{
			lvl3Narrative2Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel3Narrative2();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(100 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/wizard", 100, 2, true, 6, 4, "Music/borka", 7, 77, 3, 8));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/wizard", 100, 2, true, 6, 4, "Music/borka", 7, 77, 3, 8));
			enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/wizard", 100, 2, true, 6, 4, "Music/borka", 7, 77, 3, 8));
			enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(400 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/Ogre", 100, 6, false, 6, 12, "Music/ogre", 6, 77, 9, 10));
			enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(500 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/Ogre", 100, 6, false, 6, 12, "Music/ogre", 6, 77, 9, 10));
		}
		if (initMap3 && deathCounter >= 7)
		{
			if (!lvl3Narrative3Active)
			{
				lvl3Narrative3Active = true;
				std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
				narrative->loadLevel3Narrative3();
				narrative->narrativeActive = true;
				narratives.emplace_back(narrative);
				activeNarrativeIndex++;
				chakku = std::make_unique<ChakkuMojumder>("Duelist", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/chakkumojumder", 100, 4, false, 8, 10, 15, 74,
					3, 15, 10,"Music/chakku");
				boltu = std::make_unique<Boltu>("Tactician", Pos(500 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/Boltu", 100, 4, true, 4, 8, 20, 60,
					3, 15, 7,"Music/boltu");
				boltuChakkuSpawned = true;
			}
			if (chakku && !chakku->isDead && !narratives[activeNarrativeIndex]->narrativeActive)
			{
				handleChakku();
			}
			if (boltu && !boltu->isDead && !narratives[activeNarrativeIndex]->narrativeActive)
			{
				handleBoltu();
			}
		}
		if (initMap3 && boltu->isDead && chakku->isDead && !lvl3Narrative4Active)
		{
			lvl3Narrative4Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel3Narrative4();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			for (auto& player : players) player.reset();
		}
		if (lvl3Narrative4Active && !narratives[activeNarrativeIndex]->narrativeActive && !initMap4)
		{
			initMap4 = true;
			maps.emplace_back(std::make_shared<Map>("Level4", "res/maps/lvl4.png"));
			activeMapIndex++;
			deathCounter = 0;
		}
		if (initMap4 && !level4Narrative1Active)
		{
			level4Narrative1Active = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLevel4Narrative1();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
			enemies.emplace_back(std::make_unique<Enemy>("Duelist", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/kalajahangir", 
				100, 8, false, 4, 6, "music/jahangir", 100, 2, 5));
			enemies.push_back(std::make_unique<Enemy>("Duelist", Pos(400 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
				"res/skeletonmelee", 100, 2, false, 6, 4, "music/spear", 15, 163, 3, 5));
			enemies.push_back(std::make_unique<Enemy>("Shooter", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/skeleton", 100, 2, true, 
				5, 15, "music/skeleton", 7, 115)); // Melee skeleton
		}
		if (initMap4 && deathCounter >= 3)
		{
			if (!lvl4Narrative2Active)
			{
				lvl4Narrative2Active = true;
				std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
				narrative->loadLevel4Narrative2();
				narrative->narrativeActive = true;
				narratives.emplace_back(narrative);
				activeNarrativeIndex++;
				enemies.emplace_back(std::make_unique<Enemy>("Enforcer", Pos(200 * 1, 150 * 1), Dim(256 * 1, 256 * 1), "res/kopasamsu",
					100, 8, false, 4, 6, "music/kopa", 100, 2, 5));
				enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(100 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/SatyrRanged", 100, 2, true, 12, 4, "music/Satyr", 7, 58, 3, 5));
				enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/Satyr", 100, 2, false, 12, 4, "music/Satyr", 12, 58, 3, 5));
			}
		}
		if (initMap4 && deathCounter >= 6)
		{
			if (!lvl4Narrative3Active)
			{
				lvl4Narrative3Active = true;
				std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
				narrative->loadLevel4Narrative3();
				narrative->narrativeActive = true;
				narratives.emplace_back(narrative);
				activeNarrativeIndex++;
				enemies.emplace_back(std::make_unique<Enemy>("Duelist", Pos(200 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/chakkumojumder",
					100, 8, false, 4, 6, "music/chakku", 100, 2, 5));
				enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(400 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/boltu",
					100, 8, true, 4, 6, "music/boltu", 100, 2, 5));
				enemies.emplace_back(std::make_unique<Enemy>("Shooter", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/wizard", 100, 2, true, 6, 4, "Music/borka", 7, 77, 3, 8));
				enemies.emplace_back(std::make_unique<Enemy>("Tactician", Pos(500 * 1, 150 * 1), Dim(128 * 1, 128 * 1),
					"res/Ogre", 100, 6, false, 6, 12, "Music/ogre", 6, 77, 9, 10));
			}
		}
		if (initMap4 && deathCounter >= 10)
		{
			if (!lvl4Narrative4Active)
			{
				lvl4Narrative4Active = true;
				std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
				narrative->loadLevel4Narrative4();
				narrative->narrativeActive = true;
				narratives.emplace_back(narrative);
				activeNarrativeIndex++;
				omega = std::make_unique<Omega>("Omega", Pos(300 * 1, 150 * 1), Dim(128 * 1, 128 * 1), "res/omega", 200, 15, false, 8,
					3, 6, 58, 1, 30, 6, "Music/omega");
				omegaSpawned = true;
			}
		}
		if (omega && omegaSpawned && !omega->isDead && !narratives[activeNarrativeIndex]->narrativeActive)
		{
			handleOmega();
		}
		if (omega && omega->isDead && !lastNarrative)
		{
			lastNarrative = true;
			std::shared_ptr<Narrative> narrative = std::make_shared<Narrative>();
			narrative->loadLastNarrative();
			narrative->narrativeActive = true;
			narratives.emplace_back(narrative);
			activeNarrativeIndex++;
		}
		if (lastNarrative && !narratives[activeNarrativeIndex]->narrativeActive && !gameEnd)
		{
			gameEnd = true;
			PlaySound("Music/gameEnd", NULL, SND_ASYNC | SND_LOOP);
		}
	}
}
void loadPlayersBlockSprites()
{
	players[0].blockSprite = iLoadImage("res/player1movement/block.png");
	players[1].blockSprite = iLoadImage("res/player2movement/block.png");
	players[2].blockSprite = iLoadImage("res/player3movement/block.png");
	players[3].blockSprite = iLoadImage("res/player4movement/block.png");
}

int main() {
	iSetTimer(100, update);
	iSetTimer(150, checkPlayerDeath);
	iInitialize(800, 600, "Project Title");
	std::shared_ptr<Narrative> narrative = std::make_unique<Narrative>();
	maps.emplace_back(std::make_shared<Map>("Level1", "res/maps/lvl1.jpg"));
	players.emplace_back("Omee", Pos(100 * 1, 150 * 1), Dim(64 * 1, 64 * 1), "res/player1movement");
	players.emplace_back("Aiyan", Pos(100 * 1, 150 * 1), Dim(64 * 1, 64 * 1), "res/player2movement");
	players.emplace_back("Tirtha", Pos(100 * 1, 150 * 1), Dim(64 * 1, 64 * 1), "res/player3movement");
	players.emplace_back("Razi", Pos(100 * 1, 150 * 1), Dim(64 * 1, 64 * 1), "res/player4movement");
	players[0].specialSprite = iLoadImage("res/player1movement/special.png");
	players[1].specialSprite = iLoadImage("res/player2movement/special.png");
	players[2].specialSprite = iLoadImage("res/player3movement/special.png");
	players[3].specialSprite = iLoadImage("res/player4movement/special.png");
	players[2].isRanged = true;
	players[3].isRanged = true;
	players[2].projectileSprite = iLoadImage("res/player3movement/projectile.png");
	players[3].projectileSprite = iLoadImage("res/player4movement/projectile.png");
	players[2].projectileSpeed = 180 * 1;
	players[3].projectileSpeed = 120 * 1;
	menuImages.emplace_back(iLoadImage("res/playHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/creditsHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/exitHighlight.png"));
	menuImages.emplace_back(iLoadImage("res/menu.png"));
	gameOverSprite = iLoadImage("res/gameOver.png");
	credsImage = iLoadImage("res/credits.png");
	gameEndSprite = iLoadImage("res/gameEndSprite.jpeg");
	loadPlayersBlockSprites();

	glutSpecialUpFunc(keyUp);
	iStart();
	return 0;
}