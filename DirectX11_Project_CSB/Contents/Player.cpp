#include "PreCompile.h"
#include "Player.h"
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// 플레이어의 FVector를 초기화 해준다.
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



	// 플레이어 캐릭터 클래스를 여러개 생성하지 말고, 여기에다 구현해본다.
	// 캐릭터 이름으로 간단하게 변경하는 방식
	CreatePlayerAnimation("Gura");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Player);


	// 화살표
	ArrowCursor->SetSprite("Arrow_1.png");
	ArrowCursor->SetAutoSize(1.0f, true);
	ArrowCursor->SetOrder(ERenderingOrder::Player);



	FVector MyCursor = FVector{ PlayerPos.X, PlayerPos.Y + 20.0f };
	ArrowCursor->SetPosition(MyCursor);



	StateUpdate();

}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);

	PlayerPos = GetActorLocation();

	PlayerCursorDirCheck();
	ChangeMouseAimAttackDir();
	ArrowCursorChange();

}

// 문자열을 사용한 Idle과 Run 애니메이션 구분 및 발동
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

// 키입력과 플레이어의 방향에 따른 Arrow Dir의 변화 
void APlayer::PlayerCursorDirCheck()
{
	// None 상태를 설정해주고
	EPlayerDir InputDir = EPlayerDir::None;

	// 키 입력이 처음 들어올때
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


	// 두 키를 동시에 입력 == 남서, 북서, 북동, 남동쪽으로 갈때
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


	// 한 키만 눌렀을때 == 한 방향으로 갈때
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



