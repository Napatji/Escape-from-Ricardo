#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)

{
	this->speed = speed;
	this->follow_or_not = follow_or_not;
	row = 0;
	faceRight = true;
	faceLeft = true;
	faceDown = true;
	faceUp = true;

	enemy.setSize(sf::Vector2f(50.0f, 75.0f));
	enemy.setOrigin(enemy.getSize() / 2.0f);
	enemy.setPosition(4762.0f, 435.0f);
	enemy.setTexture(texture);
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime, sf::Vector2f playerPos)
{
	sf::Vector2f movement(0.0f, 0.0f);
	animation.Update(row, deltaTime, faceRight, faceLeft, faceUp, faceDown);
	enemy.setTextureRect(animation.uvRect);
	enemy.move(movement);
	follow(playerPos.x, playerPos.y);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->enemy.getPosition();
}

const bool& Enemy::following() const
{
	return this->follow_or_not;
}

const sf::FloatRect Enemy::getBound()
{
	return this->enemy.getGlobalBounds();
}

void Enemy::move(float dir_x, float dir_y, float& deltaTime)
{
	enemy.move(dir_x * this->speed * deltaTime, dir_x * this->speed * deltaTime);
}

void Enemy::follow(float player_pos_x, float player_pos_y)
{
	float distance = sqrt((player_pos_x - enemy.getPosition().x) * (player_pos_x - enemy.getPosition().x) + (player_pos_y - enemy.getPosition().y) * (player_pos_y - enemy.getPosition().y));
	float dir_x = (player_pos_x - enemy.getPosition().x) / distance;
	float dir_y = (player_pos_y - enemy.getPosition().y) / distance;
	if (distance > 100)
	{
		if (dir_x < 0)
		{
			enemy.move(dir_x * speed, dir_y * speed);
		}
		if (dir_x > 0)
		{
			enemy.move(dir_x * speed, dir_y * speed);
		}
		if (dir_y < 0)
		{
			enemy.move(dir_x * speed, dir_y * speed);
		}
		if (dir_y > 0)
		{
			enemy.move(dir_x * speed, dir_y * speed);
		}
	}
}

