#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

Bullet::~Bullet() 
{
};

void Bullet::Update(GLfloat deltatime)
{
	Set2DPosition(this->GetPosition().x, this->GetPosition().y - 300 * deltatime);
}
