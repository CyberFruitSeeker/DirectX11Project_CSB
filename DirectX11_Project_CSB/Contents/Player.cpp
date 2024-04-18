#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// 플레이어의 FVector를 초기화 해준다.
FVector APlayer::PlayerPosZero = FVector::Zero;

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	AttackDir = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	AttackDir->SetupAttachment(Root);
	AttackDir->SetPivot(EPivot::MAX);

	SetRoot(Root);
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 캐릭터 클래스를 여러개 생성하지 말고, 여기에다 구현해본다.
	// 캐릭터 이름으로 간단하게 변경하는 방식
	CreatePlayerAnimation("Gura");

	
	/*Renderer->CreateAnimation("GuraIdle", "Gura", 0.3f, true, (0,1),(1,2));
	Renderer->CreateAnimation("GuraRun", "Gura", 0.065f, true, (3,4,5),(6,7,8));*/
	
	Renderer->SetAutoSize(1.5f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	StateUpdate();
	
}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);
	
	PlayerPosZero = GetActorLocation();

	PlayerCursorDirCheck();

	ChangeMouseAimAttackDir();


}

// 문자열을 사용한 Idle과 Run 애니메이션 구분 및 발동
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.3f, true, (0, 1), (1, 2));
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, (3, 4, 5), (6, 7, 8));
}

// 키입력과 플레이어의 방향에 따른 Arrow Dir의 변화 
void APlayer::PlayerCursorDirCheck()
{
	// None 상태를 설정해주고
	EPlayerDir InputDir = EPlayerDir::None;

	// 키 입력이 처음 들어올때
	if (true == IsDown('W'))
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,90.0f });
		InputDir = EPlayerDir::N;
	}
	if (true == IsDown('S'))
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,270.0f });
		InputDir = EPlayerDir::S;
	}
	if (true == IsDown('A'))
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,180.0f });
		InputDir = EPlayerDir::W;
	}
	if (true == IsDown('D'))
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,0.0f });
		InputDir = EPlayerDir::E;
	}


	// 두 키를 동시에 입력 == 남서, 북서, 북동, 남동쪽으로 갈때
	if (PlayerDir == EPlayerDir::NE)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,45.0f });
		InputDir = EPlayerDir::E;
	}

	if (PlayerDir == EPlayerDir::SE)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,315.0f });
		InputDir = EPlayerDir::E;
	}

	if (PlayerDir == EPlayerDir::SW)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,225.0f });
		InputDir = EPlayerDir::W;
	}

	if (PlayerDir == EPlayerDir::NW)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,135.0f });
		InputDir = EPlayerDir::W;
	}


	// 한 키만 눌렀을때 == 한 방향으로 갈때
	if (PlayerDir == EPlayerDir::N)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,90.0f });
	}

	if (PlayerDir == EPlayerDir::S)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,270.0f });
	}

	if (PlayerDir == EPlayerDir::W)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,180.0f });
	}

	if (PlayerDir == EPlayerDir::E)
	{
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,0.0f });
	}


}

void APlayer::ChangeMouseAimAttackDir()
{
	if (true == AHoloMouse::MouseAimOn)
	{
		PlayerAngle = atan2f((HoloCureConstValue::PlayLevelMousePos.Y - APlayer::PlayerPosZero.Y), (HoloCureConstValue::PlayLevelMousePos.X - APlayer::PlayerPosZero.X)) * 180.0f / UEngineMath::PI;
		PlayerCursor->SetRotationDeg(FVector{ 0.0f,0.0f,PlayerAngle });

		if (-90.0f <= PlayerAngle && 90.0f > PlayerAngle)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
		}


	}
}



