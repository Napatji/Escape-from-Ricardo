#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
#include <vector>

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Enemy();

	void Update(float deltaTime, sf::Vector2f playerPos);
	void Draw(sf::RenderWindow& window);

	const sf::Vector2f& getPos() const;
	const bool& following() const;
	const sf::FloatRect getBound();
	sf::Vector2f GetPosition() { return enemy.getPosition(); }
	Collider GetCollider() { return Collider(enemy); }

	void move(float dir_x, float dir_y, float& deltaTime);
	void follow(float player_pos_x, float player_pos_y);

private:
	sf::RectangleShape enemy;
	Animation animation;
	unsigned int row;
	float speed ;
	bool faceRight, faceLeft, faceUp, faceDown;
	bool follow_or_not;
};

