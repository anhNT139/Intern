#include "PlayerShip.h"
#include "Bullet.h"
#include "ResourceManagers.h"

PlayerShip::PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: SpaceShip(model, shader, texture) 
{
	Init();
}
PlayerShip::PlayerShip(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed)
	: SpaceShip(model, shader, texture, speed)
{
	Init();
	m_speed = speed;
	auto b_model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto b_texture = ResourceManagers::GetInstance()->GetTexture("player_laser.tga");
	auto b_shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Bullet> bullet; 
	for (int i = 1; i <= 20; i++)
	{
		bullet = std::make_shared<Bullet>(b_model, b_shader, b_texture, Vector2(0, -1), 300);
		bullet->SetSize(16, 41);
		m_bulletPool.push_back(bullet);
	}
}

PlayerShip::~PlayerShip() {};

void PlayerShip::Init()
{
	m_damage = 100;
	m_shootTime = 0.0f;
	m_shootInterval = 0.2f;
	m_hp = 3;
	m_xxxxx = 1.0f;
	m_immortalTime = 3.0f;
	m_justCollided = false;
	m_alive = true;
}

void PlayerShip::Draw()
{
	if (m_alive)
	{
		Sprite2D::Draw();
	}
	for (auto it : m_listBullet)
	{
		it->Draw();
	}
}

void PlayerShip::Update(GLfloat deltaTime)
{
	m_shootTime += deltaTime;
	for (int i = 0; i < m_listBullet.size(); i++)
	{
		m_listBullet[i]->Update(deltaTime);
		if (m_listBullet[i]->GetPosition().y < -45)
		{
			removeBullet(i);
		}
	}

	if (m_justCollided)
	{
		m_immortalTime -= deltaTime;
		if (m_immortalTime <= 0)
		{
			m_justCollided = false;
			m_immortalTime = 3.0f;
		}
	}

	if (!m_alive)
	{
		m_xxxxx -= deltaTime;
		if (m_xxxxx <= 0)
		{
			m_alive = true;
			Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight - 50);
			m_xxxxx = 1.0f;
		}
	}
}

void PlayerShip::Shoot() {
	if (m_shootTime >= m_shootInterval)
	{
		std::shared_ptr<Bullet> bullet;
		if (m_bulletPool.empty())
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("player_laser.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			bullet = std::make_shared<Bullet>(model, shader, texture, Vector2(0, -1), 300);
			bullet->SetSize(16, 41);
		}
		else
		{
			bullet = m_bulletPool.back();
			m_bulletPool.pop_back();
		}
		bullet->Set2DPosition(GetPosition().x, GetPosition().y - 50);
		m_listBullet.push_back(bullet);
		m_shootTime = 0;
	}
}

void PlayerShip::SetDamage(int damage)
{
	m_damage = damage;
}

int PlayerShip::GetDamage()
{
	return m_damage;
}

bool PlayerShip::JustCollided()
{
	return m_justCollided;
}

bool PlayerShip::Alive()
{
	return m_alive;
}

void PlayerShip::HandleAfterCollision()
{
	m_justCollided = true;
	m_alive = false;
	m_hp--;
	if (m_damage > 100)
	{
		m_damage -= 100;
	}
}
