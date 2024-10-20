#include "PreCompile.h"
#include "Melee.h"



AMelee::AMelee()
{
	


	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::MAX);

	POARenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	POARenderer->SetupAttachment(Root);
	POARenderer->SetPivot(EPivot::MAX);

	SetRoot(Root);

}

AMelee::~AMelee()
{
}

void AMelee::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetOrder(ERenderingOrder::Attack);
	
	// 구라가 쓰는 POA
	//POARenderer->SetOrder(ERenderingOrder::Back);
}


void AMelee::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//공격이 보일때
	if (true == Renderer->IsActive())
	{
		//공격 애니메이션이 종료된 직후
		if (true == Renderer->IsCurAnimationEnd())
		{
			Renderer->SetActive(false);
		}
		else
		{
			int a = 0;
		}
	}
	else // 공격이 실행되지 않을 때
	{
		Angle = APlayGameMode::MainPlayer->GetAngle();
		if (0 < Delay) // 공격 쿨이 돌기 전
		{
			Renderer->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			Delay -= _DeltaTime;
		}
		else // 공격 시작
		{
			Delay = APlayGameMode::MainPlayer->GetAtkTime();
			Renderer->SetActive(true);
		}
	}


}

void AMelee::SetKnifeTypeMeleeLocation(float _DistanceFromPlayer)
{
	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;

	SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y });
	AddActorLocation(Dir * _DistanceFromPlayer * ContentsValue::MultipleSize);
}

// 구라가 쓸 거리 타입의 공격
void AMelee::SetReachTypeMeleeLocation(float _DistanceFromPlayer)
{
	Dir = float4::DegToDir(Angle);
	Dir.Z = 0.0f;

	//SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y });
	//SetActorLocation(FVector{ APlayer::PlayerPos.X - 15.0f, APlayer::PlayerPos.Y + 20.0f});
	SetActorLocation(FVector{ APlayer::PlayerPos.X * 1.0f, APlayer::PlayerPos.Y * 1.0f });
	AddActorLocation(Dir * _DistanceFromPlayer * ContentsValue::MultipleSize);
	
}



