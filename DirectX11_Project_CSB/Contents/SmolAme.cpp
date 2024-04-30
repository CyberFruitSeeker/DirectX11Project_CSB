#include "PreCompile.h"
#include "SmolAme.h"
#include "Player.h"

ASmolAme::ASmolAme()
{
}

ASmolAme::~ASmolAme()
{
}

void ASmolAme::BeginPlay()
{
	Super::BeginPlay();




	StateUpdate();
}

void ASmolAme::Tick(float _DeltaTime)
{



}



// ���� �Ƹ��� ����(���º�ȭ) :
// Walk => Jump => Jumping(circle shadow) => GroundPound => Walk

void ASmolAme::StateUpdate()
{

}

void ASmolAme::SmolAmeWalk(std::string _Name)
{

}

void ASmolAme::SmolAmeJumpStart()
{
}

void ASmolAme::SmolAmeJump(std::string _Name)
{
}

void ASmolAme::SmolAmeJumping(std::string _Name)
{
}

void ASmolAme::SmolAmeGroundPound(std::string _Name)
{
}

void ASmolAme::SmolAmeWalkStart()
{
}

void ASmolAme::CreateSmolAmeAnimation(std::string _Name)
{

}




void ASmolAme::SmolAmeStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType)
{
}

FVector ASmolAme::CreateSmolAmeToPlayerDir()
{
	FVector SmolAmeDir = APlayer::PlayerPos - GetActorLocation();
	SmolAmeDir = SmolAmeDir.Normalize2DReturn();
	return SmolAmeDir;
}

void ASmolAme::Move(float _DeltaTime, EMonsterMoveType _MoveType)
{
	FVector SmolAmePos = GetActorLocation();

	// ���� ����غô� ��İ� ����ϰ� FSM�� ����غ���.
	switch (_MoveType)
	{
	case EMonsterMoveType::Follow:
		Dir = APlayer::PlayerPos - SmolAmePos;
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

void ASmolAme::CheckPosComparePlayer()
{
	if (APlayer::PlayerPos.Y <= GetActorLocation().Y)
	{
		Renderer->SetOrder(ERenderingOrder::MonsterUp);
	}
	else
	{
		Renderer->SetOrder(ERenderingOrder::MonsterDown);
	}
}

void ASmolAme::MonsterPosDirSet(float _DeltaTime)
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
