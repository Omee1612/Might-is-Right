#include <algorithm>
#include <string>
#include <vector>
#include "iGraphics.h"
#include <cmath>
#include <thread>
#include <chrono>
class Pos {
private:
	int x, y;
public:
	Pos(int x = 0, int y = 0) : x(x), y(y) {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int newX) { x = newX; }
	void setY(int newY) { y = newY; }
};

class Dim {
private:
	int width, height;
public:
	Dim(int w = 0, int h = 0) : width(w), height(h) {}
	int getWidth() const { return width; }
	int getHeight() const { return height; }
};
class PlayerProjectile {
public:
	Pos position;
	Dim dimension;
	float velocityX;
	float velocityY;
	mutable bool isActive;
	int sprite;

	PlayerProjectile(Pos pos, Dim dim, float velX, float velY, int spr)
		: position(pos), dimension(dim), velocityX(velX), velocityY(velY), sprite(spr), isActive(true) {}

	void update(double deltaTime) {
		if (!isActive) return;

		position.setX(position.getX() + velocityX * deltaTime);
		position.setY(position.getY() + velocityY * deltaTime);

		// Deactivate the projectile if it goes off-screen
		if (position.getX() < 0 || position.getX() > 800 || position.getY() < 0 || position.getY() > 600) {
			isActive = false;
		}
	}

	void render() {
		if (!isActive) return;
		iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), sprite);
	}
};
class Entity {
protected:
	int FP = 0;
public:
	std::string name;
	std::string hitSoundPath;
	Pos position;
	double specialTimer = 0.0;
	int offSetX = 0;
	Dim dimension;
	bool facingRight = true;
	bool movingRight = true;
	bool jumping = false;
	bool isBlocking = false;
	std::vector<int> sprites;
	int walkIndex = 3;  // Default to idle
	int blockSprite;
	bool isIdle = true;
	bool isDead = false;
	bool isSpecial = false;
	int specialSprite;
	int specialWidth = 800;
	int specialHeight;
	int specialX = 100;
	int HP = 100;
	bool isJumping = false;
	bool isRanged = false; // Whether the entity is ranged
	float projectileSpeed = 50.0f*1; // Speed of the projectiles
	int projectileSprite; // Sprite for the projectile
	std::vector<PlayerProjectile> projectiles; // List of active projectiles
	float jumpVelocityX = 0.0f;
	float jumpVelocityY = 0.0f;
	float gravity = -30.5f;// Gravity force
	int groundY;            // Y-position of the ground
	int attackSprite;
	double attackTimer = 0.0;
	double attackDuration = 0.3f;
	bool isAttacking = false;
	Entity(std::string name, Pos pos, Dim dim, std::string folder, double attackDuration = 0.5, int offSetX = 0)
		: name(name), position(pos), dimension(dim) {
		loadWalkingSprites(folder);
		groundY = position.getY();
		this->offSetX = offSetX;
	}

	int fp() const
	{
		return FP;
	}
	void setFP(int FP)
	{
		this->FP = FP;
	}

	Entity(const Entity& other)
		: name(other.name),
		hitSoundPath(other.hitSoundPath),
		position(other.position),
		offSetX(other.offSetX),
		dimension(other.dimension),
		facingRight(other.facingRight),
		movingRight(other.movingRight),
		jumping(other.jumping),
		sprites(other.sprites),
		walkIndex(other.walkIndex),
		isIdle(other.isIdle),
		isAttacking(other.isAttacking),
		isDead(other.isDead),
		HP(other.HP),
		isJumping(other.isJumping),
		jumpVelocityX(other.jumpVelocityX),
		jumpVelocityY(other.jumpVelocityY),
		gravity(other.gravity),
		groundY(other.groundY),
		attackSprite(other.attackSprite),
		attackTimer(other.attackTimer),
		attackDuration(other.attackDuration)
	{
	}

	Entity(Entity&& other)
		: name(std::move(other.name)),
		hitSoundPath(std::move(other.hitSoundPath)),
		position(std::move(other.position)),
		offSetX(other.offSetX),
		dimension(std::move(other.dimension)),
		facingRight(other.facingRight),
		movingRight(other.movingRight),
		jumping(other.jumping),
		sprites(std::move(other.sprites)),
		walkIndex(other.walkIndex),
		isIdle(other.isIdle),
		isAttacking(other.isAttacking),
		isDead(other.isDead),
		HP(other.HP),
		isJumping(other.isJumping),
		jumpVelocityX(other.jumpVelocityX),
		jumpVelocityY(other.jumpVelocityY),
		gravity(other.gravity),
		groundY(other.groundY),
		attackSprite(other.attackSprite),
		attackTimer(other.attackTimer),
		attackDuration(other.attackDuration)
	{
	}

	Entity& operator=(const Entity& other)
	{
		if (this == &other)
			return *this;
		name = other.name;
		hitSoundPath = other.hitSoundPath;
		position = other.position;
		offSetX = other.offSetX;
		dimension = other.dimension;
		facingRight = other.facingRight;
		movingRight = other.movingRight;
		jumping = other.jumping;
		sprites = other.sprites;
		walkIndex = other.walkIndex;
		isIdle = other.isIdle;
		isAttacking = other.isAttacking;
		isDead = other.isDead;
		HP = other.HP;
		isJumping = other.isJumping;
		jumpVelocityX = other.jumpVelocityX;
		jumpVelocityY = other.jumpVelocityY;
		gravity = other.gravity;
		groundY = other.groundY;
		attackSprite = other.attackSprite;
		attackTimer = other.attackTimer;
		attackDuration = other.attackDuration;
		return *this;
	}
	void reset()
	{
		this->HP = 100;
		this->position.setX(200);
		this->facingRight = true;
		this->isDead = false;
	}
	bool getAttacking() { return isAttacking; }
	Entity& operator=(Entity&& other)
	{
		if (this == &other)
			return *this;
		name = std::move(other.name);
		hitSoundPath = std::move(other.hitSoundPath);
		position = std::move(other.position);
		offSetX = other.offSetX;
		dimension = std::move(other.dimension);
		facingRight = other.facingRight;
		movingRight = other.movingRight;
		jumping = other.jumping;
		sprites = std::move(other.sprites);
		walkIndex = other.walkIndex;
		isIdle = other.isIdle;
		isAttacking = other.isAttacking;
		isDead = other.isDead;
		HP = other.HP;
		isJumping = other.isJumping;
		jumpVelocityX = other.jumpVelocityX;
		jumpVelocityY = other.jumpVelocityY;
		gravity = other.gravity;
		groundY = other.groundY;
		attackSprite = other.attackSprite;
		attackTimer = other.attackTimer;
		attackDuration = other.attackDuration;
		return *this;
	}

	virtual ~Entity() = default;
	Dim getDim()
	{
		return dimension;
	}
	int getHealth()
	{
		return HP;
	}
	void loadWalkingSprites(std::string folder) {
		sprites.resize(4);
		std::string path;
		for (int i = 0; i < 4; i++) {
			if (i < 3)
				path = folder + "/RMove" + std::to_string(i) + ".png";
			else
				path = folder + "/Idle.png";
			sprites[i] = iLoadImage(const_cast<char*>(path.c_str()));
		}
		std::string filepath2 = folder + "/Attack.png";
		attackSprite = iLoadImage(const_cast<char*>(filepath2.c_str()));
		std::string soundPath = folder + "/Hit";
		hitSoundPath = soundPath;
	}

	virtual bool isColliding(Entity& other) {
		if (other.isDead) return false;

		// Get the other entity's position and dimensions
		float ex1 = other.position.getX();
		float ey1 = other.position.getY();
		float eWidth = other.dimension.getWidth();
		float eHeight = other.dimension.getHeight();

		// Adjust the collision box based on offsetX and facing direction
		if (other.facingRight) {
			ex1 += 0;
			eWidth -= 0;
		}
		else {
			eWidth -= 0;
		}

		// Get this entity's position and dimensions
		float x1 = position.getX();
		float y1 = position.getY();
		float width = dimension.getWidth();
		float height = dimension.getHeight();

		// Check for collision using AABB (Axis-Aligned Bounding Box) method
		return (x1 < ex1 + eWidth &&
			x1 + width > ex1 &&
			y1 < ey1 + eHeight &&
			y1 + height > ey1);
	}





	virtual void takeDamage(int amount)
	{
		if (isBlocking) amount = 0;
		if (HP - amount <= 0)
		{
			isDead = true;
			HP = 0;
			return;
		}
		HP -= amount;
	}
	void shoot() {
		if (!isRanged) return;

		// Calculate the projectile's starting position
		float startX = facingRight ? position.getX() + dimension.getWidth() : position.getX();
		float startY = position.getY() + dimension.getHeight() / 2;

		// Calculate the projectile's velocity
		float velX = facingRight ? projectileSpeed : -projectileSpeed;
		float velY = 0; // Adjust if you want arcing projectiles
		isAttacking = true;
		// Create a new projectile
		projectiles.emplace_back(Pos(startX, startY), Dim(32, 32), velX, velY, projectileSprite);
		playAttackSound();
	}
	Pos getPosition() const
	{
		return this->position;
	}
	void setPosition(int x, int y) {
		position.setX(x);
		position.setY(y);
	}
	bool getDead() const
	{
		return isDead;
	}

	virtual void render() {
		if (isDead) return;
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		iSetColor(0, 0, 255);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 50, 1 * FP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprite);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprite);
			}
		}
		else if (isBlocking)
		{
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), blockSprite);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), blockSprite);
			}
		}
		else if (facingRight) {
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), sprites[walkIndex]);
		}
		else {
			iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), sprites[walkIndex]);
		}
		for (auto& projectile : projectiles) {
			projectile.render();
		}
		if (isSpecial)
		{
			iShowImage(specialX, 125, 167, 125, specialSprite);
		}
	}
	void specialAttack(Entity& entity)
	{
		if (FP >= 100)
		{
			isSpecial = true;
			entity.takeDamage(30);
		}
	}
	virtual void updateAnimation(double deltaTime) {
		double specialTimerCooldown = 20.0;
		if (!isIdle) {
			walkIndex = (walkIndex + 1) % 3;
		}
		else {
			walkIndex = 3;
		}

		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false;
				attackTimer = 0.0;
			}
		}
		if (isSpecial)
		{
			FP = 0;
			specialTimer += 2.5;
			specialX += 200;
			if (specialTimer >= specialTimerCooldown)
			{
				specialX = 100;
				isSpecial = false;
				specialTimer = 0.0;
			}
		}
		if (isJumping) {
			// Continue the player's horizontal movement while jumping
			position.setX(position.getX() + jumpVelocityX);
			position.setY(position.getY() + jumpVelocityY);
			jumpVelocityY += gravity;

			// Clamp X position within screen bounds
			if (position.getX() < 0) {
				position.setX(0);
				jumpVelocityX = 0;  // Stop horizontal movement at the boundary
			}
			if (position.getX() + dimension.getWidth() > 800) {
				position.setX(800 - dimension.getWidth());
				jumpVelocityX = 0;  // Stop horizontal movement at the boundary
			}

			if (position.getY() <= groundY) {
				position.setY(groundY);
				isJumping = false;
			}
		}
		for (auto& projectile : projectiles) {
			projectile.update(deltaTime);
		}

		// Remove inactive projectiles
		projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
			[](const PlayerProjectile& p) { return !p.isActive; }), projectiles.end());
	}


	virtual void attack() {
		if (isDead) return;
		if (!isAttacking && !isBlocking) {
			isAttacking = true;
			playAttackSound();
			attackTimer = 0.0;
		}
	}

	void moveRight() {
		facingRight = true;
		movingRight = true;
		if (position.getX() + dimension.getWidth() < 800) {
			// Allow movement during jump
			if (!isJumping) {
				position.setX(position.getX() + 5 * 1);
			}
			isIdle = false;
		}
	}

	void moveLeft() {
		facingRight = false;
		movingRight = false;
		if (position.getX() > 0) {
			// Allow movement during jump
			if (!isJumping) {
				position.setX(position.getX() - 5 * 1);
			}
			isIdle = false;
		}
	}

	void setJumping(bool val)
	{
		isJumping = val;
	}

	void jump(float angle, float power) {
		if (!isJumping) {
			isJumping = true;
			const float radians = angle * (3.1416 / 180.0f);
			jumpVelocityX = power * cos(radians) * (movingRight ? 1 : -1); // Horizontal velocity is affected by movement direction
			jumpVelocityY = power * sin(radians);  // Vertical velocity
		}
	}




	void stopMoving() {
		isIdle = true;
		isBlocking = false;
		walkIndex = 3;
	}
	void playAttackSound()
	{
		PlaySound(hitSoundPath.c_str(), NULL, SND_ASYNC);
	}
};

class Map
{
private:
	std::string lvlName;
	Pos pos;
	Dim dim;
	int mapID;
	std::string mapPath;
	int victorySprite;
public:
	bool bossDefeated = false;
	Map(std::string lvlName, std::string mapPath) : lvlName(lvlName)
	{
		const Pos p(0, 0);
		this->pos = p;
		const Dim d(800, 600);
		this->dim = d;
		mapID = iLoadImage(const_cast<char*>(mapPath.c_str()));
	}
	void render() const
	{
		iShowImage(pos.getX(), pos.getY(), dim.getWidth(), dim.getHeight(), mapID);
	}
};


class Animation {
private:
	std::vector<std::string> frames; // Store animation frames
	int interval; // Time between frames (in milliseconds)
	std::chrono::steady_clock::time_point startTime; // Start time of animation
	bool isRunning; // Animation running state

public:
	// Constructor
	Animation(int intervalMs) : interval(intervalMs), isRunning(false) {}

	// Add a frame to the animation
	void addFrame(const std::string& frame) {
		frames.push_back(frame);
	}

	// Start the animation (record start time)
	void startAnimation() {
		if (!frames.empty()) {
			startTime = std::chrono::steady_clock::now();
			isRunning = true;
		}
	}

	// Stop/reset the animation (stops time tracking)
	void resetAnimation() {
		isRunning = false;
	}

	// Get the current frame based on elapsed time
	std::string getCurrentFrame() const {
		if (!isRunning || frames.empty()) {
			return "No animation running!";
		}

		// Calculate elapsed time since animation started
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

		// Determine the current frame index
		size_t frameIndex = (elapsed / interval) % frames.size();

		return frames[frameIndex];
	}
};

class Projectile {
private:
	int x, y;
	int speed;
	int sprite; // Single projectile image

public:
	Projectile(int x, int y, int speed, int sprite)
		: x(x), y(y), speed(speed), sprite(sprite) {
	}
	bool isColliding(Entity& target) {
		// If this projectile belongs to an enemy, it should not hit other enemies

		// Get the leftmost side of the projectileint projLeft = x;
		int projTop = y;
		int projBottom = y + 32 * 1;
		int projLeft = x;

		// Get the target entity's bounding box
		int targetLeft = target.getPosition().getX();
		int targetRight = targetLeft + target.getDim().getWidth();
		int targetTop = target.getPosition().getY();
		int targetBottom = targetTop + target.getDim().getHeight();

		// Check if the left side of the projectile is within the target's bounding box
		return (projLeft >= targetLeft && projLeft <= targetRight) &&
			(projTop <= targetBottom && projBottom >= targetTop);
	}
	void updatePosition() {
		x += speed;
	}

	bool isOutOfBounds() const {
		return (x < 0 || x > 800);
	}

	void render() {
		iShowImage(x, y, 32 * 1, 32 * 1, sprite); // Render the projectile
	}
};

class Enemy : public Entity {
public:
	int moveSpeed;
	std::vector<int> moveSprites;
	std::vector<int> attackSprites;
	std::vector<Projectile> projectiles; // Store projectiles

	int moveIndex;
	int attackIndex;
	float frameTime;
	float lastUpdatedTime;
	int damage;
	int totalWalkFrames;
	int totalAttackFrames;
	float shootCooldown = 0.5f;  // Adjust this value for the shooting delay
	float shootTimer = 0.0f;
	bool isMoving;
	bool isDead;
	bool isIdle;
	bool facingRight;
	std::string folder;
	int idleSprite;
	int attackIndexDmg;
	int projectileSprite; // Single projectile image
	bool isAttacking;
	bool deathCounted = false;
	bool isRanged;
	Enemy(std::string name, Pos pos, Dim dim, std::string folder, int hp, int speed, bool ranged, int totalWalkFrames, int totalAttackFrames, std::string soundPath, float attackDuration, int offSetX = 0, int attackIndexDmg = 0, int damage = 10)
		: Entity(name, pos, dim, folder, attackDuration), moveSpeed(speed), isMoving(true), isDead(false), isRanged(ranged), totalWalkFrames(totalWalkFrames), totalAttackFrames(totalAttackFrames), isIdle(false), isAttacking(false), facingRight(true) {
		loadEnemySprites(folder);
		this->HP = 100;
		this->attackIndexDmg = attackIndexDmg;
		this->offSetX = offSetX;
		this->hitSoundPath = soundPath;
		this->damage = damage;
	}
	void loadEnemySprites(std::string folder) {
		moveSprites.resize(totalWalkFrames);
		attackSprites.resize(totalAttackFrames);
		std::string path;

		// Load walking sprites
		for (int i = 0; i < totalWalkFrames; i++) {
			path = folder + "/Rmove" + std::to_string(i) + ".png";
			moveSprites[i] = iLoadImage(const_cast<char*>(path.c_str()));
		}

		// Load attack sprites
		for (int i = 0; i < totalAttackFrames; i++) {
			path = folder + "/Rattack" + std::to_string(i) + ".png";
			attackSprites[i] = iLoadImage(const_cast<char*>(path.c_str()));
		}

		// Load projectile sprite (only one)
		if (isRanged)
		{
			path = folder + "/Projectile.png";
			projectileSprite = iLoadImage(const_cast<char*>(path.c_str()));
		}

		// Load idle sprite
		path = folder + "/Idle.png";
		idleSprite = iLoadImage(const_cast<char*>(path.c_str()));
	}
	bool checkCollision(const Pos& pos1, const Dim& dim1, const Pos& pos2, const Dim& dim2) {
		// Adjust the collision box based on offsetX and facing direction
		if (isDead) return false;
		float adjustedX1 = pos1.getX();
		float adjustedWidth1 = dim1.getWidth();

		if (facingRight) {
			// If facing right, offsetX is added to the left side of the sprite
			adjustedX1 += 0;
			adjustedWidth1 -= 0;
		}
		else {
			// If facing left, offsetX is added to the right side of the sprite
			adjustedWidth1 -= 0;
		}

		// Perform collision detection with the adjusted collision box
		return (adjustedX1 < pos2.getX() + dim2.getWidth() &&
			adjustedX1 + adjustedWidth1 > pos2.getX() &&
			pos1.getY() < pos2.getY() + dim2.getHeight() &&
			pos1.getY() + dim1.getHeight() > pos2.getY());
	}
	bool checkProjectileCollisions(const std::vector<PlayerProjectile>& playerProjectiles, Entity& player) {
		if (isDead) return false; // Skip if the enemy is already dead

		for (const auto& projectile : playerProjectiles) {
			if (projectile.isActive && checkCollision(projectile.position, projectile.dimension, position, dimension)) {
				// Handle collision
				if ((player.name == "Tirtha" && name == "Tactician") || (player.name == "Razi" && name == "Enforcer"))
				{
					if (player.fp() <= 100)
						player.setFP(player.fp() + 15);
					takeDamage(20);
				}
				else
				{
					if (player.fp() <= 100)
						player.setFP(player.fp() + 5);
					takeDamage(5);
				}
				return true; // Indicate that a collision occurred
			}
		}
		return false; // No collision occurred
	}
	void moveTowardsPlayer(Pos playerPos) {
		if (isRanged) {
			// Update the enemy's facing direction based on player position
			if (playerPos.getX() > getPosition().getX()) {
				facingRight = true;
			}
			else {
				facingRight = false;
			}

			// Check if enemy is within range of the player (let’s say 50px)
			const float rangeThreshold = 50.0f;
			if (facingRight) {
				if (getPosition().getX() < playerPos.getX() - 200 * 1 - rangeThreshold) {
					moveRight();
					isMoving = true;  // Enemy is moving
					isIdle = false;   // Ensure the enemy is not idle
				}
				else {
					// Stop moving and idle
					isIdle = true;
					isMoving = false; // Stop the movement animation
				}
			}
			else {
				if (getPosition().getX() > playerPos.getX() + 400 * 1 + rangeThreshold) {
					moveLeft();
					isMoving = true;  // Enemy is moving
					isIdle = false;   // Ensure the enemy is not idle
				}
				else {
					// Stop moving and idle
					isIdle = true;
					isMoving = false; // Stop the movement animation
				}
			}
		}
		else {
			// Move towards player if melee
			if (getPosition().getX() < playerPos.getX() - 50.f) {
				facingRight = true;  // Make sure enemy faces right when moving right
				moveRight();
				isMoving = true;  // Enemy is moving
				isIdle = false;   // Ensure the enemy is not idle
			}
			else if (getPosition().getX() > playerPos.getX() + 50.f) {
				facingRight = false; // Make sure enemy faces left when moving left
				moveLeft();
				isMoving = true;  // Enemy is moving
				isIdle = false;   // Ensure the enemy is not idle
			}
			else {
				isIdle = true;    // If no movement is needed, set to idle
				isMoving = false; // Stop the movement animation
			}
		}
	}
	void rangedAttack(double deltaTime) {
		shootTimer += deltaTime;  // Increment shoot timer by deltaTime

		if (isRanged && !isAttacking && shootTimer >= shootCooldown) {
			isAttacking = true;
			attackIndex = 0;
			attackTimer = 0.0;

			// Create a new projectile based on the enemy's facing direction
			int projX = facingRight ? getPosition().getX() + dimension.getWidth() : getPosition().getX();
			int projSpeed = facingRight ? 21 * 1 : -21 * 1;  // Make the projectile move in the correct direction

			projectiles.emplace_back(projX, getPosition().getY() + 18 * 1, projSpeed, projectileSprite);

			shootTimer = 0.0f;  // Reset shoot timer after shooting
			PlaySound(hitSoundPath.c_str(), NULL, SND_ASYNC);
		}
	}
	void checkForAttack(Entity& player) {
		const float meleeAttackThreshold = 30.0f; // Minimum distance to trigger melee attack

		float distanceToPlayer = std::abs(getPosition().getX() - player.getPosition().getX());

		if (distanceToPlayer <= 70.0f * 1 && distanceToPlayer >= meleeAttackThreshold && !isAttacking) {
			attack();
		}
	}

	void attack() override {
		// Only initiate attack if not already attacking
		if (!isAttacking) {
			isAttacking = true;
			attackIndex = 0;   // Start from the first attack animation frame
			attackTimer = 0.0;  // Reset attack timer
			PlaySound(hitSoundPath.c_str(), NULL, SND_ASYNC);
		}
	}

	void updateProjectiles(Entity& player) {
		for (auto it = projectiles.begin(); it != projectiles.end();) {
			it->updatePosition();
			// Remove projectile if it goes off-screen
			if (it->isColliding(player))
			{
				player.takeDamage(damage);
				it = projectiles.erase(it);
				std::cout << "collision detected of projectile\n";
			}
			else if (it->isOutOfBounds()) {
				it = projectiles.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void renderProjectiles() {
		for (auto& proj : projectiles) {
			proj.render();
		}
	}

	virtual void updateAnimation(double deltaTime, Entity& player) {
		if (HP <= 0) isDead = true;
		if (isAttacking) {
			// Increment the attack timer to track the attack's duration
			attackTimer += deltaTime;

			// If the attack timer exceeds the attack duration, stop the attack
			if (attackTimer >= attackDuration) {
				isAttacking = false;  // End attack animation
				attackTimer = 0.0;    // Reset attack timer
			}

			// Update the attack animation index (loop through attack frames)
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);

			// Apply damage when attack reaches the frame where damage should be dealt
			if (attackIndex == attackIndexDmg) {
				if (isColliding(player)) {
					player.takeDamage(damage);  // Apply damage to the player (adjust damage as needed)
					std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
				}
			}
		}

		// Update movement animation
		if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to first walking frame if idle
		}
	}
	void render() override {
		if (isDead) return;

		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};
class KalaJahangir : public Enemy
{
public:
	std::vector<int> deathSprites;
	int deathSpritesSize;
	int deathSpriteIndex = 0;
	bool isDying = false;

	KalaJahangir(const std::string& name, const Pos& pos, const Dim& dim, const std::string& folder, int hp, int speed,
		bool ranged, int totalWalkFrames, int totalAttackFrames, float attackDuration, int offSetX, int attackIndexDmg,
		int damage, int death_sprites_size,std::string path)
		: Enemy(name, pos, dim, folder, hp, speed, ranged, totalWalkFrames, totalAttackFrames, path,attackDuration, offSetX,
		attackIndexDmg, damage),
		deathSpritesSize(death_sprites_size)
	{
		isDead = false;
		std::vector<int> deathS;
		for (int i = 0; i < 10; i++)
		{
			std::string path = "res/kalajahangir/death (" + std::to_string(i + 1) + ").png";
			deathS.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprites = deathS;
	}
	void takeDamage(int damage) override
	{
		HP -= damage;
		if (HP <= 0) {
			HP = 0;
			isDying = true;
		}
	}

	void updateAnimation(double deltaTime, Entity& player) override
	{
		if (isDying)
		{
			deathSpriteIndex = (deathSpriteIndex + 1) % deathSpritesSize;
			if (deathSpriteIndex == deathSpritesSize - 1) isDead = true;
			return;
		}

		// Check if the enemy is attacking
		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false; // End attack animation
				attackTimer = 0.0;
			}
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);
			if (attackIndex == attackIndexDmg && isColliding(player)) {
				player.takeDamage(damage); // Apply damage
				std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
			}
		}
		// Handle movement animation
		else if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to idle frame
		}
	}

	void render() override {
		if (isDead) return;
		if (isDying)
		{
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), deathSprites[deathSpriteIndex]);
			return;
		}
		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};

class KopaSamsu : public Enemy
{
public:
	std::vector<int> deathSprites;
	int deathSpritesSize;
	int deathSpriteIndex = 0;
	bool isDying = false;

	KopaSamsu(const std::string& name, const Pos& pos, const Dim& dim, const std::string& folder, int hp, int speed,
		bool ranged, int totalWalkFrames, int totalAttackFrames, float attackDuration, int offSetX, int attackIndexDmg,
		int damage, int death_sprites_size,std::string path)
		: Enemy(name, pos, dim, folder, hp, speed, ranged, totalWalkFrames, totalAttackFrames, path,attackDuration, offSetX,
		attackIndexDmg, damage),
		deathSpritesSize(death_sprites_size)
	{
		isDead = false;
		std::vector<int> deathS;
		for (int i = 0; i < 22; i++)
		{
			std::string path = "res/KopaSamsu/death (" + std::to_string(i + 1) + ").png";
			deathS.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprites = deathS;
	}
	void takeDamage(int damage) override
	{
		HP -= damage;
		if (HP <= 0) {
			HP = 0;
			isDying = true;
		}
	}

	void updateAnimation(double deltaTime, Entity& player) override
	{
		if (isDying)
		{
			deathSpriteIndex = (deathSpriteIndex + 1) % deathSpritesSize;
			if (deathSpriteIndex == deathSpritesSize - 1) isDead = true;
			return;
		}

		// Check if the enemy is attacking
		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false; // End attack animation
				attackTimer = 0.0;
			}
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);
			if (attackIndex == attackIndexDmg && isColliding(player)) {
				player.takeDamage(damage); // Apply damage
				std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
			}
		}
		// Handle movement animation
		else if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to idle frame
		}
	}

	void render() override {
		if (isDead) return;
		if (isDying)
		{
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), deathSprites[deathSpriteIndex]);
			return;
		}
		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};

class ChakkuMojumder : public Enemy
{
public:
	std::vector<int> deathSprites;
	int deathSpritesSize;
	int deathSpriteIndex = 0;
	bool isDying = false;

	ChakkuMojumder(const std::string& name, const Pos& pos, const Dim& dim, const std::string& folder, int hp, int speed,
		bool ranged, int totalWalkFrames, int totalAttackFrames, float attackDuration, int offSetX, int attackIndexDmg,
		int damage, int death_sprites_size,std::string path)
		: Enemy(name, pos, dim, folder, hp, speed, ranged, totalWalkFrames, totalAttackFrames, path,attackDuration, offSetX,
		attackIndexDmg, damage),
		deathSpritesSize(death_sprites_size)
	{
		isDead = false;
		std::vector<int> deathS;
		for (int i = 0; i < 9; i++)
		{
			std::string path = "res/chakkumojumder/death (" + std::to_string(i + 1) + ").png";
			deathS.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprites = deathS;
	}
	void takeDamage(int damage) override
	{
		HP -= damage;
		if (HP <= 0) {
			HP = 0;
			isDying = true;
		}
	}

	void updateAnimation(double deltaTime, Entity& player) override
	{
		if (isDying)
		{
			deathSpriteIndex = (deathSpriteIndex + 1) % deathSpritesSize;
			if (deathSpriteIndex == deathSpritesSize - 1) isDead = true;
			return;
		}

		// Check if the enemy is attacking
		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false; // End attack animation
				attackTimer = 0.0;
			}
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);
			if (attackIndex == attackIndexDmg && isColliding(player)) {
				player.takeDamage(damage); // Apply damage
				std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
			}
		}
		// Handle movement animation
		else if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to idle frame
		}
	}

	void render() override {
		if (isDead) return;
		if (isDying)
		{
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), deathSprites[deathSpriteIndex]);
			return;
		}
		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};

class Boltu : public Enemy
{
public:
	std::vector<int> deathSprites;
	int deathSpritesSize;
	int deathSpriteIndex = 0;
	bool isDying = false;

	Boltu(const std::string& name, const Pos& pos, const Dim& dim, const std::string& folder, int hp, int speed,
		bool ranged, int totalWalkFrames, int totalAttackFrames, float attackDuration, int offSetX, int attackIndexDmg,
		int damage, int death_sprites_size, std::string path)
		: Enemy(name, pos, dim, folder, hp, speed, ranged, totalWalkFrames, totalAttackFrames, path,attackDuration, offSetX,
		attackIndexDmg, damage),
		deathSpritesSize(death_sprites_size)
	{
		isDead = false;
		std::vector<int> deathS;
		for (int i = 0; i < 7; i++)
		{
			std::string path = "res/boltu/death" + std::to_string(i) + ".png";
			deathS.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprites = deathS;
	}
	void takeDamage(int damage) override
	{
		HP -= damage;
		if (HP <= 0) {
			HP = 0;
			isDying = true;
		}
	}

	void updateAnimation(double deltaTime, Entity& player) override
	{
		if (isDying)
		{
			deathSpriteIndex = (deathSpriteIndex + 1) % deathSpritesSize;
			if (deathSpriteIndex == deathSpritesSize - 1) isDead = true;
			return;
		}

		// Check if the enemy is attacking
		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false; // End attack animation
				attackTimer = 0.0;
			}
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);
			if (attackIndex == attackIndexDmg && isColliding(player)) {
				player.takeDamage(damage); // Apply damage
				std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
			}
		}
		// Handle movement animation
		else if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to idle frame
		}
		updateProjectiles(player);
	}

	void render() override {
		if (isDead) return;
		if (isDying)
		{
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), deathSprites[deathSpriteIndex]);
			return;
		}
		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};

class Omega : public Enemy
{
public:
	std::vector<int> deathSprites;
	int deathSpritesSize;
	int deathSpriteIndex = 0;

	bool isDying = false;

	Omega(const std::string& name, const Pos& pos, const Dim& dim, const std::string& folder, int hp, int speed,
		bool ranged, int totalWalkFrames, int totalAttackFrames, float attackDuration, int offSetX, int attackIndexDmg,
		int damage, int death_sprites_size, std::string path)
		: Enemy(name, pos, dim, folder, hp, speed, ranged, totalWalkFrames, totalAttackFrames, path, attackDuration, offSetX,
		attackIndexDmg, damage),
		deathSpritesSize(death_sprites_size)
	{
		isDead = false;
		std::vector<int> deathS;
		for (int i = 0; i < 7; i++)
		{
			std::string path = "res/boltu/death" + std::to_string(i) + ".png";
			deathS.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprites = deathS;
	}
	void takeDamage(int damage) override
	{
		HP -= damage;
		if (HP <= 0) {
			HP = 0;
			isDying = true;
		}
	}
	void updateAnimation(double deltaTime, Entity& player) override
	{
		if (isDying)
		{
			deathSpriteIndex = (deathSpriteIndex + 1) % deathSpritesSize;
			if (deathSpriteIndex == deathSpritesSize - 1) isDead = true;
			return;
		}

		// Check if the enemy is attacking
		if (isAttacking) {
			attackTimer += deltaTime;
			if (attackTimer >= attackDuration) {
				isAttacking = false; // End attack animation
				attackTimer = 0.0;
			}
			attackIndex = static_cast<int>((attackTimer / attackDuration) * totalAttackFrames);
			if (attackIndex == attackIndexDmg && isColliding(player)) {
				player.takeDamage(damage); // Apply damage
				std::cout << "Player takes damage from melee attack at frame " << attackIndex << std::endl;
			}
		}
		// Handle movement animation
		else if (isMoving) {
			moveIndex = (moveIndex + 1) % totalWalkFrames;
		}
		else {
			moveIndex = 0;  // Reset to idle frame
		}
		updateProjectiles(player);
	}

	void render() override {
		if (isDead) return;
		if (isDying)
		{
			iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), deathSprites[deathSpriteIndex]);
			return;
		}
		// Check if the enemy is attacking
		iSetColor(255, 0, 0);
		iFilledRectangle(position.getX(), position.getY() + dimension.getHeight() + 20, 1 * HP, 20);
		if (isAttacking) {
			if (facingRight) {
				// Normal attack sprite when facing right
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
			else {
				// Flip attack sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), attackSprites[attackIndex]);
			}
		}
		// If not attacking, show the movement or idle sprite
		else if (isMoving) {
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
			else {
				// Flip walking sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), moveSprites[moveIndex]);
			}
		}
		else {
			// Idle sprite (also flipped if facing left)
			if (facingRight) {
				iShowImage(position.getX(), position.getY(), dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
			else {
				// Flip idle sprite when facing left
				iShowImage(position.getX() + dimension.getWidth(), position.getY(), -dimension.getWidth(), dimension.getHeight(), idleSprite);
			}
		}

		// Render projectiles
		renderProjectiles();
	}
};