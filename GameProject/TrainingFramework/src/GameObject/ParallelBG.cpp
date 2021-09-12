#include "ParallelBG.h"
#include "Application.h"
#include "BaseObject.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Texture.h"

ParallelBG::ParallelBG()
{}

ParallelBG::ParallelBG(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, GLfloat speed) 
	: BaseObject(0, model, shader, texture)
{
	m_speed = speed;
	m_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_bg->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_bg->SetSize(Globals::screenWidth, Globals::screenHeight);
	m_bg1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_bg1->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight * 3 / 2);
	m_bg1->SetSize(Globals::screenWidth, Globals::screenHeight);
	Init();
}

ParallelBG::~ParallelBG()
{

}


void ParallelBG::Init()
{
	SetCamera(Application::GetInstance()->GetCamera());
	CalculateWorldMatrix();
}

void ParallelBG::Draw()
{
	m_bg->Draw();
	m_bg1->Draw();
}

void ParallelBG::Update(GLfloat deltatime)
{
	Vector2 deltaMove = Vector2(0, 1) * m_speed * deltatime;
	m_bg->Set2DPosition(m_bg->GetPosition().x + deltaMove.x, m_bg->GetPosition().y - deltaMove.y);
	m_bg1->Set2DPosition(m_bg1->GetPosition().x + deltaMove.x, m_bg1->GetPosition().y - deltaMove.y);
	if (m_bg->GetPosition().y <= -Globals::screenHeight / 2)
	{
		m_bg->Set2DPosition(m_bg->GetPosition().x, m_bg1->GetPosition().y + Globals::screenHeight);
	}
	if (m_bg1->GetPosition().y <= -Globals::screenHeight / 2)
	{
		m_bg1->Set2DPosition(m_bg1->GetPosition().x, m_bg->GetPosition().y + Globals::screenHeight);
	}
}