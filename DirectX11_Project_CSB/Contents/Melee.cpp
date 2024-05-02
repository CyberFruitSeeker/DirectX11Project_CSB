#include "PreCompile.h"
#include "Melee.h"



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
	Super::BeginPlay();

	



}


void AMelee::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	


}

void AMelee::SetKnifeTypeMeleeLocation(float _DistanceFromPlayer)
{
	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;

	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y });
	AddActorLocation(Dir * _DistanceFromPlayer * HoloCureConstValue::MultiPleSize);
}

void AMelee::SetReachTypeMeleeLocation(float _DistanceFromPlayer)
{

}



