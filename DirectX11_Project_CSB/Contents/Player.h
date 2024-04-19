#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "HoloCureEnum.h"
#include "HoloMouse.h"

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

	// ĳ���Ͱ� � �̸��� ������ ���� ���� ������ ���ΰ�?
	//void SetName(std::string _Name)
	//{
	//	Name = _Name;
	//}

	// ĳ���Ͱ� ��� �������� �ٶ󺸰�, �����ִ°�?
	EPlayerDir GetPlayerDir()
	{
		return PlayerDir;
	}

	// 8���� ����
	float GetAngle()
	{
		return PlayerAngle;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Player�� �ƴ϶�, PlayerState���� ��������.
	void StateUpdate();

	//void PlayerMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void IdleStart();
	void Run(float _DeltaTime);
	void RunStart();
	void Die(float _DeltaTime);
	
	void CreatePlayerAnimation(std::string _Name);

	void ArrowCursorChange();

	// �÷��̾��� ���⿡ ���� ���� �����̴� Arrow
	//void CheckArrowModeChange();
	//void ChangeArrowDirMove();

	void PlayerCursorDirCheck();

	void ChangeMouseAimAttackDir();



	//void KeyMove(float _DeltaTime, float4 _Dir, float _Speed);
	//void KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2);




private:
	USpriteRenderer* Renderer;
	USpriteRenderer* AttackDir;
	USpriteRenderer* PlayerCursor;
	USpriteRenderer* ArrowCursor;
	UCollision* Collision;

	std::shared_ptr<UCamera> Camera;

	float4 Color;
	float4 MousePos;
	float PlayerAngle;
	//UStateManager PlayerState;
	
	std::string Name = "Gura";
	EPlayerDir PlayerDir = EPlayerDir::None;
	
	// �÷��̾� �������ͽ�
	int HP = 100;
	float Attack = 1;

	float Speed = 300.0f;
	float LineSpeed = Speed * 0.75f;





};

