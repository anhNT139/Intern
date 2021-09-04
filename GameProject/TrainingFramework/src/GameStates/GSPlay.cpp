#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Text.h"
#include "GameButton.h"
#include "PlayerShip.h"
#include "Bullet.h"
#include "AnimationSprite.h"
#include "Meteorite.h"
#include "Enemy.h"
#include <stdlib.h>
#include <string>

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
	m_meteoriteGenerateTime = 1.0f;
	m_enemyGenerateTime = 3.0f;
	m_playerScore = 0;
	m_xxxxx = 0;
	m_immortalTime = 3.0f;
	m_justCollided = false;
	m_alive = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// hp icon
	texture = ResourceManagers::GetInstance()->GetTexture("hp_icon.tga");
	m_hpIcon = std::make_shared<Sprite2D>(model, shader, texture);
	m_hpIcon->Set2DPosition(Vector2(25, 50));
	m_hpIcon->SetSize(40, 30);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 30, 30);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateType::STATE_IN_GAME_MENU);
		});
	m_listButton.push_back(button);

	// player ship
	texture = ResourceManagers::GetInstance()->GetTexture("player_ship.tga");
	m_mainCharacter = std::make_shared<PlayerShip>(model, shader, texture, 200);
	m_mainCharacter->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight - 50);
	m_mainCharacter->SetSize(60, 60);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared<Text>(shader, font, "score: " + std::to_string(m_playerScore), TextColor::RED, 0.75);
	m_score->Set2DPosition(Vector2(5, 25));

	// hp text
	m_hpText = std::make_shared<Text>(shader, font, std::to_string(m_mainCharacter->GetHp()), TextColor::RED, 0.75);
	m_hpText->Set2DPosition(Vector2(50, 55));
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
	Vector3 curPos = m_mainCharacter->GetPosition();
	int speed = m_mainCharacter->GetSpeed();
	// Handle key events
	if (keyPressed & KEY_MOVE_LEFT)
	{
		curPos.x -= speed * deltaTime;
		if (curPos.x < 30)
			curPos.x = 30;
	}
	if (keyPressed & KEY_MOVE_RIGHT)
	{	
		curPos.x += speed * deltaTime;
		if (curPos.x > 450)
			curPos.x = 450;
	}
	if (keyPressed & KEY_MOVE_BACKWORD)
	{
		curPos.y += speed * deltaTime;
		if (curPos.y > 770)
			curPos.y = 770;
	}
	if (keyPressed & KEY_MOVE_FORWORD)
	{
		curPos.y -= speed * deltaTime;
		if (curPos.y < 30)
			curPos.y = 30;
	}
	m_mainCharacter->Set2DPosition(curPos.x, curPos.y);
	if (keyPressed & KEY_SHOOT)
	{
		m_mainCharacter->Shoot();
	}

	// update main character
	m_mainCharacter->Update(deltaTime);

	// Generate meteorite
	m_meteoriteGenerateTime -= deltaTime;
	if (m_meteoriteGenerateTime <= 0)
	{	
		std::shared_ptr<Meteorite> meteorite;
		if (m_meteoritePool.empty())
		{
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("rock3.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			meteorite = std::make_shared<Meteorite>(model, shader, texture);
		}
		else
		{
			meteorite = m_meteoritePool.back();
			m_meteoritePool.pop_back();
		}
		meteorite->SetSize(60, 60);
		meteorite->Set2DPosition(30 + rand() % 421, -30);
		m_listMeteorite.push_back(meteorite);
		m_meteoriteGenerateTime = 2.0f;
	}

	// Generate enemy
	m_enemyGenerateTime -= deltaTime;
	if (m_enemyGenerateTime <= 0)
	{
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("enemy.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 50);
		enemy->SetSize(80, 60);
		enemy->Set2DPosition(0, 300);
		m_listEnemy.push_back(enemy);
		m_enemyGenerateTime = 3.0f;
	}

	// handle collision
	std::vector<std::shared_ptr<Bullet>> listPlayerBullet = m_mainCharacter->getBullet();
	for (int i = 0; i < listPlayerBullet.size(); i++)
	{
		for (int j = 0; j < m_listMeteorite.size(); j++)
		{
			if (isCollision(listPlayerBullet[i], m_listMeteorite[j]))
			{
				m_mainCharacter->removeBullet(i);
				RemoveMeteorite(j);
				m_playerScore += 10;
			}
		}
		for (int k = 0; k < m_listEnemy.size(); k++)
		{
			if (isCollision(listPlayerBullet[i], m_listEnemy[k]))
			{
				m_mainCharacter->removeBullet(i);
				m_listEnemy.erase(m_listEnemy.begin() + k);
				m_playerScore += 30;
			}
		}
	}

	if (MainCharacterCollision())
	{
		m_justCollided = true;
		m_alive = false;
		m_mainCharacter->SetHp(m_mainCharacter->GetHp() - 1);
		m_hpText->SetText(std::to_string(m_mainCharacter->GetHp()));
	}

	if (m_justCollided)
	{
		m_immortalTime -= deltaTime;
		if (m_immortalTime <= 0)
		{
			m_justCollided = false;
			m_immortalTime = 3.0f;
		}
	}

	if (!m_alive)
	{
		m_xxxxx -= deltaTime;
		if (m_xxxxx <= 0)
		{
			m_alive = true;
			m_mainCharacter->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight - 50);
			m_xxxxx = 1.0f;
		}
	}

	// update possition
	for (int i = 0; i < m_listMeteorite.size(); i++)
	{
		m_listMeteorite[i]->Update(deltaTime);
		if (m_listMeteorite[i]->GetPosition().y > 830)
		{
			RemoveMeteorite(i);
		}
	}

	for (int i = 0; i < m_listEnemy.size(); i++)
	{
		m_listEnemy[i]->Update(deltaTime);
		if (m_alive)
		{
			m_listEnemy[i]->Shoot(curPos);
		}
		if (m_listEnemy[i]->GetPosition().x > 550)
		{
			m_listEnemy.erase(m_listEnemy.begin() + i);
		}
	}

	// update score
	m_score->SetText("Score: " + std::to_string(m_playerScore));
}

void GSPlay::Draw()
{
	m_background->Draw();
	if (m_alive)
	{
		m_mainCharacter->Draw();
	}
	m_score->Draw();
	m_hpIcon->Draw();
	m_hpText->Draw();
	for (auto it : m_listMeteorite)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_mainCharacter->getBullet())
	{
		it->Draw();
	}
	for (auto it : m_listEnemy)
	{
		it->Draw();
		for (auto it2 : it->getBullet())
		{
			it2->Draw();
		}
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

void GSPlay::RemoveMeteorite(int index)
{
	m_meteoritePool.push_back(m_listMeteorite[index]);
	m_listMeteorite.erase(m_listMeteorite.begin() + index);
}

bool GSPlay::MainCharacterCollision()
{
	if (m_justCollided)
	{
		return false;
	}
	// between main character and enemy
	for (int i = 0; i < m_listEnemy.size(); i++)
	{
		std::shared_ptr<Enemy> enemy = m_listEnemy[i];
		if (isCollision(enemy, m_mainCharacter))
		{
			m_listEnemy.erase(m_listEnemy.begin() + i);
			return true;
		}
		std::vector <std::shared_ptr<Bullet>> listEnemyBullet = enemy->getBullet();
		for (int j = 0; j < listEnemyBullet.size(); j++)
		{
			if (isCollision(listEnemyBullet[j], m_mainCharacter))
			{
				enemy->removeBullet(j);
				return true;
			}
		}
	}

	// between main character and meteorite
	for (int i = 0; i < m_listMeteorite.size(); i++)
	{
		if (isCollision(m_listMeteorite[i], m_mainCharacter))
		{
			RemoveMeteorite(i);
			return true;
		}
	}

	return false;
}