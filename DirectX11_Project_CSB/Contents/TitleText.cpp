#include "PreCompile.h"
#include "TitleText.h"

TitleText::TitleText()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Collision");

	NewGameCol = CreateDefaultSubObject<UCollision>("Collision");
	NewGameCol->SetScale({ 340.0f, 50.0f });
	NewGameCol->SetPosition(FVector(430.f, 220.f));
	NewGameCol->SetCollisionGroup(ECollisionOrder::Menu);
	NewGameCol->SetCollisionType(ECollisionType::Rect);
	NewGameCol->SetupAttachment(Root);

	SetRoot(Root);

	InputOn();
}

TitleText::~TitleText()
{
}

void TitleText::BeginPlay()
{
	Super::BeginPlay();
	UISpawn();

}

void TitleText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CollisionCheck();

}

void TitleText::UISpawn()
{
	NewGame = CreateWidget<UTextWidget>(GetWorld(), "NewGame");
	NewGame->AddToViewPort(2);
	NewGame->SetScale(HoloCureConstValue::MultipleSize * 11);
	NewGame->SetFont("Galmuri9");
	NewGame->SetColor(Color8Bit::White);
	NewGame->SetPosition(FVector(430.f, 220.f));
	NewGame->SetText("»õ °ÔÀÓ");

}

void TitleText::CollisionCheck()
{
	NewGameCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			NewGame->SetColor(Color8Bit::Black);
			ColChack = true;

		}
	);
	NewGameCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			NewGame->SetColor(Color8Bit::White);
			ColChack = false;
		}
	);

	if (true == IsDown(VK_LBUTTON) && true == ColChack)
	{
		GEngine->ChangeLevel("SelectLevel");
	}
	if (true == IsDown(VK_LBUTTON) && true == ExitChack)
	{
		GEngine->EngineWindow.Off();
	}

}
