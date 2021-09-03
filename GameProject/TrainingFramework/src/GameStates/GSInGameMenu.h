#pragma once
#include "GameStateBase.h"
#include "GameButton.h"

class GSInGameMenu : public GameStateBase
{
public:
	GSInGameMenu();
	~GSInGameMenu();

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

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Sprite2D>	m_textPause;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
};