#pragma once

// 설명 :
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


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SmolAmeWalk(std::string _Name);
	void SmolAmeJumpStart();
	void SmolAmeJump(std::string _Name);
	void SmolAmeJumping(std::string _Name);
	void SmolAmeGroundPound(std::string _Name);
	void SmolAmeWalkStart();

	void CreateSmolAmeAnimation(std::string _Name);

	void Move(float _DeltaTime, EMonsterMoveType _MoveType);




private:
	USpriteRenderer* Renderer;


	// 공식 위키 기준 스몰 아메 스테이터스
	float Hp = 25000.0f;
	float Atk = 20.0f;
	float Speed = 1.2f;
	float EarnExp = 5000.0f;


	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;



};

