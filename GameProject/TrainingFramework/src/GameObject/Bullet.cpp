#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Vector2 direction, int speed)
	: Sprite2D(model, shader, texture), m_speed(speed), m_direction(m_direction)
{
	Init();
	m_speed = speed;
	m_direction = direction;
}

Bullet::~Bullet() 
{
};

void Bullet::SetDirection(Vector2 direction)
{
	m_direction = direction;
}

void Bullet::SetSpeed(int speed)
{
	m_speed = speed;
}

void Bullet::Update(GLfloat deltaTime)
{
	Set2DPosition(this->GetPosition().x + m_direction.x * deltaTime * m_speed, this->GetPosition().y + m_direction.y * deltaTime * m_speed);
}
