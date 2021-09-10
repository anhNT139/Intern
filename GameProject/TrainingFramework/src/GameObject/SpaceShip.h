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
	int m_hp;
public:
	SpaceShip() : Sprite2D() {}
	SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed);
	SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed, int hp);
	~SpaceShip();
	std::vector<std::shared_ptr<Bullet>> getBullet();
	virtual void Update(GLfloat deltaTime);
	virtual void removeBullet(int index);
	void		SetShootInterval(int shootInterval);
	void		SetSpeed(int speed);
	int			GetSpeed();
	int			GetHp();
	void		AddHp(int hp);
	void		SubHp(int hp);
	void		SetHp(int hp);
};