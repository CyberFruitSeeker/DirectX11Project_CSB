#include "PreCompile.h"
#include "Button.h"

AButton::AButton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	MenuRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	MenuRenderer->SetupAttachment(Root);
	MenuRenderer->SetPivot(EPivot::MAX);
	MenuRenderer->SetOrder(ERenderingOrder::Menu);


	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetScale({ 340.0f, 50.0f });
	Collision->SetCollisionGroup(ECollisionOrder::Menu);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetupAttachment(Root);

	SetRoot(Root);
}

AButton::~AButton()
{
}

void AButton::BeginPlay()
{
	Super::BeginPlay();
	MenuRenderer->SetSprite("hud_OptionButton_0.png");
	MenuRenderer->SetAutoSize(2.0f, true);

	Sound = UEngineSound::SoundPlay("ButtonMove.wav");
	Sound.SetVolume(10);
	Sound.Off();

}

void AButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CollisionCheck();
}

void AButton::CollisionCheck()
{
	Collision->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			MenuRenderer->SetSprite("hud_OptionButton_1.png");
			Sound.On();
		}

	);
	Collision->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
		{
			MenuRenderer->SetSprite("hud_OptionButton_0.png");
		}
	);

}
