#pragma once
//#include <EngineCore/Actor.h>

// 설명 :
class USpriteRenderer;
class AMonster : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	void SetMonsterStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType);

	FVector CreateGroupToPlayerDir();

	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}

	void SetToPlayerDir(FVector _GoToPlayerDir)
	{
		GoToPlayerDir = _GoToPlayerDir;
	}




protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPosComparePlayer();
	void Move(float _DeltaTime, EMonsterMoveType _MoveType);
	void CreateMonsterAnimation(std::string _Name);

	void MonsterPosDirSet(float _DeltaTime);

	// 보스 몬스터 : 스몰 아메
	void SmolAmeWalk(std::string _Name);
	void SmolAmeJump(std::string _Name);
	void SmolAmeGroundPound(std::string _Name);
	




private:
	USpriteRenderer* Renderer;
	UCollision* Collision;

	std::string Name = "Deadbeat";

	float Hp = 100.0f;
	float Atk = 10.0f;
	float Speed = 0.5f;
	float CalSpeed = 200.0f;
	float MoveSpeed = 100.0f;
	float Exp = 5.0f;



	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;



};

