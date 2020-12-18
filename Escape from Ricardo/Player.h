#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"
#include<iostream>
#include <vector>

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBound();
	void SetPosition(float x, float y);
	sf::RectangleShape body;

private:
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight, faceLeft, faceUp, faceDown;
};

