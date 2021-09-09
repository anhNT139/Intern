#include "GSNoName.h"
#include "Text.h"

GSNoName::GSNoName() : GameStateBase(StateType::STATE_CREDIT),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textScore(nullptr)
{

}

GSNoName::~GSNoName()
{

}

void GSNoName::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// text score
	texture = ResourceManagers::GetInstance()->GetTexture("text_score.tga");
	m_textScore = std::make_shared<Sprite2D>(model, shader, texture);
	m_textScore->Set2DPosition(Globals::screenWidth / 2, 100);
	m_textScore->SetSize(300, 80);


	// new game button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_new_game.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth / 2, 500);
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
	button->Set2DPosition(Globals::screenWidth / 2, 600);
	button->SetSize(250, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared<Text>(shader, font, "100", TextColor::BLUE, 5);
	m_score->Set2DPosition(Globals::screenWidth / 4, 300);
}

void GSNoName::Exit()
{
}


void GSNoName::Pause()
{
}

void GSNoName::Resume()
{
}


void GSNoName::HandleEvents()
{
}

void GSNoName::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSNoName::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSNoName::HandleMouseMoveEvents(int x, int y)
{
}

void GSNoName::Update(float deltaTime)
{

}

void GSNoName::Draw()
{
	m_background->Draw();
	m_textScore->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
