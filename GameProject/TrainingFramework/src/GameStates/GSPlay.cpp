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

	// ship
	texture = ResourceManagers::GetInstance()->GetTexture("player_ship.tga");
	m_playerShip = std::make_shared<Ship>(model, shader, texture);
	m_playerShip->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight - 50);
	m_playerShip->SetSize(60, 60);

	// meteorites
	texture = ResourceManagers::GetInstance()->GetTexture("rock3.tga");
	std::shared_ptr<Sprite2D> meteorite = std::make_shared<GameButton>(model, shader, texture);
	meteorite->Set2DPosition(200, 200);
	meteorite->SetSize(70, 70);
	m_listMeteorite.push_back(meteorite);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 30, 30);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

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
	int x = m_playerShip->GetPosition().x;
	int y = m_playerShip->GetPosition().y;
	if (keyPressed & KEY_MOVE_LEFT)
	{
		if (x < 35)
		{
			x = 35;
		}
		x -= 5;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_RIGHT)
	{	
		if (x > 445)
		{
			x = 445;
		}
		x += 5;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_FORWORD)
	{	
		if (y < 35)
		{
			y = 35;
		}
		y -= 5;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_MOVE_BACKWORD)
	{
		if (y > 765)
		{
			y = 765;
		}
		y += 5;
		m_playerShip->Set2DPosition(x, y);
	}
	if (keyPressed & KEY_SHOOT)
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("rock3.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
		bullet->Set2DPosition(x, y - 50);
		bullet->SetSize(30, 30);
		m_playerShip->shoot(bullet);
	}

	for (auto it : m_playerShip->getBullet())
	{
		
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
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