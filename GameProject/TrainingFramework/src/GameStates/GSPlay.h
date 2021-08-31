#pragma once
#include "GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class Ship;
class AnimationSprite;
class Meteorite;

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

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Ship>	m_playerShip;
	std::vector<std::shared_ptr<Meteorite>>	m_listMeteorite;
	std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<AnimationSprite> m_coin;
	float time = 0;
};
