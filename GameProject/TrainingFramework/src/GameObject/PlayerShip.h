#pragma once
#include "SpaceShip.h"

class Bullet;

class PlayerShip : public SpaceShip
{
public:
	PlayerShip() : SpaceShip() {}
	PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed);
	~PlayerShip();
	void		Init() override;
	void		Shoot();
};