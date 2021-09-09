#include "BoostItem.h"

BoostItem::BoostItem(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	Init();
}

BoostItem::BoostItem(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int id)
{
	Init();
	m_id = id;
}

int BoostItem::GetID()
{
	return m_id;
}

void BoostItem::SetID(int id)
{
	m_id = id;
}

void BoostItem::Update(GLfloat deltaTime)
{
	Set2DPosition(this->GetPosition().x, this->GetPosition().y + 80 * deltaTime);
}