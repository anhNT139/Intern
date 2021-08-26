#pragma once
#include "Sprite2D.h"

class Bullet : public Sprite2D
{
public:
	Bullet() : Sprite2D() {};
	Bullet(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	Bullet(GLint id, std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, Vector4 color);

	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

	~Bullet();
};
