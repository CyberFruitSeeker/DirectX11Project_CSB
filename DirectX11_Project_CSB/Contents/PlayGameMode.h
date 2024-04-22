#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloMouse.h"
#include "Monster.h"


// ���Ѹ��� �����ϱ� ���� union �Լ� ����ü(Ŭ����)
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


// ���� :
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



	// (��������1)���Ѹ��� �����ϱ� ���� �Լ� �� ��ɵ�
	std::vector <std::shared_ptr<APlayBackLayer>> Grounds;
	float4 IndexToCenterPos(FIntPoint _Index);
	FIntPoint PosToIndex(float4 _Pos);
	void InfinityGroundCheck();
	void InfinityMapSpawn();


	// ���� ���� ���� & ����
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

