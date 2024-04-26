#pragma once

// Ό³Έν :
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


	int Hp = 25000;
	int Atk = 20;
	float Speed = 1.2f;
	float Exp = 5000.0f;


	EMonsterMoveType MoveType = EMonsterMoveType::Follow;

	FVector PlayerLocation;
	FVector GoToPlayerDir;

	FVector Dir = FVector::Zero;



};

