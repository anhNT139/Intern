#pragma once
#include "Sprite2D.h"

class Meteorite : public Sprite2D
{
public:
	Meteorite() : Sprite2D() {};
	Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	~Meteorite();
	void		Update(GLfloat deltatime) override;
};