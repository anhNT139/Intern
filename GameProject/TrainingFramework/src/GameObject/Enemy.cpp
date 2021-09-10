#include "Enemy.h"
#include "Bullet.h"
#include "ResourceManagers.h"
#include<math.h>

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: SpaceShip(model, shader, texture)
{
	Init();
}

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed, int hp)
	: SpaceShip(model, shader, texture, speed)
{
	Init();
	m_speed = speed;
	m_hp = hp;
}

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed)
	: SpaceShip(model, shader, texture, speed)
{
	Init();
	m_speed = speed;
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	m_shootTime = 0.0f;
	m_shootInterval = 1.5f;
}

void Enemy::Draw()
{
	Sprite2D::Draw();
	for (auto it : m_listBullet)
		it->Draw();
}

void Enemy::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);
	if (m_id == 1)
	{
		Set2DPosition(GetPosition().x + m_speed * deltaTime, GetPosition().y);
	}
	else if (m_id == 2)
	{
		Set2DPosition(GetPosition().x - m_speed * deltaTime, GetPosition().y);
	}
	else if (m_id == 3)
	{
		Set2DPosition(GetPosition().x, GetPosition().y + m_speed * deltaTime);
	}
}

void Enemy::Shoot(Vector3 playerPos) {
	if (m_shootTime >= m_shootInterval)
	{
		std::shared_ptr<Bullet> bullet;
		Vector2 tmp(playerPos.x - GetPosition().x, playerPos.y - GetPosition().y);
		GLfloat tmp2 = sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
		Vector2 direction(tmp.x / tmp2, tmp.y / tmp2);
		if (m_bulletPool.empty())
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("enemy_laser.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			bullet = std::make_shared<Bullet>(model, shader, texture, direction, m_bulletSpeed);
		}
		else
		{
			bullet = m_bulletPool.back();
			m_bulletPool.pop_back();
			bullet->SetDirection(direction);
		}
		bullet->Set2DPosition(GetPosition().x, GetPosition().y);
		bullet->SetSize(20, 20);
		m_listBullet.push_back(bullet);
		m_shootTime = 0;
	}
}

void Enemy::SetBulletSpeed(int speed)
{
	m_bulletSpeed = speed;
}