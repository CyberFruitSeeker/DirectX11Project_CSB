#include "PreCompile.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

}

ATitleLogo::~ATitleLogo()
{
}


void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(700.0f, 300.0f, 100.0f));

	// Renderer->SetSprite("CharWalk1_0.png");

	Renderer->CreateAnimation("Gura_Run_0", "Gura_Run_1", 0.1f);

	Renderer->ChangeAnimation("Gura_Run_2");

}

void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int a = 0;
}
