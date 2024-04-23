#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"


AMonster::AMonster()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	SetRoot(Root);

	UCollision* Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 30.0f,30.0f });
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);

}

AMonster::~AMonster()
{
}


void AMonster::BeginPlay()
{
	Super::BeginPlay();

	CreateMonsterAnimation("Deadbeat");
	CreateMonsterAnimation("DeadbeatBat");
	CreateMonsterAnimation("DeadbeatGang");
	CreateMonsterAnimation("DeadbeatShield");
	CreateMonsterAnimation("Shrimp");
	CreateMonsterAnimation("ShrimpDark");
	CreateMonsterAnimation("Bubba");
	CreateMonsterAnimation("KFP");
	CreateMonsterAnimation("Takodachi");





	Renderer->SetAutoSize(1.0f, true);
	Renderer->ChangeAnimation(Name);
	Renderer->SetOrder(ERenderingOrder::MonsterUp);

}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	MonsterPosDirSet(_DeltaTime);

}

void AMonster::CreateMonsterAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.25f, true, (0, 1),(1,2));
}

void AMonster::MonsterPosDirSet(float _DeltaTime)
{
	FVector MonsterPos = GetActorLocation();
	FVector MonsterDir = APlayer::PlayerPos - MonsterPos;
	FVector MonsterDirNormal = MonsterDir.Normalize2DReturn();
	AddActorLocation(MonsterDirNormal * _DeltaTime * MoveSpeed);
	if (MonsterPos.X > APlayer::PlayerPos.X)
	{
		Renderer->SetDir(EEngineDir::Left);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}

}

void AMonster::SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType)
{
	Hp = _Hp;
	Atk = _Atk;
	Speed = _Speed;
	CalSpeed = 200.0f * Speed;
	Exp = _Exp;
	MoveType = _MoveType;
}

FVector AMonster::CreateGroupToPlayerDir()
{
	// 몬스터들이 플레이어의 거리 사이가 줄어들면서 점점 다가간다.
	FVector MonsterGroupDir = APlayer::PlayerPos - GetActorLocation();
	MonsterGroupDir = MonsterGroupDir.Normalize2DReturn();
	return MonsterGroupDir;
}

void AMonster::CheckPosComparePlayer()
{
	if (APlayer::PlayerPos.Y<=GetActorLocation().Y)
	{
		Renderer->SetOrder(ERenderingOrder::MonsterUp);
	}
	else
	{
		Renderer->SetOrder(ERenderingOrder::MonsterDown);
	}

}

void AMonster::Move(float _DeltaTime, EMonsterMoveType _MoveType)
{
	FVector MonsterPos = GetActorLocation();

	// 전에 사용해봤던 방식과 비슷하게 FSM을 사용해본다.
	switch (_MoveType)
	{
	case EMonsterMoveType::Follow:
		Dir = APlayer::PlayerPos - MonsterPos;
		Dir = Dir.Normalize2DReturn();
		break;
	case EMonsterMoveType::StraightToPlayer:
		Dir = GoToPlayerDir;
		break;
	case EMonsterMoveType::StraightToUp:
		break;
	case EMonsterMoveType::StraightToDown:
		break;
	case EMonsterMoveType::StraightToRight:
		break;
	case EMonsterMoveType::StraightToLeft:
		break;
	case EMonsterMoveType::Stop:
		break;
	default:
		break;
	}

	AddActorLocation(Dir * _DeltaTime * CalSpeed);
}


