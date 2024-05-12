#include "PreCompile.h"
#include "TitleBack.h"

ATitleBack::ATitleBack()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	TitleBack = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	TitleBack->SetupAttachment(Root);
	TitleBack->SetPivot(EPivot::BOT);

	SetRoot(Root);

}

ATitleBack::~ATitleBack()
{
}

void ATitleBack::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));
	TitleBack->SetSprite("menu_charselec_bar_0.png");
	TitleBack->SetScale(FVector{ 1.0f,3.5f });
	TitleBack->SetPosition(FVector{ 1.5f,0.0f });
	TitleBack->SetOrder(ERenderingOrder::Title);
	TitleBack->SetRotationDeg({ 0.0f,0.0f,-10.0f });

	DelayCallBack(8.0f, [=]()
		{
			Destroy();
		});

}

void ATitleBack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BackMove(_DeltaTime);

}

void ATitleBack::BackMove(float _DeltaTime)
{
	TitleBack->AddPosition(FVector::Left * _DeltaTime * MoveSpeed);


}
