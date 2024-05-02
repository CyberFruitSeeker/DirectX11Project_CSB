#include "PreCompile.h"
#include "Melee.h"
#include "Player.h"
#include "HoloMouse.h"
#include "Ranged.h"

EPlayerDir AMelee::PlayerDir = EPlayerDir::None;

AMelee::AMelee()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::MAX);

	SetRoot(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 100.0f,100.f });

	Collision->SetCollisionGroup(ECollisionOrder::Weapon);
	Collision->SetCollisionType(ECollisionType::Rect);




}

AMelee::~AMelee()
{
}

void AMelee::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("GuraAttack", "GuraAttack", 0.10f, 0, 10);
	
	Renderer->SetAutoSize(1.5f, true);
	Renderer->ChangeAnimation("GuraAttack");
	Renderer->SetOrder(ERenderingOrder::Attack);



}

void AMelee::MeleeAttack(float _DeltaTime)
{
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
		Angle = AttackAngle;
		if (0 < Delay) // 공격 쿨이 돌기 전
		{
			Delay -= _DeltaTime;
		}
		else // 공격 시작
		{
			Delay = AttackTime;
			Renderer->SetActive(true);
		}
	}

}



void AMelee::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	MeleeAttack(_DeltaTime);
	if (false == AHoloMouse::MouseCursorOn)
	{
		AttackDir();
	}
	else
	{
		AttackDir();
	}

	CursorOff();

	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			_Collison->GetActor()->Destroy();
		}
	);


}

void AMelee::CursorOff()
{
	ShowCursor(FALSE);
}

void AMelee::AttackAimDir()
{
	FVector MyPos = GEngine->EngineWindow.GetScreenMousePos();
	FVector WolrdMyPos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(MyPos);

	AttackAngle = atan2f((HoloCureConstValue::PlayLevelMousePos.Y - APlayer::PlayerPos.Y),
		(HoloCureConstValue::PlayLevelMousePos.X - APlayer::PlayerPos.X)) * 180.0f / UEngineMath::PI;

	FVector Dir = WolrdMyPos - APlayer::PlayerPos;
	Dir.Normalize2D();
	Dir.Z = 0.0f;

	SetActorLocation(APlayer::PlayerPos);
	AddActorLocation(Dir * 100);
	SetActorLocation(FVector{ 0.0f,0.0f,AttackAngle });

	// 공격 애니메이션이 끝나면 다음이 나가게끔 한다.

}

void AMelee::AttackDir()
{

	if (PlayerDir == EPlayerDir::E)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X + 100 , APlayer::PlayerPos.Y + 20 });
		SetActorRotation(FVector{ 0.0f,0.0f,0.0f });
	}
	else if (PlayerDir == EPlayerDir::N)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y + 100 });
		SetActorRotation(FVector{ 0.0f,0.0f,90.0f });
	}
	else if (PlayerDir == EPlayerDir::S)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X, APlayer::PlayerPos.Y - 30 });
		SetActorRotation(FVector{ 0.0f,0.0f,270.0f });
	}
	else if (PlayerDir == EPlayerDir::W)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X - 100, APlayer::PlayerPos.Y + 20 });
		SetActorRotation(FVector{ 0.0f,0.0f,180.0f });
	}
	else if (PlayerDir == EPlayerDir::NE)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X + 100, APlayer::PlayerPos.Y + 70 });
		SetActorRotation(FVector{ 0.0f,0.0f,45.0f });
	}
	else if (PlayerDir == EPlayerDir::NW)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X - 100, APlayer::PlayerPos.Y + 70 });
		SetActorRotation(FVector{ 0.0f,0.0f,135.0f });
	}
	else if (PlayerDir == EPlayerDir::SE)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X + 100, APlayer::PlayerPos.Y - 30 });
		SetActorRotation(FVector{ 0.0f,0.0f,315.0f });
	}
	else if (PlayerDir == EPlayerDir::SW)
	{
		SetActorLocation(FVector{ APlayer::PlayerPos.X - 100, APlayer::PlayerPos.Y - 30 });
		SetActorRotation(FVector{ 0.0f,0.0f,225.0f });
	}


}





