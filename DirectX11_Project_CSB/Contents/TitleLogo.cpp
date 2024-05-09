#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackRenderer->SetupAttachment(Root);

	SetRoot(Root);
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("HoloTitle.png");
	Renderer->SetAutoSize(0.7f, true);
	Renderer->SetPosition(FVector({ -150.0f,-60.0f }));
	Renderer->SetOrder(ERenderingOrder::Title);

	BackRenderer->SetSprite("menu_charselecBG_0.png");
	BackRenderer->SetAutoSize(10.0f, true);
	BackRenderer->SetOrder(ERenderingOrder::Back);

	//{
	//	SetActorScale3D(FVector(1300.0f, 600.0f, 100.0f));
	//	Renderer->SetSprite("HoloCureTitle.png");

	//}

}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Move(_DeltaTime);

	int a = 0;
}

void ATitleLogo::Move(float _DeltaTime)
{
	if (0.0f <= LogoMoveTime && LogoMoveTime < 1.3f)
	{
		Renderer->AddPosition(LogoMove * _DeltaTime);
	}
	if (1.4f <= LogoMoveTime && LogoMoveTime < 2.7f)
	{
		Renderer->AddPosition(LogoMove * -1 * _DeltaTime);
	}
	if (2.8f <= LogoMoveTime)
	{
		LogoMoveTime = 0.0f;
	}
	LogoMoveTime += _DeltaTime;

}
