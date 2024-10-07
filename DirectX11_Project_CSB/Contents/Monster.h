#pragma once
//#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// ���� :
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


	void SetToPlayerDir(FVector _GoToPlayerDir)
	{
		GoToPlayerDir = _GoToPlayerDir;
	}

	float GetHp()
	{
		return Hp;
	}

	void SetHp(float _Hp)
	{
		Hp = _Hp;
	}

	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}

	USpriteRenderer* GetSaveRenderer()
	{
		return SavedRenderer;
	}


	UCollision* GetCollision()
	{
		return Collision;
	}







	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckPosComparePlayer();
	void Move(float _DeltaTime, EMonsterMoveType _MoveType);
	void CreateMonsterAnimation(std::string _Name, int _MaxIndex = 2);

	void CreatePOA(std::string _Name);


	void MonsterPosDirSet(float _DeltaTime);

	// ���� ���� �ִϸ��̼�
	// 1. ���� �Ƹ�
	// ������? �� ���� Ŭ�������� ���������� �ʴ´�.
	//void SmolAmeAllAnimations(std::string _Name);
	//void SmolAmeWalk(std::string _Name);
	//void SmolAmeJump(std::string _Name);
	//void SmolAmeGroundPound(std::string _Name);

	// �׳� ����� power of atlantis
	void PowerOfAtlantis(std::string _Name);


	// 2. �ĺ�����
	void FubuzillaAnimation(std::string _Name);
	//void FubuzillaLaser(std::string _Name);

	void CheckHit();

	void CheckSaved();
	void Saved(float _DeltaTime);

	void SavedHeartTick(float _DeltaTime);



private:
	UCollision* Collision;

	USpriteRenderer* Renderer;
	USpriteRenderer* SavedRenderer;
	USpriteRenderer* Shadow;

	std::string Name = "Deadbeat";

	float Hp = 100.0f;
	float Atk = 10.0f;
	float Speed = 0.35f;
	float CalSpeed = ContentsValue::BaseSpeed * Speed;
	float Exp = 5.0f;
	
	float MoveSpeed = 100.0f;

	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	bool IsSaved = false;
	EEngineDir SavedDir = EEngineDir::MAX;
	float RendererAlpha = 1.0f;


	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;



};

