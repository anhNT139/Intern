#pragma once
#include "Sprite2D.h"

class Bullet : public Sprite2D
{
private:
	Vector2 m_direction;
	int m_speed;
public:
	Bullet() : Sprite2D() {}
	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Bullet(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, Vector2 direction, int speed);
	~Bullet();
	void	Update(GLfloat deltaTime) override;
	void	SetDirection(Vector2 direction);
	void	SetSpeed(int speed);
};
