#include "Ship.h"
#include "Bullet.h"
#include<iostream>

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

void Ship::removeBullet(int index)
{
	m_listBullet.erase(m_listBullet.begin() + index);
}

void Ship::Update(GLfloat deltatime)
{
	for (int i = 0; i < m_listBullet.size(); i++)
	{
		m_listBullet[i]->Update(deltatime);
		if (m_listBullet[i]->GetPosition().y < -45)
		{
			removeBullet(i);
		}
	}
}
