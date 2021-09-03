#pragma once
#include "SpaceShip.h"

class Bullet;

class Enemy : public SpaceShip
{
public:
	Enemy():SpaceShip() {}
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed);
	~Enemy();
	void Update(GLfloat deltaTime) override;
	void Init() override;
	void Shoot(Vector3 playerPos);
};