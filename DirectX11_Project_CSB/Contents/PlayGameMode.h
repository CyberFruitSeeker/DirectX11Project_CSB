#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloMouse.h"
#include "Monster.h"


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
	

	std::shared_ptr<APlayer> Player;
	std::shared_ptr<AHoloMouse> MouseCursor;
	std::shared_ptr<AMonster> Monster;



	// (스테이지1)무한맵을 구현하기 위한 함수 및 기능들
	std::vector <std::shared_ptr<APlayBackLayer>> Grounds;
	float4 IndexToCenterPos(FIntPoint _Index);
	FIntPoint PosToIndex(float4 _Pos);
	void InfinityGroundCheck();
	void InfinityMapSpawn();


	// 몬스터 랜덤 생성 & 스폰
	void SpawnMonster(std::string _Name, float4 _Location);
	void SpawnMonsterTimeSet(float _DeltaTime, float _SpawnBegin, float _SpawnEnd, float _Term, std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group = false, int _Quantity = 1);
	void RandomSpawnMonster(std::string _Name, float _Size, float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType, bool _Group, int _Quantity);
	void MonsterSpawnTick(float _DeltaTime);
	float4 RandomLocation(bool _Group);


	
	void PlayingDebugTextUI();

private:
	FIntPoint CurIndex;
	float PlayTime = 0;
	float SpawnTerm = 0;
	float4 GroupMonsterPos;
	bool GroupSpawn = false;

	

};

