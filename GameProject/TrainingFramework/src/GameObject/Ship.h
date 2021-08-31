#pragma once
#include "Sprite2D.h"

class Bullet;

class Ship : public Sprite2D
{
private:
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
	
public:
	Ship() : Sprite2D() {};
	Ship(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Ship();
	std::vector<std::shared_ptr<Bullet>> getBullet();
	void		Update(GLfloat deltatime) override;
	void		shoot(std::shared_ptr<Bullet> bullet);
	void		removeBullet(int index);
	float m_timeShoot = 0;
};