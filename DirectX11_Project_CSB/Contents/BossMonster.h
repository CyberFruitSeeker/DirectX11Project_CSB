#pragma once

// ���� :
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


	// �����Ƹ�
	//void SmolAmeWalk(std::string _Name);
	//void SmolAmeJumpStart();
	//void SmolAmeJump(std::string _Name);
	//void SmolAmeJumping(std::string _Name);
	//void SmolAmeGroundPound(std::string _Name);
	//void SmolAmeWalkStart();

	//void CreateSmolAmeAnimation(std::string _Name);





private:

	// �ĺ����� �������ͽ�



	// ���� �Ƹ� �������ͽ�



	// ���ڴٴϿ� �������ͽ�





};

