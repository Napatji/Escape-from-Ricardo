#include "Player.h"
#include "Animation.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;
	faceLeft = true;
	faceDown = true;
	faceUp = true;

	body.setSize(sf::Vector2f(50.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(340.0f, 850.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		row = 1;
		movement.y -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		row = 1;
		movement.y -= 2 * (speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		row = 0;
		movement.y += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		row = 0;
		movement.y += 2 * (speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		row = 2;
		movement.x -= speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		row = 2;
		movement.x -= 2 * (speed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		row = 3;
		movement.x += speed * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		row = 3;
		movement.x += 2 * (speed * deltaTime);
	}



	animation.Update(row, deltaTime,faceRight, faceLeft, faceUp, faceDown);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

const sf::Vector2f& Player::getPos() const
{
	return this->body.getPosition();
}

const sf::FloatRect Player::getBound()
{
	return this->body.getGlobalBounds();
}

void Player::SetPosition(float x, float y)
{
	body.setPosition(x, y);
}