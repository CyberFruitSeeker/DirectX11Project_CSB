#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// ���� :
class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	static FVector PlayerPosZero;
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager PlayerState;


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
	

	//void PlayerInteractiveToWorld(float _DeltaTime);




private:
	USpriteRenderer* Renderer;
	float4 Color;
	//UStateManager PlayerState;

};

