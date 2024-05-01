#include "PreCompile.h"
#include "SmolAme.h"
#include "Player.h"

ASmolAme::ASmolAme()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	SetRoot(Root);

	UCollision* SmolAmeCol = CreateDefaultSubObject<UCollision>("Collision");
	SmolAmeCol->SetupAttachment(Root);
	SmolAmeCol->SetScale({ 100.0f,100.0f });
	SmolAmeCol->SetCollisionGroup(ECollisionOrder::Monster);
	SmolAmeCol->SetCollisionType(ECollisionType::Rect);


}

ASmolAme::~ASmolAme()
{
}

void ASmolAme::BeginPlay()
{
	Super::BeginPlay();

	CreateSmolAmeAnimation("SmolAme");

	SmolAmeState.CreateState("Walk");
	SmolAmeState.CreateState("Jump");
	SmolAmeState.CreateState("Jumping");
	SmolAmeState.CreateState("GroundPound");

	//SmolAmeState.SetUpdateFunction("Idle", std::bind(&ASmolAme::SmolAmeWalk, this, std::placeholders::_1));



	//Renderer->CreateAnimation("SmolAme_Walk", "SmolAme", 0.06f, true, 0, 7);
	//Renderer->CreateAnimation("SmolAme_Jump", "SmolAme", 0.06f, true, 8, 16);
	//Renderer->CreateAnimation("SmolAme_Jumping", "SmolAme", 0.06f, true, 17, 26);
	//Renderer->CreateAnimation("SmolAme_GroundPound", "SmolAme", 0.06f, true, 27, 44);




	Renderer->SetAutoSize(1.0f, true);
	Renderer->ChangeAnimation("SmolAme");
	Renderer->SetOrder(ERenderingOrder::MonsterUp);

	//StateUpdate();
}

void ASmolAme::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	



	MonsterPosDirSet(_DeltaTime);

}

void ASmolAme::CreateSmolAmeAnimation(std::string _Name)
{
	Renderer->CreateAnimation("SmolAme", "SmolAme", 0.6f, true, 0, 44);
	Renderer->CreateAnimation("SmolAme_Walk", "SmolAme", 0.06f, true, 0, 7);
	Renderer->CreateAnimation("SmolAme_Jump", "SmolAme", 0.06f, true, 8, 16);
	Renderer->CreateAnimation("SmolAme_Jumping", "SmolAme", 0.06f, true, 17, 26);
	Renderer->CreateAnimation("SmolAme_GroundPound", "SmolAme", 0.06f, true, 27, 44);

}


// 스몰 아메의 패턴(상태변화) :
// Walk => Jump => Jumping(circle shadow) => GroundPound => Walk

void ASmolAme::StateUpdate()
{

	//SmolAmeState.CreateState("Idle");
	//SmolAmeState.CreateState("Jump");
	//SmolAmeState.CreateState("GroundPound");


}

void ASmolAme::SmolAmeWalk(std::string _Name)
{
	//Renderer->CreateAnimation(_Name + "_Idle", _Name, 0.06f, true, 37, 44);
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






void ASmolAme::SmolAmeStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType)
{
	Hp = _Hp;
	Atk = _Atk;
	Speed = _Speed;
	CalSpeed = 200.0f * Speed;
	Exp = _Exp;
	MoveType = _MoveType;
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

	// 전에 사용해봤던 방식과 비슷하게 FSM을 사용해본다.
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
