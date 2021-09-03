#pragma once
#include "Sprite2D.h"

class Bullet;

class SpaceShip : public Sprite2D
{
protected:
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
	std::list <std::shared_ptr<Bullet>> m_bulletPool;
	float m_shootTime;
	float m_shootInterval;
	int m_speed;
public:
	SpaceShip() : Sprite2D() {}
	SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed);
	~SpaceShip();
	std::vector<std::shared_ptr<Bullet>> getBullet();
	virtual void Update(GLfloat deltaTime);
	void		removeBullet(int index);
	void		SetSpeed(int speed);
	int			GetSpeed();
};