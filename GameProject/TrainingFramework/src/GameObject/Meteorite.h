#pragma once
#include "Sprite2D.h"

class Meteorite : public Sprite2D
{
private:
	int m_hp;
	int m_speed;
public:
	Meteorite() : Sprite2D() {};
	Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int speed, int hp);
	Meteorite(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, int hp);
	~Meteorite();
	void	Update(GLfloat deltatime) override;
	void	SubHp(int damage);
	void	SetHp(int hp);
	int		GetHp();
};