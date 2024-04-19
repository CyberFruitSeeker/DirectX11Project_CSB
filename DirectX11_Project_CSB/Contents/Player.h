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

	// 캐릭터가 어떤 이름의 동작을 가진 것을 수행할 것인가?
	//void SetName(std::string _Name)
	//{
	//	Name = _Name;
	//}

	// 캐릭터가 어느 방향으로 바라보고, 가고있는가?
	EPlayerDir GetPlayerDir()
	{
		return PlayerDir;
	}

	// 8방향 각도
	float GetAngle()
	{
		return PlayerAngle;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Player가 아니라, PlayerState에서 돌려진다.
	void StateUpdate();

	//void PlayerMove(float _DeltaTime);

	void Idle(float _DeltaTime);
	void IdleStart();
	void Run(float _DeltaTime);
	void RunStart();
	void Die(float _DeltaTime);
	
	void CreatePlayerAnimation(std::string _Name);

	void ArrowCursorChange();

	// 플레이어의 방향에 따라 같이 움직이는 Arrow
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
	
	// 플레이어 스테이터스
	int HP = 100;
	float Attack = 1;

	float Speed = 300.0f;
	float LineSpeed = Speed * 0.75f;





};

