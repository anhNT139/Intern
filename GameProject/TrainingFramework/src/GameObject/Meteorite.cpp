#include "Meteorite.h"

Meteorite::Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

Meteorite::~Meteorite() {};

void Meteorite::Update(GLfloat deltatime)
{
	Set2DPosition(this->GetPosition().x, this->GetPosition().y + 100 * deltatime);
}