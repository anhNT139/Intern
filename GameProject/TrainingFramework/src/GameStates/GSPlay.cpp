#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "Ship.h"
#include "Bullet.h"
#include "AnimationSprite.h"
#include "Meteorite.h"
#include <stdlib.h>

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 30, 30);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// ship
	texture = ResourceManagers::GetInstance()->GetTexture("player_ship.tga");
	m_playerShip = std::make_shared<Ship>(model, shader, texture);
	m_playerShip->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight - 50);
	m_playerShip->SetSize(60, 60);

	// meteorites
	/*texture = ResourceManagers::GetInstance()->GetTexture("rock3.tga");
	std::shared_ptr<Meteorite> meteorite;
	for (int i = 1; i <= 3; i++)
	{
		meteorite = std::make_shared<Meteorite>(model, shader, texture);
		meteorite->Set2DPosition(i * 100, i * 100);
		meteorite->SetSize(60, 60);
		m_listMeteorite.push_back(meteorite);
	}*/

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 0", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
	std::vector<std::shared_ptr<Bullet>> listBullet = m_playerShip->getBullet();
	for (auto it : listBullet)
	{
		it->Update(1);
	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case VK_LEFT:
			keyPressed |= KEY_MOVE_LEFT;
			break;
		case VK_RIGHT:
			keyPressed |= KEY_MOVE_RIGHT;
			break;
		case VK_UP:
			keyPressed |= KEY_MOVE_FORWORD;
			break;
		case VK_DOWN:
			keyPressed |= KEY_MOVE_BACKWORD;
			break;
		case VK_SPACE:
			keyPressed |= KEY_SHOOT;
			break;
		}
	}
	else
	{
		switch (key)
		{
		case VK_LEFT:
			keyPressed ^= KEY_MOVE_LEFT;
			break;
		case VK_RIGHT:
			keyPressed ^= KEY_MOVE_RIGHT;
			break;
		case VK_UP:
			keyPressed ^= KEY_MOVE_FORWORD;
			break;
		case VK_DOWN:
			keyPressed ^= KEY_MOVE_BACKWORD;
			break;
		case VK_SPACE:
			keyPressed ^= KEY_SHOOT;
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{	
	float x = m_playerShip->GetPosition().x;
	float y = m_playerShip->GetPosition().y;
	if (keyPressed & KEY_MOVE_LEFT)
	{
		x -= 200 * deltaTime;
		if (x < 30)
			x = 30;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_RIGHT)
	{	
		x += 200 * deltaTime;
		if (x > 450)
			x = 450;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_BACKWORD)
	{
		y += 200 * deltaTime;
		if (y > 770)
			y = 770;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_FORWORD)
	{
		y -= 200 * deltaTime;
		if (y < 30)
			y = 30;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_SHOOT)
	{
		m_playerShip->m_timeShoot -= deltaTime;
		if (m_playerShip->m_timeShoot <= 0)
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("player_laser.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
			bullet->Set2DPosition(x, y - 50);
			bullet->SetSize(16, 41);
			m_playerShip->shoot(bullet);
			m_playerShip->m_timeShoot = 0.15;
		}
	}

	m_playerShip->Update(deltaTime);

	time -= deltaTime;
	if (time <= 0)
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("rock3.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Meteorite> meteorite = std::make_shared<Meteorite>(model, shader, texture);
		meteorite->Set2DPosition(30 + rand() % 421, -40);
		meteorite->SetSize(60, 60);
		m_listMeteorite.push_back(meteorite);
		time = 1;
	}

	std::vector<std::shared_ptr<Bullet>> listBullet = m_playerShip->getBullet();
	for (int i = 0; i < listBullet.size(); i++)
	{
		for (int j = 0; j < m_listMeteorite.size(); j++)
		{
			if (isCollision(listBullet[i], m_listMeteorite[j]))
			{
				m_playerShip->removeBullet(i);
				m_listMeteorite.erase(m_listMeteorite.begin() + j);
			}
		}
	}

	for (int i = 0; i < m_listMeteorite.size(); i++)
	{
		m_listMeteorite[i]->Update(deltaTime);
		if (m_listMeteorite[i]->GetPosition().y > 830)
			m_listMeteorite.erase(m_listMeteorite.begin() + i);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_playerShip->Draw();
	m_score->Draw();
	for (auto it : m_listMeteorite)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_playerShip->getBullet())
	{
		it->Draw();
	}
}

bool GSPlay::isCollision(std::shared_ptr<Sprite2D> o1, std::shared_ptr<Sprite2D> o2)
{ 
	float left1 = o1->GetPosition().x - o1->getWidth() / 2;
	float right1 = o1->GetPosition().x + o1->getWidth() / 2;
	float bottom1 = o1->GetPosition().y + o1->getHeight() / 2;
	float top1 = o1->GetPosition().y - o1->getHeight() / 2;

	float left2 = o2->GetPosition().x - o2->getWidth() / 2;
	float right2 = o2->GetPosition().x + o2->getWidth() / 2;
	float bottom2 = o2->GetPosition().y + o2->getHeight() / 2;
	float top2 = o2->GetPosition().y - o2->getHeight() / 2;

	if ((left1 > left2 && left1 < right2 && top1 < bottom2 && top1 > top2)
		|| (right1 < right2 && right1 > left2 && top1 < bottom2 && top1 > top2)
		|| (left1 > left2 && left1 < right2 && bottom1 > top2 && bottom1 < bottom2)
		|| (right1 < right2 && right1 > left2 && bottom1 > top2 && bottom1 < bottom2))
	{
		return true;
	}

	return false;
}