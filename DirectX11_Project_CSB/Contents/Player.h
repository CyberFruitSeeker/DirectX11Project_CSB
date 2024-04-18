#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "HoloCureEnum.h"


class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	static FVector PlayerPosZero;

	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager PlayerState;

	// ��� ĳ���͸� �����ϴ� ���� ���� ���ڿ�
	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	// ĳ���Ͱ� ��� �������� �ٶ󺸰�, �����ִ°�?
	EPlayerDir GetPlayerDir()
	{
		return PlayerDir;
	}

	float GetAngle()
	{
		return PlayerAngle;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate();

	//void PlayerMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void IdleStart();
	void Run(float _DeltaTime);
	void RunStart();
	void Die(float _DeltaTime);
	
	void CreatePlayerAnimation(std::string _Name);

	// �÷��̾��� ���⿡ ���� ���� �����̴� Arrow
	void CheckArrowModeChange();
	void ChangeArrowDirMove();
	void ChangeMouseAimAttackDir();

	




private:
	USpriteRenderer* Renderer;
	USpriteRenderer* AttackDir;
	std::shared_ptr<UCamera> Camera;

	float4 Color;
	float PlayerAngle;
	//UStateManager PlayerState;
	
	std::string Name = "Gura";
	EPlayerDir PlayerDir = EPlayerDir::E;
	
	// �÷��̾� �������ͽ�
	int HP = 100;
	float Attack = 1;
	float Speed = 150.0f;
	float LineSpeed = Speed * 0.75f;





};

