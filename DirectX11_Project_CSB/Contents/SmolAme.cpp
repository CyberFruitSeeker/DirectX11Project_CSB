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

	//SmolAmeState.CreateState("Walk");
	//SmolAmeState.CreateState("Jump");
	//SmolAmeState.CreateState("Jumping");
	//SmolAmeState.CreateState("GroundPound");

	//SmolAmeState.SetUpdateFunction("Idle", std::bind(&ASmolAme::SmolAmeWalk, this, std::placeholders::_1));

	//Renderer->CreateAnimation("SmolAme_Walk", "SmolAme", 0.06f, true, 0, 7);
	//Renderer->CreateAnimation("SmolAme_Jump", "SmolAme", 0.06f, true, 8, 16);
	//Renderer->CreateAnimation("SmolAme_Jumping", "SmolAme", 0.06f, true, 17, 26);
	//Renderer->CreateAnimation("SmolAme_GroundPound", "SmolAme", 0.06f, true, 27, 44);



	// ======= 스몰아메 애니메이션 FSM =======

	// 플레이어를 향해서 다가오다가 // 상태1
	// 일정범위 안에 들어오면 점프를 뛰어서 공격한다. 상태2



	//// 각 상태 만들고
	//SmolAmeState.CreateState("Walk");
	//SmolAmeState.CreateState("Jump");
	//SmolAmeState.CreateState("Jumping");
	//SmolAmeState.CreateState("GroundPound");

	//// 걷기 시작할때
	//SmolAmeState.SetStartFunction("Walk", [=]()
	//	{
	//		Renderer->ChangeAnimation("SmolAme_Walk");
	//	});

	//// 점프 시작할때
	//SmolAmeState.SetStartFunction("Jump", [=]()
	//	{
	//		Renderer->ChangeAnimation("SmolAme_Jump");
	//	});

	//// 점프중인 상태 시작
	//SmolAmeState.SetStartFunction("Jumping", [=]()
	//	{
	//		Renderer->ChangeAnimation("SmolAme_Jumping");
	//	});

	//// 그라운드 파운드 상태 시작
	//SmolAmeState.SetStartFunction("GroundPound", [=]()
	//	{
	//		Renderer->ChangeAnimation("SmolAme_GroundPound");
	//	});


	//// 걷기 완료될때
	//SmolAmeState.SetUpdateFunction("Walk", [=](float _DeltaTime)
	//	{
	//		PlayerTargetMove(_DeltaTime);
	//		float4 Range = APlayer::PlayerPos - GetActorLocation();

	//		if (250.0f >= Range.Size2D())
	//		{
	//			StatePtr->ChangeState("Jump");
	//		}
	//	});

	//// 점프가 완료될때
	//SmolAmeState.SetUpdateFunction("Jump", [=](float _DeltaTime)
	//	{
	//		PlayerTargetMove(_DeltaTime);

	//		float4 Range = APlayer::PlayerPos - GetActorLocation();
	//
	//		StatePtr->ChangeState("Jumping");

	//	});

	//// 점프 하고있는 상태 업데이트
	//SmolAmeState.SetUpdateFunction("Jumping", [=](float _DeltaTime)
	//	{
	//		PlayerTargetMove(_DeltaTime);

	//		float4 Range = APlayer::PlayerPos - GetActorLocation();

	//		StatePtr->ChangeState("GroundPound");
	//	});

	//// 그라운드 파운드가 업데이트 될때 :
	//// 점프 업데이트 되고, End해서 다시 걷기로
	//SmolAmeState.SetUpdateFunction("GroundPound", [=](float _DeltaTime)
	//	{
	//		//PlayerTargetMove(_DeltaTime);

	//		float4 Range = APlayer::PlayerPos - GetActorLocation();
	//		//if (100.0f <= Range.Size2D() && Renderer->IsCurAnimationEnd())
	//		//{
	//		//	StatePtr->ChangeState("Walk");
	//		//}
	//		StatePtr->ChangeState("Walk");
	//	});



	// 걷기 만들고
	SmolAmeState.CreateState("Walk");
	// 걷기 시작할때
	SmolAmeState.SetStartFunction("Walk", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Walk");
		});
	// 걷기 완료될때
	SmolAmeState.SetUpdateFunction("Walk", [=](float _DeltaTime)
		{
			PlayerTargetMove(_DeltaTime);
			float4 Range = APlayer::PlayerPos - GetActorLocation();

			if (200.0f >= Range.Size2D())
			{
				StatePtr->ChangeState("Jump");
			}


			//if (250.0f >= Range.Size2D())
			//{
			//	StatePtr->ChangeState("JumpToJumping");
			//}
		});
	//// 점프 만들고
	//SmolAmeState.CreateState("Jump");
	//// 점프 시작할때
	//SmolAmeState.SetStartFunction("Jump", [=]()
	//	{
	//		Renderer->ChangeAnimation("SmolAme_JumpToGroundPound");
	//	});
	//// 점프 업데이트 될때
	//SmolAmeState.SetUpdateFunction("Jump", [=](float _DeltaTime)
	//	{
	//		PlayerTargetMove(_DeltaTime * JumpingAccel);

	//		float4 Range = APlayer::PlayerPos - GetActorLocation();
	//		if (100.0f <= Range.Size2D() && Renderer->IsCurAnimationEnd())
	//		{
	//			StatePtr->ChangeState("Walk");
	//		}
	//	});

	// 점프 만들고
	SmolAmeState.CreateState("Jump");
	// 점프 시작할때
	SmolAmeState.SetStartFunction("Jump", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Jump");
		});
	// 점프 업데이트 될때
	SmolAmeState.SetUpdateFunction("Jump", [=](float _DeltaTime)
		{
			PlayerTargetMove(_DeltaTime);

			float4 Range = APlayer::PlayerPos - GetActorLocation();
			if (Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("Jumping");
			}
		});
	
	// 점핑 만들고
	SmolAmeState.CreateState("Jumping");
	// 점핑 시작할때
	SmolAmeState.SetStartFunction("Jumping", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_Jumping");
		});
	// 점핑 업데이트 될때
	SmolAmeState.SetUpdateFunction("Jumping", [=](float _DeltaTime)
		{
			PlayerTargetMove(_DeltaTime * JumpingAccel);

			float4 Range = APlayer::PlayerPos - GetActorLocation();
			if (Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("GroundPound");
			}
		});



	// 그라운드 파운드 만들고
	SmolAmeState.CreateState("GroundPound");
	// 그라운드 파운드 시작할때
	SmolAmeState.SetStartFunction("GroundPound", [=]()
		{
			Renderer->ChangeAnimation("SmolAme_GroundPound");
		});
	// 그라운드 파운드 업데이트 될때
	SmolAmeState.SetUpdateFunction("GroundPound", [=](float _DeltaTime)
		{
			PlayerTargetMove(_DeltaTime);

			float4 Range = APlayer::PlayerPos - GetActorLocation();
			if (Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("Walk");
			}

			if (100.0f <= Range.Size2D() && Renderer->IsCurAnimationEnd())
			{
				StatePtr->ChangeState("Walk");
			}

		});






	//Renderer->SetAutoSize(1.0f, true);
	//Renderer->SetOrder(ERenderingOrder::MonsterUp);
	//SmolAmeState.ChangeState("Walk");


	//SmolAmeState.SetUpdateFunction("Jumping", [=](float _DeltaTime)
	//	{
	//		PlayerTargetMove(_DeltaTime);

	//		float4 Range = APlayer::PlayerPos - GetActorLocation();
	//		if (100.0f <= Range.Size2D() && Renderer->IsCurAnimationEnd())
	//		{
	//			StatePtr->ChangeState("Walk");
	//		}
	//	});

	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::MonsterUp);
	SmolAmeState.ChangeState("Walk");



	//StateUpdate();
}

void ASmolAme::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	MonsterPosDirSet(_DeltaTime);
	SmolAmeState.Update(_DeltaTime);
}

// 스몰아메가 플레이어한테 다가간다.
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
	Renderer->CreateAnimation("SmolAme_Jumping", "SmolAme", 0.15f, true, 17, 26);
	Renderer->CreateAnimation("SmolAme_GroundPound", "SmolAme", 0.06f, true, 27, 44);
	//Renderer->CreateAnimation("SmolAme_JumpToJumping", "SmolAme", 0.12f, true, 8, 26);
	//Renderer->CreateAnimation("SmolAme_JumpToGroundPound", "SmolAme", 0.12f, true, 8, 44);

}

// 스몰 아메의 패턴(상태변화) :
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
