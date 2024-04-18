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

	// 어떠한 캐릭터를 선택하는 것을 위한 문자열
	void SetName(std::string _Name)
	{
		Name = _Name;
	}

	// 캐릭터가 어느 방향으로 바라보고, 가고있는가?
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

	// 플레이어의 방향에 따라 같이 움직이는 Arrow
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
	
	// 플레이어 스테이터스
	int HP = 100;
	float Attack = 1;
	float Speed = 150.0f;
	float LineSpeed = Speed * 0.75f;





};

