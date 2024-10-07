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

	// ĳ���Ͱ� � �̸��� ������ ���� ���� ������ ���ΰ�?
	//void SetName(std::string _Name)
	//{
	//	Name = _Name;
	//}

	// ĳ���Ͱ� ��� �������� �ٶ󺸰�, �����ִ°�?
	EPlayerDir GetPlayerDir()
	{
		return DirState;
	}

	// 8���� ����
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

	// Player�� �ƴ϶�, PlayerState���� ��������.
	void StateUpdate();


	// ĳ���� ������Ʈ
	void Idle(float _DeltaTime);
	void IdleStart();
	void Run(float _DeltaTime);
	void RunStart();
	void Die(float _DeltaTime);
	
	std::string Name = "Gura";
	void CreatePlayerAnimation(std::string _Name);

	void ArrowCursorChange();

	// �÷��̾��� ���⿡ ���� ���� �����̴� Arrow
	//void CheckArrowModeChange();
	//void ChangeArrowDirMove();

	void PlayerCursorDirCheck();
	void ChangeMouseAimAttackDir();

	// �ݸ���
	void PlayerCollisionInteractiveToMonster();


	void CalStatus();
	
	void SpawnRanged(float _DeltaTime);









private:
	// �ʵ� ���� �� �Լ� ��Ī ��ġ��ų ��
	// => �׷��� ������ ���忡��(����ó��) �߻���
	
	USpriteRenderer* Renderer;
	USpriteRenderer* ArrowCursor;
	UCollision* Collision;

	// �÷��̾� ����(����)�� �߻���Ű��, ������� �ϰ�
	std::vector<std::shared_ptr<AWeapon>> VPlayerWeapons;
	std::vector<std::shared_ptr<AWeapon>>::iterator VPlayerWeaponsIter = VPlayerWeapons.begin();
	
	//UStateManager PlayerState;
	
	std::shared_ptr <UCamera> Camera;
	EPlayerDir DirState = EPlayerDir::E;
	
	// �÷��̾� �������ͽ�
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


