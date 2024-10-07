#include "PreCompile.h"
#include "TitleText.h"
#include "PlayGameMode.h"

//UTitleText::UTitleText()
//{
//	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Collision");
//
//	NewGameCol = CreateDefaultSubObject<UCollision>("Collision");
//	NewGameCol->SetScale({ 340.0f, 50.0f });
//	NewGameCol->SetPosition(FVector(430.f, 220.f));
//	NewGameCol->SetCollisionGroup(ECollisionOrder::Menu);
//	NewGameCol->SetCollisionType(ECollisionType::Rect);
//	NewGameCol->SetupAttachment(Root);
//
//	SetRoot(Root);
//
//	InputOn();
//}
//
//UTitleText::~UTitleText()
//{
//}
//
//void UTitleText::BeginPlay()
//{
//	Super::BeginPlay();
//	UISpawn();
//
//}
//
//void UTitleText::Tick(float _DeltaTime)
//{
//	Super::Tick(_DeltaTime);
//	CollisionCheck();
//
//}
//
//void UTitleText::UISpawn()
//{
//	NewGame = CreateWidget<UTextWidget>(GetWorld(), "NewGame");
//	NewGame->AddToViewPort(2);
//	NewGame->SetScale(HoloCureConstValue::MultipleSize * 11);
//	NewGame->SetFont("Galmuri9");
//	NewGame->SetColor(Color8Bit::White);
//	NewGame->SetPosition(FVector(430.f, 220.f));
//	NewGame->SetText("새 게임");
//
//}
//
//void UTitleText::CollisionCheck()
//{
//	NewGameCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
//		{
//			NewGame->SetColor(Color8Bit::Black);
//			ColChack = true;
//
//		}
//	);
//	NewGameCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
//		{
//			NewGame->SetColor(Color8Bit::White);
//			ColChack = false;
//		}
//	);
//
//	if (true == IsDown(VK_LBUTTON) && true == ColChack)
//	{
//		GEngine->ChangeLevel("SelectLevel");
//	}
//	if (true == IsDown(VK_LBUTTON) && true == ExitChack)
//	{
//		GEngine->EngineWindow.Off();
//	}
//
//}


UTitleText::UTitleText()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Collision");

	NewGameCol = CreateDefaultSubObject<UCollision>("Collision");
	NewGameCol->SetScale({ 340.0f, 50.0f });
	NewGameCol->SetPosition(FVector(430.f, 220.f));
	NewGameCol->SetCollisionGroup(ECollisionOrder::Menu);
	NewGameCol->SetCollisionType(ECollisionType::Rect);
	NewGameCol->SetupAttachment(Root);

	HoloHouseCol = CreateDefaultSubObject<UCollision>("Collision");
	HoloHouseCol->SetScale({ 340.0f, 50.0f });
	HoloHouseCol->SetPosition(FVector(430.f, 150.f));
	HoloHouseCol->SetCollisionGroup(ECollisionOrder::Menu);
	HoloHouseCol->SetCollisionType(ECollisionType::Rect);
	HoloHouseCol->SetupAttachment(Root);

	ShopCol = CreateDefaultSubObject<UCollision>("Collision");
	ShopCol->SetScale({ 340.0f, 50.0f });
	ShopCol->SetPosition(FVector(430.f, 80.f));
	ShopCol->SetCollisionGroup(ECollisionOrder::Menu);
	ShopCol->SetCollisionType(ECollisionType::Rect);
	ShopCol->SetupAttachment(Root);

	ScoreboardCol = CreateDefaultSubObject<UCollision>("Collision");
	ScoreboardCol->SetScale({ 340.0f, 50.0f });
	ScoreboardCol->SetPosition(FVector(430.f, 10.f));
	ScoreboardCol->SetCollisionGroup(ECollisionOrder::Menu);
	ScoreboardCol->SetCollisionType(ECollisionType::Rect);
	ScoreboardCol->SetupAttachment(Root);

	ChallengeCol = CreateDefaultSubObject<UCollision>("Collision");
	ChallengeCol->SetScale({ 340.0f, 50.0f });
	ChallengeCol->SetPosition(FVector(430.0f, -60.f));
	ChallengeCol->SetCollisionGroup(ECollisionOrder::Menu);
	ChallengeCol->SetCollisionType(ECollisionType::Rect);
	ChallengeCol->SetupAttachment(Root);

	SettingCol = CreateDefaultSubObject<UCollision>("Collision");
	SettingCol->SetScale({ 340.0f, 50.0f });
	SettingCol->SetPosition(FVector(430.0f, -130.f));
	SettingCol->SetCollisionGroup(ECollisionOrder::Menu);
	SettingCol->SetCollisionType(ECollisionType::Rect);
	SettingCol->SetupAttachment(Root);

	ProducerCol = CreateDefaultSubObject<UCollision>("Collision");
	ProducerCol->SetScale({ 340.0f, 50.0f });
	ProducerCol->SetPosition(FVector(430.0f, -200.f));
	ProducerCol->SetCollisionGroup(ECollisionOrder::Menu);
	ProducerCol->SetCollisionType(ECollisionType::Rect);
	ProducerCol->SetupAttachment(Root);

	ExitCol = CreateDefaultSubObject<UCollision>("Collision");
	ExitCol->SetScale({ 340.0f, 50.0f });
	ExitCol->SetPosition(FVector(430.0f, -270.f));
	ExitCol->SetCollisionGroup(ECollisionOrder::Menu);
	ExitCol->SetCollisionType(ECollisionType::Rect);
	ExitCol->SetupAttachment(Root);

	SetRoot(Root);
	InputOn();
}

UTitleText::~UTitleText()
{
}

void UTitleText::BeginPlay()
{
	Super::BeginPlay();
	UISpawn();
	Sound = UEngineSound::SoundPlay("TitleBGM.mp3");
	Sound.On();
}

void UTitleText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CollisionCheck();


}

void UTitleText::UISpawn()
{
	NewGame = CreateWidget<UTextWidget>(GetWorld(), "NewGame");
	NewGame->AddToViewPort(2);
	NewGame->SetScale(ContentsValue::MultipleSize * 11);
	NewGame->SetFont("Galmuri9");
	NewGame->SetColor(Color8Bit::White);
	NewGame->SetPosition(FVector(430.f, 220.f));
	NewGame->SetText("새 게임");

	HoloHouse = CreateWidget<UTextWidget>(GetWorld(), "HoloHouse");
	HoloHouse->AddToViewPort(2);
	HoloHouse->SetScale(ContentsValue::MultipleSize * 11);
	HoloHouse->SetFont("Galmuri9");
	HoloHouse->SetColor(Color8Bit::White);
	HoloHouse->SetPosition(FVector(430.f, 150.f));
	HoloHouse->SetText("홀로하우스");

	Shop = CreateWidget<UTextWidget>(GetWorld(), "Shop");
	Shop->AddToViewPort(2);
	Shop->SetScale(ContentsValue::MultipleSize * 11);
	Shop->SetFont("Galmuri9");
	Shop->SetColor(Color8Bit::White);
	Shop->SetPosition(FVector(430.f, 80.f));
	Shop->SetText("상점");

	Scoreboard = CreateWidget<UTextWidget>(GetWorld(), "Scoreboard");
	Scoreboard->AddToViewPort(2);
	Scoreboard->SetScale(ContentsValue::MultipleSize * 11);
	Scoreboard->SetFont("Galmuri9");
	Scoreboard->SetColor(Color8Bit::White);
	Scoreboard->SetPosition(FVector(430.f, 10.f));
	Scoreboard->SetText("점수판");

	Challenge = CreateWidget<UTextWidget>(GetWorld(), "Challenge");
	Challenge->AddToViewPort(2);
	Challenge->SetScale(ContentsValue::MultipleSize * 11);
	Challenge->SetFont("Galmuri9");
	Challenge->SetColor(Color8Bit::White);
	Challenge->SetPosition(FVector(430.0f, -60.f));
	Challenge->SetText("도전과제");

	Setting = CreateWidget<UTextWidget>(GetWorld(), "Setting");
	Setting->AddToViewPort(2);
	Setting->SetScale(ContentsValue::MultipleSize * 11);
	Setting->SetFont("Galmuri9");
	Setting->SetColor(Color8Bit::White);
	Setting->SetPosition(FVector(430.0f, -130.f));
	Setting->SetText("설정");

	Producer = CreateWidget<UTextWidget>(GetWorld(), "Producer");
	Producer->AddToViewPort(2);
	Producer->SetScale(ContentsValue::MultipleSize * 11);
	Producer->SetFont("Galmuri9");
	Producer->SetColor(Color8Bit::White);
	Producer->SetPosition(FVector(430.0f, -200.f));
	Producer->SetText("제작사");

	Exit = CreateWidget<UTextWidget>(GetWorld(), "Exit");
	Exit->AddToViewPort(2);
	Exit->SetScale(ContentsValue::MultipleSize * 11);
	Exit->SetFont("Galmuri9");
	Exit->SetColor(Color8Bit::White);
	Exit->SetPosition(FVector(430.0f, -270.f));
	Exit->SetText("나가기");

}

void UTitleText::CollisionCheck()
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

	HoloHouseCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			HoloHouse->SetColor(Color8Bit::Black);
		}
	);
	HoloHouseCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			HoloHouse->SetColor(Color8Bit::White);
		}
	);

	ShopCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Shop->SetColor(Color8Bit::Black);
		}
	);
	ShopCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Shop->SetColor(Color8Bit::White);
		}
	);

	ScoreboardCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Scoreboard->SetColor(Color8Bit::Black);
		}
	);
	ScoreboardCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Scoreboard->SetColor(Color8Bit::White);
		}
	);

	ChallengeCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Challenge->SetColor(Color8Bit::Black);
		}
	);
	ChallengeCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Challenge->SetColor(Color8Bit::White);
		}
	);

	SettingCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Setting->SetColor(Color8Bit::Black);
		}
	);
	SettingCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Setting->SetColor(Color8Bit::White);
		}
	);

	ProducerCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Producer->SetColor(Color8Bit::Black);
		}
	);
	ProducerCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Producer->SetColor(Color8Bit::White);
		}
	);

	ExitCol->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Exit->SetColor(Color8Bit::Black);
			ExitChack = true;

		}
	);
	ExitCol->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			Exit->SetColor(Color8Bit::White);
			ExitChack = false;
		}
	);
	
	if (true == IsDown(VK_LBUTTON) && true == ColChack)
	{
		GEngine->CreateLevel<APlayGameMode>("PlayLevel");
		GEngine->ChangeLevel("PlayLevel");
		Sound.Off();
	}
	if (true == IsDown(VK_LBUTTON) && true == ExitChack)
	{
		GEngine->EngineWindow.Off();
	}
}

