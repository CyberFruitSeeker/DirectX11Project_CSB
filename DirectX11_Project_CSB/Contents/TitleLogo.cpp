#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	{
		SetActorScale3D(FVector(1300.0f, 600.0f, 100.0f));
		Renderer->SetSprite("HoloCureTitle.png");

	}

	//{
	//	Renderer->SetSprite("Gura_Title.png");
	//	SetActorScale3D(FVector(210.0f, 200.0f, 100.0f));
	//}


}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int a = 0;
}
