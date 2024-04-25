#include "PreCompile.h"
#include "Melee.h"

EPlayerDir AMelee::PlayerDir = EPlayerDir::None;

AMelee::AMelee()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::MAX);

	SetRoot(Root);

}

AMelee::~AMelee()
{
}

void AMelee::BeginPlay()
{
}

void AMelee::Tick(float _DeltaTime)
{
}

void AMelee::CursorOff()
{
}

void AMelee::AttackDir()
{
}

void AMelee::AttackAimDir()
{
}

void AMelee::MeleeAttack(float _DeltaTime)
{
}



