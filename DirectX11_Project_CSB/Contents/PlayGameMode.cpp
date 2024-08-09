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

	// ������Ʈ�� �߰��� ���̺� ��� ��������� ���⿡�� �غ� ��
	//

	//Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	// �ν��Ͻ� ��� �� �ǳ�?
	// �ν��Ͻ� ��� ������? : ���͵� ������ ���� �� �ٸ��� �������
	// ��?? : ���� �ؽ�ó(���͸���)�� �͸� ����Ǳ� ������
	//GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderingOrder::MonsterUp);
	//GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderingOrder::MonsterDown);


	// ���Ѹ��� ������Ű�� ���� �� �̹������� ã���ְ�
	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::FindRes("Holo_map_06.png");
	CurIndex = { 0,0 };
	float4 PlayerStartPos = IndexToCenterPos(CurIndex);


	// (PlayLevel �����Ҷ�) �ʿ��� ī�޶� ��ġ ����
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -200.0f });
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	float4 CameraPos = PlayerStartPos;
	CameraPos.Z = -150.0f;
	Camera->SetActorLocation(CameraPos);


	// �÷��̾� ����
	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetName("Gura");
	Player->SetActorLocation(PlayerStartPos);
	MainPlayer = Player;
	Player->PlayerState.ChangeState("Idle");

	// ���콺 Ŀ�� ����
	MouseCursor = GetWorld()->SpawnActor<AHoloMouse>("MouseCursor");
	AHoloMouse::MouseCursorOn = false;
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MouseCursor->SetActorLocation(AHoloMouse::MousePos);


	// ���Ѹ� ����
	InfinityMapSpawn();



}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// ���콺 Ŀ�� ������ Tick
	MouseCursorToTick();

	// (��������1)���Ѹ� Tick
	InfinityGroundCheck();

	// ���� ���� Tick
	MonsterSpawnTick(_DeltaTime);
	//PlayTime += _DeltaTime;

	// ���� �Ƹ� ���� Tick
	SmolAmeSpawnTick(_DeltaTime);

	// ������ UI
	PlayingDebugTextUI();

	// ����� UI : ������ ǥ��
	std::string FPS = std::format("FPS : {}", 1.0f / _DeltaTime);
	UEngineDebugMsgWindow::PushMsg(FPS);




}

// ========== Tick ���� �����ִ� �Լ��� ==========
// ����
void APlayGameMode::MonsterSpawnTick(float _DeltaTime)
{
	// ���� ���� ���� - �� - ����
	// ���� ũ��, ü��, ���ݷ�, ���ǵ�, ����ġ
	// �������� �����Ǵ� ��

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



	//���� ����

	// ����� : �Ŀ� ���� ��Ʋ��Ƽ��

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "POA",
	//	2.2f, 40.0f, 4.0f, 0.6f, 7.0f, EMonsterMoveType::Follow, false, 5);

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "PowerOfAtlantis",
	//	0.4f, 40.0f, 4.0f, 0.6f, 7.0f, EMonsterMoveType::Follow, false, 3);


	// �ĺ�����
	SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "Fubuzilla",
		4.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 3);

	// �����Ƹ�
	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "SmolAme",
	//	3.3f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 1);

	//SpawnMonsterTimeSet(_DeltaTime, 0.5f, 40.0f, 12.0f, "fubuLazer",
	//	3.0f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 50);


	//SpawnMonsterTimeSet(_DeltaTime, 0.0f, 40.0f, 12.0f, "SmolAme",
	//	3.3f, 40.0f, 4.0f, 0.4f, 7.0f, EMonsterMoveType::Follow, false, 1);




	PlayTime += _DeltaTime;
}

// ���� �Ƹ�
void APlayGameMode::SmolAmeSpawnTick(float _DeltaTime)
{
	SpawnSmolAmeTimeSet(_DeltaTime, 1.0f, 25.0f, 12.0f, "SmolAme",
		4.0f, 40.0f, 4.0f, 0.1f, 7.0f, EMonsterMoveType::Follow, false, 1);

	PlayTime += _DeltaTime;
}

// ����� â
void APlayGameMode::PlayingDebugTextUI()
{
	float4 PlayerPos = Player->GetActorLocation();
	FIntPoint Index = PosToIndex(PlayerPos);
	CurIndex = Index;
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : {}", PlayerPos.ToString()));
	UEngineDebugMsgWindow::PushMsg(std::format("PlayerIndex : {}, {}", Index.X, Index.Y));

	// 8�� ������ ǥ�����ִ� �͵� �߰��غ���.
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

// ���콺 Ŀ�� �����̰� �ϱ�
void APlayGameMode::MouseCursorToTick()
{
	AHoloMouse::MousePos = GEngine->EngineWindow.GetScreenMousePos();
	HoloCureConstValue::PlayLevelMousePos = FVector{ APlayer::PlayerPos.X + AHoloMouse::MousePos.X - 640, APlayer::PlayerPos.Y - AHoloMouse::MousePos.Y + 360 };
	MouseCursor->SetActorLocation(HoloCureConstValue::PlayLevelMousePos);
}


// ========== ���� �� ����� ��� �Լ���==========
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
	// push back�� �ؼ� ���Ѹ��� ������Ű�� for��
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


// ============== ���� (����)��ġ, ���� ��ɵ� ==============
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
		MsgBoxAssert("�����Ϸ��� ������ ���� 0 ���ϴ� �� �̻����ݾ�..?");
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

// �÷��̾� �ֺ����� ������ �Ѵ�.
float4 APlayGameMode::RandomLocation(bool _Group)
{
	float4 MonsterPos;

	// ���ļ� ������ ������
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
		//���ļ� ���ö�
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


// ====== ���� �Ƹ� �� �ٸ� ����, �ߺ��� ���� �ִϸ��̼� & ���� �Լ��� ======

//�켱 �����Ƹ�
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
	//	MsgBoxAssert("�����Ϸ��� ������ ���� 0 ���ϴ� �� �̻����ݾ�..?");
	//	return;
	//}

	FVector GroupToPlayerDir;

	for (int i = 0; i < _Quantity; i++)
	{
		std::shared_ptr<ASmolAme> SmolAme;

		SmolAme = GetWorld()->SpawnActor<ASmolAme>(_Name);
		SmolAme->GetRenderer()->SetAutoSize(_Size, true);
		// �����Ƹ� �ִϸ��̼���? :
		// Ŭ���� �ȿ��� ��ü������ ������Ʈ �Ŵ����� �����Լ��� ���ư���.
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







