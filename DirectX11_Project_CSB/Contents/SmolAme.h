#pragma once

// 설명 :
class USpriteRenderer;
class ASmolAme : public AActor
{
public:
	
	GENERATED_BODY(AActor);
	
	// constrcuter destructer
	ASmolAme();
	~ASmolAme();

	// delete Function
	ASmolAme(const ASmolAme& _Other) = delete;
	ASmolAme(ASmolAme&& _Other) noexcept = delete;
	ASmolAme& operator=(const ASmolAme& _Other) = delete;
	ASmolAme& operator=(ASmolAme&& _Other) noexcept = delete;


	UStateManager* SmolAmeState;

	void SmolAmeStatus(float _Hp, float _Atk, float _Speed, float _Exp, EMonsterMoveType _MoveType);

	FVector CreateSmolAmeToPlayerDir();

	void SetName(std::string _Name)
	{
		Name = _Name;
	}

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

	void StateUpdate();

	void SmolAmeWalk(std::string _Name);
	void SmolAmeJumpStart();
	void SmolAmeJump(std::string _Name);
	void SmolAmeJumping(std::string _Name);
	void SmolAmeGroundPound(std::string _Name);
	void SmolAmeWalkStart();

	void CreateSmolAmeAnimation(std::string _Name);

	void Move(float _DeltaTime, EMonsterMoveType _MoveType);

	void CheckPosComparePlayer();

	void MonsterPosDirSet(float _DeltaTime);



private:
	USpriteRenderer* Renderer;
	UCollision* Collision;


	// 공식 위키 기준 스몰 아메 스테이터스
	float Hp = 25000.0f;
	float Atk = 20.0f;
	//float Speed = 1.2f;
	float Exp = 5000.0f;

	float CalSpeed = 200.0f;
	float MoveSpeed = 100.0f;

	std::string Name = "SmolAme";


	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;



};

