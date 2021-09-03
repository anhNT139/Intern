#include "GSInGameMenu.h"
#include "Text.h"

GSInGameMenu::GSInGameMenu() : GameStateBase(StateType::STATE_CREDIT),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textPause(nullptr)
{

}

GSInGameMenu::~GSInGameMenu()
{

}

void GSInGameMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_in_game_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// text pause
	texture = ResourceManagers::GetInstance()->GetTexture("text_pause.tga");
	m_textPause = std::make_shared<Sprite2D>(model, shader, texture);
	m_textPause->Set2DPosition(Globals::screenWidth / 2, 60);
	m_textPause->SetSize(300, 60);

	// resume button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_resume.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 300);
	button->SetSize(250, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// new game button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_new_game.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 400);
	button->SetSize(250, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(button);

	// menu button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_menu.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 500);
	button->SetSize(250, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSInGameMenu::Exit()
{
}


void GSInGameMenu::Pause()
{
}

void GSInGameMenu::Resume()
{
}


void GSInGameMenu::HandleEvents()
{
}

void GSInGameMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSInGameMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSInGameMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSInGameMenu::Update(float deltaTime)
{

}

void GSInGameMenu::Draw()
{
	m_background->Draw();
	m_textPause->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
