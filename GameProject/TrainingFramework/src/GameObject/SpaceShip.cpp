#include "SpaceShip.h"
#include "Bullet.h"

SpaceShip::SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

SpaceShip::SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed)
	: Sprite2D(model, shader, texture)
{
	Init();
	m_speed = speed;
}

SpaceShip::SpaceShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed, int hp)
	: Sprite2D(model, shader, texture)
{
	SpaceShip(model, shader, texture, speed);
	m_hp = hp;
}

SpaceShip::~SpaceShip() 
{

}

void SpaceShip::Update(GLfloat deltaTime)
{
	m_shootTime += deltaTime;
	for (int i = 0; i < m_listBullet.size(); i++)
	{
		m_listBullet[i]->Update(deltaTime);
		if (m_listBullet[i]->GetPosition().y < -45 || m_listBullet[i]->GetPosition().y > Globals::screenHeight
			|| m_listBullet[i]->GetPosition().x < -10 || m_listBullet[i]->GetPosition().x > Globals::screenWidth)
		{
			removeBullet(i);
		}
	}
}

std::vector<std::shared_ptr<Bullet>> SpaceShip::getBullet() {
	return m_listBullet;
}

void SpaceShip::removeBullet(int index)
{
	m_bulletPool.push_back(m_listBullet[index]);
	m_listBullet.erase(m_listBullet.begin() + index);
}

void SpaceShip::SetSpeed(int speed)
{
	m_speed = speed;
}

int SpaceShip::GetSpeed()
{
	return m_speed;
}

int SpaceShip::GetHp()
{
	return m_hp;
}

void SpaceShip::AddHp(int hp)
{
	m_hp += hp;
}

void SpaceShip::SubHp(int hp)
{
	m_hp -= hp;
}