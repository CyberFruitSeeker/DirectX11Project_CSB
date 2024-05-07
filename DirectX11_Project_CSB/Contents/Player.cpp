#include "PreCompile.h"
#include "Player.h"
#include <EngineBase/EngineMath.h>
#include "HoloMouse.h"
#include "HoloCureConstValue.h"
#include "Gura.h"

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
	//CreatePlayerAnimation("Matsuri");



	Renderer->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	Renderer->SetOrder(ERenderingOrder::Player);

	Collision->SetPosition({ GetActorLocation().X,GetActorLocation().Y + (10.0f * HoloCureConstValue::MultipleSize) });


	// ȭ��ǥ
	ArrowCursor->SetSprite("Arrow_1.png");
	ArrowCursor->SetAutoSize(1.0f, true);
	ArrowCursor->SetOrder(ERenderingOrder::Mouse);
	ArrowCursor->SetPosition(FVector{ PlayerPos.X, PlayerPos.Y + (20.0f * HoloCureConstValue::MultipleSize) });



	//FVector MyCursor = FVector{ PlayerPos.X, PlayerPos.Y + 20.0f };
	//ArrowCursor->SetPosition(MyCursor);

	// �÷��̾� ���� ����Ʈ ����
	AddWeapon<AGura>("AGura");


	StateUpdate();

}

void APlayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��Ҷ��� �ִ�.
	Super::Tick(_DeltaTime);

	PlayerState.Update(_DeltaTime);

	PlayerPos = GetActorLocation();
	//PlayerPos= float4{ PlayerColPos.X, PlayerColPos.Y + (20.0f * HoloCureConstValue::MultipleSize) };

	PlayerCursorDirCheck();
	ChangeMouseAimAttackDir();
	ArrowCursorChange();
	//PlayerCollisionInteractiveToMonster();

	{
		for (VPlayerWeaponsIter = VPlayerWeapons.begin(); VPlayerWeaponsIter != VPlayerWeapons.end(); ++VPlayerWeaponsIter)
		{
			std::shared_ptr<AWeapon> Weapon = *VPlayerWeaponsIter;

			*VPlayerWeaponsIter = Weapon;
		}

	}




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
			Angle = 90.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::NE:
			Angle = 45.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::E:
			Angle = 0.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::SE:
			Angle = 315.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::S:
			Angle = 270.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::SW:
			Angle = 225.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::W:
			Angle = 180.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
			break;
		case EPlayerDir::NW:
			Angle = 135.0f;
			ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });
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
		Angle = atan2f((HoloCureConstValue::PlayLevelMousePos.Y - APlayer::PlayerPos.Y),
			(HoloCureConstValue::PlayLevelMousePos.X - APlayer::PlayerPos.X)) * 180.0f / UEngineMath::PI;
		ArrowCursor->SetRotationDeg(FVector{ 0.0f, 0.0f, Angle });

		if (-90.0f <= Angle && 90.0f > Angle)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
		}
	}
}

void APlayer::PlayerCollisionInteractiveToMonster()
{
	// �÷��̾ ���͵��̶� �ݸ��� ��ȣ�ۿ��� �Ͼ�� : �켱�� ������� �غ���.
	Collision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision>_collision)
		{
			_collision->GetActor()->Destroy();
		}
	);


}

template<typename WeaponType>
void APlayer::AddWeapon(std::string _Name)
{
	std::shared_ptr<AWeapon> Weapon = GetWorld()->SpawnActor<WeaponType>(_Name);
	VPlayerWeapons.push_back(Weapon);
}






