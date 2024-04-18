#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// �÷��̾��� FVector�� �ʱ�ȭ ���ش�.
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

	// �÷��̾� ĳ���� Ŭ������ ������ �������� ����, ���⿡�� �����غ���.
	// ĳ���� �̸����� �����ϰ� �����ϴ� ���
	CreatePlayerAnimation("Gura");

	
	/*Renderer->CreateAnimation("GuraIdle", "Gura", 0.3f, true, (0,1),(1,2));
	Renderer->CreateAnimation("GuraRun", "Gura", 0.065f, true, (3,4,5),(6,7,8));*/
	
	Renderer->SetAutoSize(1.5f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	StateUpdate();
	
}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);
	
	PlayerPosZero = GetActorLocation();

	PlayerCursorDirCheck();

	ChangeMouseAimAttackDir();


}

// ���ڿ��� ����� Idle�� Run �ִϸ��̼� ���� �� �ߵ�
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.3f, true, (0, 1), (1, 2));
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, (3, 4, 5), (6, 7, 8));
}

// Ű�Է°� �÷��̾��� ���⿡ ���� Arrow Dir�� ��ȭ 
void APlayer::PlayerCursorDirCheck()
{
	// None ���¸� �������ְ�
	EPlayerDir InputDir = EPlayerDir::None;

	// Ű �Է��� ó�� ���ö�
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


	// �� Ű�� ���ÿ� �Է� == ����, �ϼ�, �ϵ�, ���������� ����
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


	// �� Ű�� �������� == �� �������� ����
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



