#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class PlayerShip;
class AnimationSprite;
class Meteorite;
class Enemy;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	bool	isCollision(std::shared_ptr<Sprite2D> o1, std::shared_ptr<Sprite2D> o2);
	void	RemoveMeteorite(int index);
	bool	MainCharacterCollision();

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<PlayerShip>	m_mainCharacter;
	std::shared_ptr<Sprite2D>	m_hpIcon;
	std::shared_ptr<Text>	m_hpText;
	std::shared_ptr<Text>		m_score;
	std::vector<std::shared_ptr<Meteorite>>	m_listMeteorite;
	std::list<std::shared_ptr<Meteorite>> m_meteoritePool;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector<std::shared_ptr<Enemy>>	m_listEnemy;
	float m_meteoriteGenerateTime;
	float m_enemyGenerateTime;
	int m_playerScore;
	float m_immortalTime;
	float m_xxxxx;
	bool m_justCollided;
	bool m_alive;
};
