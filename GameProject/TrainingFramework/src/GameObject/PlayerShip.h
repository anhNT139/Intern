#pragma once
#include "SpaceShip.h"

class Bullet;

class PlayerShip : public SpaceShip
{
private:
	float m_immortalTime;
	float m_xxxxx;
	bool m_justCollided;
	bool m_alive;
	int m_damage;
public:
	PlayerShip() : SpaceShip() {}
	PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed);
	~PlayerShip();
	void		Init() override;
	void		Shoot();
	void		Draw() override;
	void		Update(GLfloat deltaTime) override;
	bool		JustCollided();
	bool		Alive();
	void		HandleAfterCollision();
	void		SetDamage(int damage);
	int			GetDamage();
};