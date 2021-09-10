#include "Meteorite.h"

Meteorite::Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

Meteorite::Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hp)
	: Sprite2D(model, shader, texture)
{
	Init();
	m_hp = hp;
}

Meteorite::Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed, int hp)
	: Sprite2D(model, shader, texture)
{
	Init();
	m_hp = hp;
	m_speed = speed;
}

Meteorite::~Meteorite() {};

void Meteorite::Update(GLfloat deltaTime)
{
	Set2DPosition(this->GetPosition().x, this->GetPosition().y + m_speed * deltaTime);
}

int Meteorite::GetHp()
{
	return m_hp;
}

void Meteorite::SubHp(int damage)
{
	m_hp -= damage;
}

void Meteorite::SetHp(int hp)
{
	m_hp = hp;
}

void Meteorite::SetSpeed(int speed)
{
	m_speed = speed;
}