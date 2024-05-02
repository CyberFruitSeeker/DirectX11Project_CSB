#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloMouse.h"
#include "Monster.h"
#include "SmolAme.h"


// 무한맵을 구현하기 위한 union 함수 구조체(클래스)
struct FIntPoint
{
	union
	{
		struct
		{
			int X;
			int Y;
		};

		__int64 Key;
	};
};


// 설명 :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MouseCursorToTick();
	void PlayingDebugTextUI();
	void MonsterSpawnTick(float _DeltaTime);
	void SmolAmeSpawnTick(float _DeltaTime);



	std::shared_ptr<APlayer> Player;
	std::shared_ptr<AHoloMouse> MouseCursor;
	std::shared_ptr<AMonster> Monster;
	std::shared_ptr<ASmolAme> SmolAme;


	// (스테이지1)무한맵을 구현하기 위한 함수 및 기능들
	std::vector <std::shared_ptr<APlayBackLayer>> Grounds;
	float4 IndexToCenterPos(FIntPoint _Index);
	FIntPoint PosToIndex(float4 _Pos);
	void InfinityGroundCheck();
	void InfinityMapSpawn();


	// ====== 몬스터 랜덤 생성 & 스폰 ======
	void SpawnMonster(std::string _Name, float4 _Location);
	void SpawnMonsterTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term, std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group = false, int _Quantity = 1);
	void RandomSpawnMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity);
	float4 RandomLocation(bool _Group);

	// 아래는 보스 몬스터들
	// 
	// 1. 스몰아메
	void SpawnSmolAme(std::string _Name, float4 _Location);
	void SpawnSmolAmeTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term, std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group = false, int _Quantity = 1);
	void RandomSpawnSmolAme(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity);
	float4 SmolAmeRandomLocation(bool _Group);

	// 2. 후부질라




	

private:
	FIntPoint CurIndex;
	float PlayTime = 0;
	float SpawnTerm = 0;
	float4 GroupMonsterPos;
	bool GroupSpawn = false;

	

};

