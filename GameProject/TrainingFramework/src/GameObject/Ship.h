#pragma once
#include "Sprite2D.h"

class Bullet;

class Ship : public Sprite2D
{
private:
	std::vector<std::shared_ptr<Bullet>> m_listBullet;
public:
	Ship() : Sprite2D() {};
	Ship(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Ship(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);
	Ship(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Ship();
	void shoot(std::shared_ptr<Bullet> bullet);
	std::vector<std::shared_ptr<Bullet>> getBullet();
};