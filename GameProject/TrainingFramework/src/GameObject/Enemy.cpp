#include "Enemy.h"
#include "Bullet.h"
#include "ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: SpaceShip(model, shader, texture)
{
	Init();
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


void Enemy::Update(GLfloat deltaTime)
{
	SpaceShip::Update(deltaTime);
	Set2DPosition(GetPosition().x + m_speed * deltaTime, GetPosition().y);
}

void Enemy::Shoot(Vector3 playerPos) {
	if (m_shootTime >= m_shootInterval)
	{
		std::shared_ptr<Bullet> bullet;
		Vector2 direction;
		if (GetPosition().y < playerPos.y)
		{
			direction.y = 1.0f;
			direction.x = (GetPosition().x - playerPos.x) / (GetPosition().y - playerPos.y);
		}
		else
		{
			direction.y = -1.0f;
			direction.x = (playerPos.x- GetPosition().x) / (playerPos.y - GetPosition().y);
		}
		if (m_bulletPool.empty())
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("enemy_laser.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			bullet = std::make_shared<Bullet>(model, shader, texture, direction, 150);
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
