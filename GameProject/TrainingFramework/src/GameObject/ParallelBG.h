#pragma once
#include "Sprite2D.h"

class ParallelBG :
	public BaseObject
{
private:
	GLfloat m_speed;
	std::shared_ptr<Sprite2D> m_bg;
	std::shared_ptr<Sprite2D> m_bg1;
public:
	ParallelBG();
	ParallelBG(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat speed);
	~ParallelBG();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

};