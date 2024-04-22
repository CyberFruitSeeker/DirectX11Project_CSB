#include "PreCompile.h"
#include "Player.h"
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// �÷��̾��� FVector�� �ʱ�ȭ ���ش�.
FVector APlayer::PlayerPos = FVector::Zero;

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	ArrowCursor = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	ArrowCursor->SetupAttachment(Root);
	ArrowCursor->SetPivot(EPivot::MAX);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionOrder::Player);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	//UEngineSerializer Serial;
	//Serial << this;



	// �÷��̾� ĳ���� Ŭ������ ������ �������� ����, ���⿡�� �����غ���.
	// ĳ���� �̸����� �����ϰ� �����ϴ� ���
	CreatePlayerAnimation("Gura");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	// ȭ��ǥ
	ArrowCursor->SetSprite("Arrow_1.png");
	ArrowCursor->SetAutoSize(1.0f, true);
	ArrowCursor->SetOrder(ERenderingOrder::Player);



	FVector MyCursor = FVector{ PlayerPos.X, PlayerPos.Y + 20.0f };
	ArrowCursor->SetPosition(MyCursor);



	StateUpdate();

}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);

	PlayerPos = GetActorLocation();

	PlayerCursorDirCheck();
	ChangeMouseAimAttackDir();
	ArrowCursorChange();

}

// ���ڿ��� ����� Idle�� Run �ִϸ��̼� ���� �� �ߵ�
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.3f, true, (0, 1), (1, 2));
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, (3, 4, 5), (6, 7, 8));
}

void APlayer::ArrowCursorChange()
{
	if (false == AHoloMouse::MouseCursorOn)
	{
		ArrowCursor->SetSprite("Arrow_1.png");
		ArrowCursor->SetAutoSize(1.0f, true);
	}
	if (true == AHoloMouse::MouseCursorOn)
	{
		ArrowCursor->SetSprite("Arrow_2.png");
		ArrowCursor->SetAutoSize(1.0f, true);
	}
}

// Ű�Է°� �÷��̾��� ���⿡ ���� Arrow Dir�� ��ȭ 
void APlayer::PlayerCursorDirCheck()
{
	// None ���¸� �������ְ�
	EPlayerDir InputDir = EPlayerDir::None;

	// Ű �Է��� ó�� ���ö�
	if (true == IsDown('W'))
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,90.0f });
		InputDir = EPlayerDir::N;
	}
	if (true == IsDown('S'))
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,270.0f });
		InputDir = EPlayerDir::S;
	}
	if (true == IsDown('A'))
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,180.0f });
		InputDir = EPlayerDir::W;
	}
	if (true == IsDown('D'))
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,0.0f });
		InputDir = EPlayerDir::E;
	}


	// �� Ű�� ���ÿ� �Է� == ����, �ϼ�, �ϵ�, ���������� ����
	if (DirState == EPlayerDir::NE)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,45.0f });
		InputDir = EPlayerDir::E;
	}

	if (DirState == EPlayerDir::SE)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,315.0f });
		InputDir = EPlayerDir::E;
	}

	if (DirState == EPlayerDir::SW)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,225.0f });
		InputDir = EPlayerDir::W;
	}

	if (DirState == EPlayerDir::NW)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,135.0f });
		InputDir = EPlayerDir::W;
	}


	// �� Ű�� �������� == �� �������� ����
	if (DirState == EPlayerDir::N)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,90.0f });
	}

	if (DirState == EPlayerDir::S)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,270.0f });
	}

	if (DirState == EPlayerDir::W)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,180.0f });
	}

	if (DirState == EPlayerDir::E)
	{
		ArrowCursor->SetRotationDeg(FVector{ 0.0f,0.0f,0.0f });
	}


}

void APlayer::ChangeMouseAimAttackDir()
{
	if (true == AHoloMouse::MouseCursorOn)
	{
		PlayerAngle = atan2f((HoloCureConstValue::PlayLevelMousePos.Y - APlayer::PlayerPos.Y),
			(HoloCureConstValue::PlayLevelMousePos.X - APlayer::PlayerPos.X)) * 180.0f / UEngineMath::PI;
		ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });

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



