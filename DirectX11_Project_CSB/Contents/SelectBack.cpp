#include "PreCompile.h"
#include "SelectBack.h"

ASelectBack::ASelectBack()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SelectBack = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SelectBack->SetupAttachment(Root);
	SelectBack->SetPivot(EPivot::BOT);

	SelectBackGround = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SelectBackGround->SetupAttachment(Root);


	SetRoot(Root);

}

ASelectBack::~ASelectBack()
{
}

void ASelectBack::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));
	SelectBack->SetSprite("menu_charselec_bar_0.png");
	SelectBack->SetScale(FVector{ 1.0f,3.5f });
	SelectBack->SetPosition(FVector{ 1.5f,0.0f });
	SelectBack->SetOrder(ERenderingOrder::Title);
	SelectBack->SetRotationDeg({ 0.0f,0.0f,-10.0f });


	SelectBack->DelayCallBack(8.0f, [=]()
		{
			Destroy();
		});


	SelectBackGround->SetSprite("menu_charselecBG_0.png");
	SelectBackGround->SetAutoSize(1.0f, true);
	SelectBackGround->SetOrder(ERenderingOrder::Back);

}

void ASelectBack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	BackMove(_DeltaTime);

}

void ASelectBack::BackMove(float _DeltaTime)
{
	SelectBack->AddPosition(FVector::Left * _DeltaTime * MoveSpeed);

}
