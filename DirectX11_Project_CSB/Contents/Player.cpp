#include "PreCompile.h"
#include "Player.h"
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"

// �÷��̾��� FVector�� �ʱ�ȭ ���ش�.
float4 APlayer::PlayerPos = float4::Zero;
float4 APlayer::PlayerColPos = float4::Zero;

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
	Collision->SetScale({ 10.0f,10.0f });
	Collision->SetPosition({ 0.0f,35.0f });
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

	UEngineSerializer Serial;
	Serial << this;



	// �÷��̾� ĳ���� Ŭ������ ������ �������� ����, ���⿡�� �����غ���.
	// ĳ���� �̸����� �����ϰ� �����ϴ� ���
	CreatePlayerAnimation("Gura");
	CreatePlayerAnimation("Matsuri");



	Renderer->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	Renderer->SetOrder(ERenderingOrder::Player);

	Collision->SetPosition({ GetActorLocation().X,GetActorLocation().Y + (10.0f * HoloCureConstValue::MultipleSize) });


	// ȭ��ǥ
	ArrowCursor->SetSprite("Arrow_1.png");
	ArrowCursor->SetAutoSize(1.0f, true);
	ArrowCursor->SetOrder(ERenderingOrder::MouseCursor);
	ArrowCursor->SetPosition(FVector{ PlayerPos.X, PlayerPos.Y + (20.0f * HoloCureConstValue::MultipleSize) });



	//FVector MyCursor = FVector{ PlayerPos.X, PlayerPos.Y + 20.0f };
	//ArrowCursor->SetPosition(MyCursor);

	// �÷��̾� ���� ����Ʈ ����


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
	//PlayerCollisionInteractiveToMonster();



}

// ���ڿ��� ����� Idle�� Run �ִϸ��̼� ���� �� �ߵ�
void APlayer::CreatePlayerAnimation(std::string _Name)
{
	// ���� ������ �̹��� �ε���
	Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.2f, true, 0, 2);
	Renderer->CreateAnimation(_Name + "_Run", _Name, 0.065f, true, 3, 8);
}

void APlayer::ArrowCursorChange()
{
	if (false == AHoloMouse::MouseCursorOn)
	{
		ArrowCursor->SetSprite("Arrow_1.png");
		ArrowCursor->SetAutoSize(2.0f, true);
	}
	if (true == AHoloMouse::MouseCursorOn)
	{
		ArrowCursor->SetSprite("Arrow_2.png");
		ArrowCursor->SetAutoSize(2.0f, true);
	}
}

void APlayer::CalStatus()
{
	AtkTime = roundf(1.0f / (1.0f + Haste));

	CalSpeed = HoloCureConstValue::BaseSpeed * Speed;
	LineSpeed = CalSpeed * 0.75f;

}

// Ű�Է°� �÷��̾��� ���⿡ ���� Arrow Dir�� ��ȭ 
void APlayer::PlayerCursorDirCheck()
{
	if (false == AHoloMouse::MouseCursorOn)
	{
		switch (DirState)
		{
		case EPlayerDir::N:
			PlayerAngle = 90.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::NE:
			PlayerAngle = 45.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::E:
			PlayerAngle = 0.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::SE:
			PlayerAngle = 315.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::S:
			PlayerAngle = 270.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::SW:
			PlayerAngle = 225.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::W:
			PlayerAngle = 180.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		case EPlayerDir::NW:
			PlayerAngle = 135.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, PlayerAngle });
			break;
		default:
			break;
		}
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

//void APlayer::PlayerCollisionInteractiveToMonster()
//{
//	// �÷��̾ ���͵��̶� �ݸ��� ��ȣ�ۿ��� �Ͼ�� : �켱�� ������� �غ���.
//	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision>_collision)
//		{
//			//_collision->GetActor()->Destroy();
//		}
//	);
//
//
//}







