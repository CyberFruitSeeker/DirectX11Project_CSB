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

	// ���� ���Ϳ� �ݸ���
	// 1. �����Ƹ�
	UCollision* SmolAmeCol = CreateDefaultSubObject<UCollision>("Collision");
	SmolAmeCol->SetupAttachment(Root);
	SmolAmeCol->SetScale({ 100.0f,100.0f });
	SmolAmeCol->SetCollisionGroup(ECollisionOrder::Monster);
	SmolAmeCol->SetCollisionType(ECollisionType::Rect);

	// 2. �ĺ�����
	UCollision* FubuzillaCol = CreateDefaultSubObject<UCollision>("Collision");
	FubuzillaCol->SetupAttachment(Root);
	FubuzillaCol->SetScale({ 100.0f,100.0f });
	FubuzillaCol->SetCollisionGroup(ECollisionOrder::Monster);
	FubuzillaCol->SetCollisionType(ECollisionType::Rect);


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

	


	// ���� ����

	// �����Ƹ�
	//SmolAmeAllAnimations("SmollAme");
	//SmolAmeWalk("SmollAme");
	//SmolAmeJump("SmollAme");
	SmolAmeJump_GroundPound("SmollAme");
	//SmolAmeGroundPound("SmollAme");
	

	// �ĺ�����
	FubuzillaAnimation("fubuzilla");
	//FubuzillaLaser("fubuLazer");



	




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
	Renderer->CreateAnimation(_Name, _Name, 0.25f, true, 0, 2);
}


// ���� ���� �ִϸ��̼�
// 
// 1. ���� �Ƹ�
// 
// �̹��� �ε���?
// ��ũ : 0~7
// ���� : 8~26
// �׶��� �Ŀ�� : 27~44

void AMonster::SmolAmeAllAnimations(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.06f, true, 0,44);
}

void AMonster::SmolAmeWalk(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.06f, true, 0, 7);
}

void AMonster::SmolAmeJump(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.06f, true, 8, 26);
}

void AMonster::SmolAmeJump_GroundPound(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.06f, true, 8, 44);
}

void AMonster::SmolAmeGroundPound(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.06f, true, 27, 44);
}


// 2. �ĺ�����
void AMonster::FubuzillaAnimation(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.12f, true, 0, 11);
}

//void AMonster::FubuzillaLaser(std::string _Name)
//{
//	Renderer->CreateAnimation(_Name, _Name, 0.12f, true, 0, 32);
//}




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
	// ���͵��� �÷��̾��� �Ÿ� ���̰� �پ��鼭 ���� �ٰ�����.
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

	// ���� ����غô� ��İ� ����ϰ� FSM�� ����غ���.
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


