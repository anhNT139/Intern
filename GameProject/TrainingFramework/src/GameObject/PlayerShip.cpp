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
}

PlayerShip::~PlayerShip() {};

void PlayerShip::Init()
{
	m_shootTime = 0.0f;
	m_shootInterval = 0.2f;
	m_hp = 3;
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
		}
		else
		{
			bullet = m_bulletPool.back();
			m_bulletPool.pop_back();
		}
		bullet->Set2DPosition(GetPosition().x, GetPosition().y - 50);
		bullet->SetSize(16, 41);
		m_listBullet.push_back(bullet);
		m_shootTime = 0;
	}
}

int PlayerShip::GetHp()
{
	return m_hp;
}

void PlayerShip::SetHp(int hp)
{
	m_hp = hp;
}