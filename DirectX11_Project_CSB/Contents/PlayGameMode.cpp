#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloCureConstValue.h"
#include "HoloMouse.h"
#include "SmolAme.h"
#include <random>
#include <EngineCore/Camera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineBase/EngineRandom.h>


std::shared_ptr<APlayer> APlayGameMode::MainPlayer = nullptr;

APlayGameMode::APlayGameMode()
{
	InputOn();
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 업데이트로 추가된 세이브 기능 쓰고싶으면 여기에다 해볼 것
	//

	//Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	// 인스턴싱 기능 잘 되나?
	// 인스턴싱 기능 쓸려면? : 몬스터들 렌더링 오더 다 다르게 해줘야함
	// 왜?? : 같은 텍스처(머터리얼)인 것만 적용되기 때문에
	//GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderingOrder::MonsterUp);
	//GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderingOrder::MonsterDown);


	// 무한맵을 가동시키기 전에 맵 이미지부터 찾아주고
	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::FindRes("Holo_map_06.png");
	CurIndex = { 0,0 };
	float4 PlayerStartPos = IndexToCenterPos(CurIndex);


	// (PlayLevel 시작할때) 맵에서 카메라 위치 세팅
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -200.0f });
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	float4 CameraPos = PlayerStartPos;
	CameraPos.Z = -150.0f;
	Camera->SetActorLocation(CameraPos);


	// 플레이어 스폰
	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetName("Gura");
	Player->SetActorLocation(PlayerStartPos);
	MainPlayer = Player;
	Player->PlayerState.ChangeState("Idle");

	// 마우스 커서 스폰
	MouseCursor = GetWorld()->SpawnActor<AHoloMouse>("MouseCursor");
	AHoloMouse::MouseCursorOn = false;
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MouseCursor->SetActorLocation(AHoloMouse::MousePos);


	// 무한맵 스폰
	InfinityMapSpawn();



}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 마우스 커서 움직임 Tick
	MouseCursorToTick();

	// (스테이지1)무한맵 Tick
	InfinityGroundCheck();

	// 몬스터 스폰 Tick
	MonsterSpawnTick(_DeltaTime);
	//PlayTime += _DeltaTime;

	// 스몰 아메 스폰 Tick
	SmolAmeSpawnTick(_DeltaTime);

	// 디버깅용 UI
	PlayingDebugTextUI();

	// 디버깅 UI : 프레임 표시
	std::string FPS = std::format("FPS : {}", 1.0f / _DeltaTime);
	UEngineDebugMsgWindow::PushMsg(FPS);




}

// ========== Tick 에서 돌려주는 함수들 ==========
// 몬스터
void APlayGameMode::MonsterSpawnTick(float _DeltaTime)
{
	// 몬스터 스폰 시작 - 끝 - 간격
	// 몬스터 크기, 체력, 공격력, 스피드, 경험치
	// 마지막은 스폰되는 양

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 7.0f, "Deadbeat",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 2);

	SpawnMonsterTimeSet(_DeltaTime, 1.0f, 40.0f, 11.0f, "DeadbeatBat",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 3);

	SpawnMonsterTimeSet(_DeltaTime, 1.5f, 40.0f, 13.0f, "DeadbeatGang",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 2);

	SpawnMonsterTimeSet(_DeltaTime, 2.0f, 40.0f, 15.0f, "DeadbeatShield",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 2);

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 8.0f, "Shrimp",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 3);

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 10.0f, "ShrimpDark",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 2);

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 11.0f, "Bubba",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 3);

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 8.0f, "KFP",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 5);

	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "Takodachi",
		2.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 4);



	//보스 몬스터

	// 실험용 : 파워 오브 아틀란티스

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "POA",
	//	2.2f, 40.0f, 4.0f, 0.6f, 7.0f, EMonsterMoveType::Follow, false, 5);

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "PowerOfAtlantis",
	//	0.4f, 40.0f, 4.0f, 0.6f, 7.0f, EMonsterMoveType::Follow, false, 3);


	// 후부질라
	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "Fubuzilla",
		4.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 3);

	// 스몰아메
	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "SmolAme",
	//	3.3f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 1);

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "fubuLazer",
	//	3.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 50);


	//SpawnMonsterTimeSet(_DeltaTime, 0.0f, 40.0f, 12.0f, "SmolAme",
	//	3.3f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 1);




	PlayTime += _DeltaTime;
}

// 스몰 아메
void APlayGameMode::SmolAmeSpawnTick(float _DeltaTime)
{
	SpawnSmolAmeTimeSet(_DeltaTime, 1.0f, 25.0f, 12.0f, "SmolAme",
		4.0f, 40.0f, 4.0f, 0.1f, 7.0f, EMonsterMoveType::Follow, false, 1);

	PlayTime += _DeltaTime;
}

// 디버깅 창
void APlayGameMode::PlayingDebugTextUI()
{
	float4 PlayerPos = Player->GetActorLocation();
	FIntPoint Index = PosToIndex(PlayerPos);
	CurIndex = Index;
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : {}", PlayerPos.ToString()));
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerIndex : {}, {}", Index.X, Index.Y));

	// 8축 방향을 표시해주는 것도 추가해본다.
	std::string PlayerDir = "";
	switch (Player->GetPlayerDir())
	{
	case EPlayerDir::N:
		PlayerDir = "N";
		break;
	case EPlayerDir::NE:
		PlayerDir = "NE";
		break;
	case EPlayerDir::NW:
		PlayerDir = "NW";
		break;
	case EPlayerDir::E:
		PlayerDir = "E";
		break;
	case EPlayerDir::W:
		PlayerDir = "W";
		break;
	case EPlayerDir::S:
		PlayerDir = "S";
		break;
	case EPlayerDir::SE:
		PlayerDir = "SE";
		break;
	case EPlayerDir::SW:
		PlayerDir = "SW";
		break;
	default:
		break;
	}
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerDir : {}", PlayerDir));



}

// 마우스 커서 움직이게 하기
void APlayGameMode::MouseCursorToTick()
{
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	HoloCureConstValue::PlayLevelMousePos = FVector{ APlayer::PlayerPos.X + AHoloMouse::MousePos.X - 640, APlayer::PlayerPos.Y - AHoloMouse::MousePos.Y + 360 };
	MouseCursor->SetActorLocation(HoloCureConstValue::PlayLevelMousePos);
}


// ========== 무한 맵 기능이 담긴 함수들==========
// 
//
float4 APlayGameMode::IndexToCenterPos(FIntPoint _Index)
{
	float4 Pos;
	Pos.X = HoloCureConstValue::GroundTileSize.X * _Index.X;
	Pos.X = HoloCureConstValue::GroundTileSize.X * _Index.Y;

	Pos.X = HoloCureConstValue::GroundTileSize.hX();
	Pos.X = HoloCureConstValue::GroundTileSize.hY();

	return Pos;
}

FIntPoint APlayGameMode::PosToIndex(float4 _Pos)
{
	FIntPoint Index;

	float4 Location = _Pos;

	float4 Pos;
	Pos.X = Location.X / HoloCureConstValue::GroundTileSize.X;
	Pos.Y = Location.Y / HoloCureConstValue::GroundTileSize.Y;

	if (0 >= Pos.X)
	{
		Pos.X += -1;
	}
	if (0 >= Pos.Y)
	{
		Pos.Y += -1;
	}

	Index.X = Pos.X;
	Index.Y = Pos.Y;
	return Index;
}

void APlayGameMode::InfinityGroundCheck()
{
	float4 PlayerPos = Player->GetActorLocation();

	FIntPoint Index = PosToIndex(PlayerPos);

	if (Index.X != CurIndex.X || Index.Y != CurIndex.Y)
	{
		int GroundCount = 0;

		float4 MovePos;
		MovePos.X = Index.X * HoloCureConstValue::GroundTileSize.X;
		MovePos.Y = Index.Y * HoloCureConstValue::GroundTileSize.Y;

		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				std::shared_ptr<APlayBackLayer> Back = Grounds[GroundCount];

				Back->SetActorScale3D(HoloCureConstValue::GroundTileSize);
				FIntPoint Point;
				Point.X = x;
				Point.Y = y;

				float4 Pos;
				Pos.X = HoloCureConstValue::GroundTileSize.X * x;
				Pos.Y = HoloCureConstValue::GroundTileSize.Y * y;

				Pos.X += HoloCureConstValue::GroundTileSize.hX();
				Pos.Y += HoloCureConstValue::GroundTileSize.hY();
				Back->SetActorLocation(Pos + MovePos);
				++GroundCount;
			}
		}

		CurIndex = Index;
	}
}

void APlayGameMode::InfinityMapSpawn()
{
	// push back을 해서 무한맵을 가동시키는 for문
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			std::shared_ptr<APlayBackLayer> Back = GetWorld()->SpawnActor<APlayBackLayer>("PlayBackLayer");
			Back->SetActorScale3D(HoloCureConstValue::GroundTileSize);

			FIntPoint Point;
			Point.X = x;
			Point.Y = y;

			float4 Pos;
			Pos.X = HoloCureConstValue::GroundTileSize.X * x;
			Pos.Y = HoloCureConstValue::GroundTileSize.X * y;

			Pos.X = HoloCureConstValue::GroundTileSize.hX();
			Pos.Y = HoloCureConstValue::GroundTileSize.hY();
			Back->SetActorLocation(Pos);

			Grounds.push_back(Back);
		}
	}

}


// ============== 몬스터 (랜덤)배치, 스폰 기능들 ==============
void APlayGameMode::SpawnMonster(std::string _Name, float4 _Location)
{
	std::shared_ptr<AMonster> Monster;
	Monster = GetWorld()->SpawnActor<AMonster>(_Name);
	Monster->SetActorLocation(_Location);
}

void APlayGameMode::SpawnMonsterTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term,
	std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp,
	EMonsterMoveType _MoveType, bool _Group, int _Quantity)
{
	if (PlayTime >= _SpawnBegin && PlayTime < _SpawnEnd)
	{
		if (SpawnTerm <= 0)
		{
			RandomSpawnMonster(_Name, _Size, _Hp, _Atk, _Speed, _Exp, _MoveType, _Group, _Quantity);
			SpawnTerm = _Term;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}
}

void APlayGameMode::RandomSpawnMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp,
	EMonsterMoveType _MoveType, bool _Group, int _Quantity)
{
	if (0 >= _Quantity)
	{
		MsgBoxAssert("스폰하려는 몬스터의 수가 0 이하는 좀 이상하잖아..?");
		return;
	}

	FVector GroupToPlayerDir;

	for (int i = 0; i < _Quantity; i++)
	{
		std::shared_ptr<AMonster> Monster;

		Monster = GetWorld()->SpawnActor<AMonster>(_Name);
		Monster->GetRenderer()->SetAutoSize(_Size, true);
		Monster->GetRenderer()->ChangeAnimation(_Name);
		Monster->SetMonsterStatus(_Hp, _Atk, _Speed, _Exp, _MoveType);
		FVector GroupPos = RandomLocation(_Group);
		Monster->SetActorLocation(GroupPos);
		if (true == _Group)
		{
			if (false == GroupSpawn)
			{
				GroupToPlayerDir = Monster->CreateGroupToPlayerDir();
				Monster->SetToPlayerDir(GroupToPlayerDir);
				GroupSpawn = true;
			}
			else
			{
				Monster->SetToPlayerDir(GroupToPlayerDir);
			}
		}
		else
		{
			FVector Dir = APlayer::PlayerPos - Monster->GetActorLocation();
			Dir = Dir.Normalize2DReturn();
			Monster->SetToPlayerDir(Dir);
		}

	}
	GroupSpawn = false;
}

// 플레이어 주변에서 나오게 한다.
float4 APlayGameMode::RandomLocation(bool _Group)
{
	float4 MonsterPos;

	// 뭉쳐서 나오지 않을때
	if (false == _Group)
	{
		MonsterPos = APlayer::PlayerPos;

		while (MonsterPos.X > (APlayer::PlayerPos.X - 300.0f) && MonsterPos.X < (APlayer::PlayerPos.X + 300.0f))
		{
			MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 100.0f;
		}
		while (MonsterPos.Y > (APlayer::PlayerPos.Y - 300.0f) && MonsterPos.Y < (APlayer::PlayerPos.Y + 300.0f))
		{
			MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 100.0f;
		}
	}
	else
	{
		//뭉쳐서 나올때
		if (false == GroupSpawn)
		{
			GroupMonsterPos = APlayer::PlayerPos;

			while (GroupMonsterPos.X > (APlayer::PlayerPos.X - 300.0f) && GroupMonsterPos.X < (APlayer::PlayerPos.X + 300.0f))
			{
				GroupMonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 100.0f;
			}
			while (GroupMonsterPos.Y > (APlayer::PlayerPos.Y - 250.0f) && GroupMonsterPos.Y < (APlayer::PlayerPos.Y + 250.0f))
			{
				GroupMonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 100.0f;
			}
		}

		MonsterPos = GroupMonsterPos;

		MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
		MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;

	}

	//float4 MonsterPos = APlayer::PlayerPos;
	//MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
	//MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;

	return MonsterPos;
}


// ====== 스몰 아메 및 다른 보스, 중보스 몬스터 애니메이션 & 스폰 함수들 ======

//우선 스몰아메
void APlayGameMode::SpawnSmolAme(std::string _Name, float4 _Location)
{
	std::shared_ptr<ASmolAme> SmolAme;
	SmolAme = GetWorld()->SpawnActor<ASmolAme>(_Name);
	SmolAme->SetActorLocation(_Location);
}

void APlayGameMode::SpawnSmolAmeTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term, std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity)
{
	if (PlayTime >= _SpawnBegin && PlayTime < _SpawnEnd)
	{
		if (SpawnTerm <= 0)
		{
			RandomSpawnSmolAme(_Name, _Size, _Hp, _Atk, _Speed, _Exp, _MoveType, _Group, _Quantity);
			SpawnTerm = _Term;
		}
		else
		{
			SpawnTerm -= _DeltaTime;
		}
	}
}

void APlayGameMode::RandomSpawnSmolAme(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity)
{
	//if (0 >= _Quantity)
	//{
	//	MsgBoxAssert("스폰하려는 몬스터의 수가 0 이하는 좀 이상하잖아..?");
	//	return;
	//}

	FVector GroupToPlayerDir;

	for (int i = 0; i < _Quantity; i++)
	{
		std::shared_ptr<ASmolAme> SmolAme;

		SmolAme = GetWorld()->SpawnActor<ASmolAme>(_Name);
		SmolAme->GetRenderer()->SetAutoSize(_Size, true);
		// 스몰아메 애니메이션은? :
		// 클래스 안에서 자체적으로 스테이트 매니저와 람다함수로 돌아간다.
		//SmolAme->GetRenderer()->ChangeAnimation(_Name);
		SmolAme->SmolAmeStatus(_Hp, _Atk, _Speed, _Exp, _MoveType);
		FVector GroupPos = RandomLocation(_Group);
		SmolAme->SetActorLocation(GroupPos);
		if (true == _Group)
		{
			if (false == GroupSpawn)
			{
				GroupToPlayerDir = SmolAme->CreateSmolAmeToPlayerDir();
				SmolAme->SetToPlayerDir(GroupToPlayerDir);
				GroupSpawn = true;
			}
			else
			{
				SmolAme->SetToPlayerDir(GroupToPlayerDir);
			}
		}
		else
		{
			FVector Dir = APlayer::PlayerPos - SmolAme->GetActorLocation();
			Dir = Dir.Normalize2DReturn();
			SmolAme->SetToPlayerDir(Dir);
		}

	}
	GroupSpawn = false;

}

//float4 APlayGameMode::SmolAmeRandomLocation(bool _Group)
//{
//	float4 MonsterPos = APlayer::PlayerPos;
//	MonsterPos.X += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
//	MonsterPos.Y += UEngineRandom::MainRandom.RandomFloat(-5.0f, 5.0f) * 200.0f;
//
//	return MonsterPos;
//}







