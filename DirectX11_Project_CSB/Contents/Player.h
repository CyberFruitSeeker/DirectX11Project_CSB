#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "HoloCureEnum.h"


class AWeapon;
class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	static float4 PlayerPos;
	static float4 PlayerColPos;

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
		return DirState;
	}

	// 8방향 각도
	float GetAngle()
	{
		return Angle;
	}

	float GetHp()
	{
		return Hp;
	}

	float GetAtk()
	{
		return Atk;
	}

	float GetAtkTime()
	{
		return AtkTime;
	}

	float GetSpeed()
	{
		return Speed;
	}

	template<typename WeaponType>
	void AddWeapon(std::string _Name);




protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// Player가 아니라, PlayerState에서 돌려진다.
	void StateUpdate();


	// 캐릭터 스테이트
	void Idle(float _DeltaTime);
	void IdleStart();
	void Run(float _DeltaTime);
	void RunStart();
	void Die(float _DeltaTime);
	
	std::string Name = "Gura";
	void CreatePlayerAnimation(std::string _Name);

	void ArrowCursorChange();

	// 플레이어의 방향에 따라 같이 움직이는 Arrow
	//void CheckArrowModeChange();
	//void ChangeArrowDirMove();

	void PlayerCursorDirCheck();
	void ChangeMouseAimAttackDir();

	// 콜리전
	void PlayerCollisionInteractiveToMonster();


	void CalStatus();
	
	void SpawnRanged(float _DeltaTime);









private:
	// 필드 변수 및 함수 명칭 일치시킬 것
	// => 그렇지 않으면 빌드에러(예외처리) 발생함
	
	USpriteRenderer* Renderer;
	USpriteRenderer* ArrowCursor;
	UCollision* Collision;

	// 플레이어 무기(공격)을 발생시키고, 사라지게 하고
	std::vector<std::shared_ptr<AWeapon>> VPlayerWeapons;
	std::vector<std::shared_ptr<AWeapon>>::iterator VPlayerWeaponsIter = VPlayerWeapons.begin();
	
	//UStateManager PlayerState;
	
	std::shared_ptr <UCamera> Camera;
	EPlayerDir DirState = EPlayerDir::E;
	
	// 플레이어 스테이터스
	int Hp = 100;
	float Atk = 1;
	float CriRate = 0.05f;
	float Haste = 0.0f;
	float AtkTime = 1.0f;
	float Speed = 0.75f;
	float CalSpeed = ContentsValue::BaseSpeed * Speed;
	float LineSpeed = CalSpeed * 0.75f;
	float Exp = 0;

	float4 Color;
	float4 MousePos;
	float Angle;

	//float Speed = 300.0f;
	//float LineSpeed = Speed * 0.75f;
	//float Speed = 175.0f;
	//float LineSpeed = CalSpeed * 0.004f;



	void KeyMove(float _DeltaTime, float4 _Dir, float _Speed);
	void KeyLineMove(float _DeltaTime, float4 _Dir1, float4 _Dir2);

};


