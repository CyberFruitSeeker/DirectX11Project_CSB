#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"


AMonster::AMonster()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);


	Shadow = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Shadow->SetupAttachment(Root);
	Shadow->SetPivot(EPivot::BOT);

	SavedRenderer = CreateDefaultSubObject<USpriteRenderer>("SavedRenderer");
	SavedRenderer->SetupAttachment(Root);
	SavedRenderer->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	SavedRenderer->SetActive(false);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetScale({ 30.0f,30.0f });
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);





	// 2. �ĺ�����
	//UCollision* FubuzillaCol = CreateDefaultSubObject<UCollision>("Collision");
	//FubuzillaCol->SetupAttachment(Root);
	//FubuzillaCol->SetScale({ 100.0f,100.0f });
	//FubuzillaCol->SetCollisionGroup(ECollisionOrder::Monster);
	//FubuzillaCol->SetCollisionType(ECollisionType::Rect);


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

	// �ĺ�����
	//FubuzillaAnimation("fubuzilla");
	//FubuzillaLaser("fubuLazer");
	CreateMonsterAnimation("Fubuzilla", 11);

	// ������ ����� : �Ŀ� ���� ��Ʋ��Ƽ��(2����)
	PowerOfAtlantis("PowerOfAtlantis");
	//CreateMonsterAnimation("PowerOfAtlantis", 8);
	CreatePOA("POA");

	// ���͵� ������
	Renderer->SetAutoSize(1.0f, true);
	Renderer->ChangeAnimation(Name);
	Renderer->SetOrder(ERenderingOrder::MonsterUp);

	// ������ ������
	//Shadow->SetSprite()
	Shadow->SetSprite("Shadow_0.png");
	Shadow->SetAutoSize(HoloCureConstValue::MultipleSize, true);
	Shadow->SetOrder(ERenderingOrder::Shadow);
	Shadow->SetMulColor({ 1.f,1.f,1.f,0.7f });

	// ���� ������ �߻��ϴ� (��Ʈ)����Ʈ ������
	SavedRenderer->CreateAnimation("MonsterKillHeart", "MonsterKillHeart", 0.1f, false);
	SavedRenderer->SetOrder(ERenderingOrder::MonsterUIUp);
	SavedRenderer->ChangeAnimation("MonsterKillHeart");

}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//MonsterPosDirSet(_DeltaTime);
	
	//SavedHeartTick(_DeltaTime);
	
	if (false == IsSaved)
	{
		Move(_DeltaTime, MoveType);

		if (0 > Dir.X)
		{
			Renderer->SetDir(EEngineDir::Left);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		CheckSaved();
		CheckHit();
	}
	else
	{
		Saved(_DeltaTime);
	}


	CheckPosComparePlayer();

}

void AMonster::CreateMonsterAnimation(std::string _Name, int _MaxIndex)
{
	Renderer->CreateAnimation(_Name, _Name, 0.1f, true, 0, _MaxIndex);
}


// 2. �ĺ�����
//void AMonster::FubuzillaAnimation(std::string _Name)
//{
//	Renderer->CreateAnimation(_Name, _Name, 0.12f, true, 0, 11);
//}

//void AMonster::FubuzillaLaser(std::string _Name)
//{
//	Renderer->CreateAnimation(_Name, _Name, 0.12f, true, 0, 32);
//}

void AMonster::CreatePOA(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.025f, true, 0, 4);
}


void AMonster::PowerOfAtlantis(std::string _Name)
{
	Renderer->CreateAnimation(_Name, _Name, 0.025f, true, 0, 8);
}


// ���͵��� �÷��̾ ���� �ٰ����� ����� �Լ�
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
	CalSpeed = HoloCureConstValue::BaseSpeed * Speed;
	Exp = _Exp;
	MoveType = _MoveType;
}

// ���͵�� �÷��̾��� �Ÿ� ���̰� ���� �پ��鼭 �ٰ�����.
FVector AMonster::CreateGroupToPlayerDir()
{
	FVector MonsterGroupDir = APlayer::PlayerPos - GetActorLocation();
	MonsterGroupDir = MonsterGroupDir.Normalize2DReturn();
	return MonsterGroupDir;
}

void AMonster::CheckPosComparePlayer()
{
	if (APlayer::PlayerPos.Y<=GetActorLocation().Y)
	{
		Renderer->SetOrder(ERenderingOrder::MonsterUp);
		SavedRenderer->SetOrder(ERenderingOrder::MonsterUIUp);
	}
	else
	{
		Renderer->SetOrder(ERenderingOrder::MonsterDown);
		SavedRenderer->SetOrder(ERenderingOrder::MonsterUIDown);
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


// �÷��̾ ���� ���ݰ� (�ݸ���) ��ȣ�ۿ�
void AMonster::CheckHit()
{
	Collision->CollisionEnter(ECollisionOrder::Weapon, [=](std::shared_ptr<UCollision> _Collison)
		{

		}
	);
}

void AMonster::CheckSaved()
{
	if (0 >= Hp)
	{
		IsSaved = true;
		SavedDir = Renderer->GetDir();
	}

}

// ���͸� ���̸� ������ ��Ʈ ����Ʈ
void AMonster::Saved(float _DeltaTime)
{
	SavedRenderer->SetActive(true);

	if (EEngineDir::Left == SavedDir)
	{
		Renderer->AddPosition(FVector{ 1.0f, 0.0f } *_DeltaTime * 20.0f * HoloCureConstValue::MultipleSize);
	}
	else if (EEngineDir::Right == SavedDir)
	{
		Renderer->AddPosition(FVector{ -1.0f, 0.0f } *_DeltaTime * 20.0f * HoloCureConstValue::MultipleSize);
	}
	else
	{
		MsgBoxAssert("������ SavedDir���� �߸��ƽ��ϴ�.");
		return;
	}

	RendererAlpha -= _DeltaTime;
	Renderer->SetMulColor(float4{ 1.0f, 1.0f, 1.0f, RendererAlpha });

	if (true == SavedRenderer->IsCurAnimationEnd())
	{
		Destroy();
		++HoloCureConstValue::KillCount;
	}

}

void AMonster::SavedHeartTick(float _DeltaTime)
{
	//if (false == IsSaved)
	//{
	//	Move(_DeltaTime, MoveType);

	//	if (0>Dir.X)
	//	{
	//		Renderer->SetDir(EEngineDir::Left);
	//	}
	//	else
	//	{
	//		Renderer->SetDir(EEngineDir::Right);
	//	}
	//	CheckSaved();
	//	CheckHit();
	//}
	//else
	//{
	//	Saved(_DeltaTime);
	//}
	
	//CheckPosComparePlayer();

}

