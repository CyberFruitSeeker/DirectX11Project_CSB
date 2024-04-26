#pragma once

// 설명 :
class USpriteRenderer;
class ABossMonster : public AActor
{

	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABossMonster();
	~ABossMonster();

	// delete Function
	ABossMonster(const ABossMonster& _Other) = delete;
	ABossMonster(ABossMonster&& _Other) noexcept = delete;
	ABossMonster& operator=(const ABossMonster& _Other) = delete;
	ABossMonster& operator=(ABossMonster&& _Other) noexcept = delete;

	//UStateManager SmolAmeState;








protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	// 스몰아메
	//void SmolAmeWalk(std::string _Name);
	//void SmolAmeJumpStart();
	//void SmolAmeJump(std::string _Name);
	//void SmolAmeJumping(std::string _Name);
	//void SmolAmeGroundPound(std::string _Name);
	//void SmolAmeWalkStart();

	//void CreateSmolAmeAnimation(std::string _Name);





private:

	// 후부질라 스테이터스



	// 스몰 아메 스테이터스



	// 미코다니에 스테이터스





};

