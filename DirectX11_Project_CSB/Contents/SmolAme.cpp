#include "PreCompile.h"
#include "SmolAme.h"
#include "Player.h"
#include <EngineCore/StateManager.h>

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

	UStateManager* StatePtr = &SmolAmeState;

	// �ȱ� �����
	SmolAmeState.CreateState("Walk");
	// �ȱ� �����Ҷ�
	SmolAmeState.SetStartFunction("Walk", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Walk");
			WalkTime = 0.0f;
			// Ÿ���� ��ŸƮ���� �ʱ�ȭ ���ִ� ������ġ
		});
	// �ȱ� �Ϸ�ɶ�
	SmolAmeState.SetUpdateFunction("Walk", [=](float _DeltaTime)
		{
			WalkTime += _DeltaTime;
			PlayerTargetMove(_DeltaTime);
			MonsterPosDirSet(_DeltaTime);
			float4 Range = APlayer::PlayerPos - GetActorLocation();

			if (/*200.0f >= Range.Size2D()*/4.0f < WalkTime)
			{
				StatePtr->ChangeState("Jump");
			}
		});
	

	// ���� �����
	SmolAmeState.CreateState("Jump");
	// ���� �����Ҷ�
	SmolAmeState.SetStartFunction("Jump", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Jump");
		});
	// ���� ������Ʈ �ɶ�
	SmolAmeState.SetUpdateFunction("Jump", [=](float _DeltaTime)
		{
			PlayerTargetMove(_DeltaTime);
			MonsterPosDirSet(_DeltaTime);
			float4 Range = APlayer::PlayerPos - GetActorLocation();
			if (Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("Jumping");
			}
		});
	
	// ���� �����
	SmolAmeState.CreateState("Jumping");
	// ���� �����Ҷ�
	SmolAmeState.SetStartFunction("Jumping", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Jumping");
			JumpingTime = 0.0f;
		});
	// ���� ������Ʈ �ɶ�
	SmolAmeState.SetUpdateFunction("Jumping", [=](float _DeltaTime)
		{
			JumpingTime += _DeltaTime;
			//JumpingAccel += 0.0264f;
			JumpingAccel += 0.025f;
			PlayerTargetMove(_DeltaTime * JumpingAccel < 0.01f);
			MonsterPosDirSet(_DeltaTime);
			float4 Range = APlayer::PlayerPos - GetActorLocation();
			if (3.0f < JumpingTime)
			{
				JumpingAccel = 0.0f;
				StatePtr->ChangeState("GroundPound");
				int a = 0;
			}
		});

	// �׶��� �Ŀ�� �����
	SmolAmeState.CreateState("GroundPound");
	// �׶��� �Ŀ�� �����Ҷ�
	SmolAmeState.SetStartFunction("GroundPound", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_GroundPound");
			SittingTime = 0.0f;
		});
	// �׶��� �Ŀ�� ������Ʈ �ɶ�
	SmolAmeState.SetUpdateFunction("GroundPound", [=](float _DeltaTime)
		{

			if (Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("Walk");
			}

		});


	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterUp);
	SmolAmeState.ChangeState("Walk");

}

void ASmolAme::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SmolAmeState.Update(_DeltaTime);
}

// �����Ƹް� �÷��̾����� �ٰ�����.
void ASmolAme::PlayerTargetMove(float _Delta)
{
	Dir = APlayer::PlayerPos - GetActorLocation();
	Dir = Dir.Normalize2DReturn();
	AddActorLocation(Dir * _Delta * CalSpeed);
}

void ASmolAme::CreateSmolAmeAnimation(std::string _Name)
{
	//Renderer->CreateAnimation("SmolAme_AllAnimation", "SmolAme", 0.06f, true, 0, 44);
	Renderer->CreateAnimation("SmolAme_Walk", "SmolAme", 0.06f, true, 0, 7);
	Renderer->CreateAnimation("SmolAme_Jump", "SmolAme", 0.06f, true, 8, 16);
	Renderer->CreateAnimation("SmolAme_Jumping", "SmolAme", 0.12f, true, 17, 26);
	Renderer->CreateAnimation("SmolAme_GroundPound", "SmolAme", 0.06f, true, 27, 44);
	//Renderer->CreateAnimation("SmolAme_JumpToJumping", "SmolAme", 0.12f, true, 8, 26);
	//Renderer->CreateAnimation("SmolAme_JumpToGroundPound", "SmolAme", 0.12f, true, 8, 44);

}

// ���� �Ƹ��� ����(���º�ȭ) :
// Walk => Jump => Jumping(circle shadow) => GroundPound => Walk

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
