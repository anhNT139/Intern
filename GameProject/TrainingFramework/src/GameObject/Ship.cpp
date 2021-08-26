#include "Ship.h"
#include "Bullet.h"

Ship::Ship(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(id, model, shader, texture) 
{
	Init();
}

Ship::Ship(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color)
	: Sprite2D(id, model, shader, color)
{
	Init();
}

Ship::Ship(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture) 
{
	Init();
}

Ship::~Ship() {};

void Ship::shoot(std::shared_ptr<Bullet> bullet) {
	m_listBullet.push_back(bullet);
}

std::vector<std::shared_ptr<Bullet>> Ship::getBullet() {
	return m_listBullet;
}