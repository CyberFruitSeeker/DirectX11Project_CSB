#pragma once

// ���� :
class USpriteRenderer;
class ASmolAme : public AActor
{
public:
	
	GENERATED_BODY(AActor);
	
	//friend class APlayer;

	// constrcuter destructer
	ASmolAme();
	~ASmolAme();

	// delete Function
	ASmolAme(const ASmolAme& _Other) = delete;
	ASmolAme(ASmolAme&& _Other) noexcept = delete;
	ASmolAme& operator=(const ASmolAme& _Other) = delete;
	ASmolAme& operator=(ASmolAme&& _Other) noexcept = delete;


	UStateManager SmolAmeState;

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

	void PlayerTargetMove(float _Delta);

	// ���� �Ƹ� ü�� ������, �׾����� ��Ʈ ������ �ϱ�
	//float GetHp()
	//{
	//	return Hp;
	//}

	//void SetHp(float _Hp)
	//{
	//	Hp = _Hp;
	//}

	USpriteRenderer* GetSaveRenderer()
	{
		return SavedRenderer;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	//void StateUpdate();

	//void SmolAmeWalk(std::string _Name);
	//void SmolAmeJumpStart();
	//void SmolAmeJump(std::string _Name);
	//void SmolAmeJumping(std::string _Name);
	//void SmolAmeGroundPound(std::string _Name);
	//void SmolAmeWalkStart();

	float WalkTime = 0.0f;
	float JumpingAccel = 0.0f;
	float JumpingTime = 0.0f;
	float SittingTime = 0.0f;


	void Move(float _DeltaTime, EMonsterMoveType _MoveType);
	void CheckPosComparePlayer();
	void CreateSmolAmeAnimation(std::string _Name);

	void MonsterPosDirSet(float _DeltaTime);

	// Jumping ���¿����� �÷��̾�� �ݸ����� �߻��ϸ� �ȵǴϱ�
	void JumpingCollisionCheck();
	bool JumpingCollision = true;

	void CheckSaved();
	void Saved(float _DeltaTime);
	void SavedHeartTick(float _DeltaTime);

	void CheckHit();


private:
	USpriteRenderer* Renderer;
	UCollision* SmolAmeCollision;
	USpriteRenderer* SavedRenderer;
	UCollision* Collision;

	// ���� ��Ű ���� ���� �Ƹ� �������ͽ�
	float Hp = 25000.0f;
	float Atk = 20.0f;
	float Exp = 5000.0f;

	float Speed = 0.5f;
	float CalSpeed = 200.0f;
	float MoveSpeed = 100.0f;

	std::string Name = "SmolAme";


	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	// ���� �Ƹ� �׾����� ��Ʈ ������ �ϱ� : Saved
	bool IsSaved = false;
	EEngineDir SavedDir = EEngineDir::MAX;
	float RendererAlpha = 1.0f;


	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;


	



};

