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
		SetActorScale3D(FVector(615.0f, 259.0f, 100.0f));
		Renderer->SetSprite("HoloCureTitle_full.png");

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
