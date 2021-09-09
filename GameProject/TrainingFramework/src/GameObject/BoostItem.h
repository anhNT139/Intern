#pragma once
#include "Sprite2D.h"

class BoostItem : public Sprite2D
{
private:
	int m_id;
public:
	BoostItem() : Sprite2D() {}
	BoostItem(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	BoostItem(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int id);
	int GetID();
	void SetID(int id);
	void Update(GLfloat deltaTime);
};