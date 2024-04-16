#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class Monster_Deadbeat : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	Monster_Deadbeat();
	~Monster_Deadbeat();

	// delete Function
	Monster_Deadbeat(const Monster_Deadbeat& _Other) = delete;
	Monster_Deadbeat(Monster_Deadbeat&& _Other) noexcept = delete;
	Monster_Deadbeat& operator=(const Monster_Deadbeat& _Other) = delete;
	Monster_Deadbeat& operator=(Monster_Deadbeat&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetMonsterStatus();


private:
	USpriteRenderer* Renderer;
	float MonsterSpeed = 250.0f;

	int DeadbeatHP = 0;
	int DeadbeatBatHP = 0;
	int DeadbeatGangAHP = 0;

	int DeadbeatAtt = 0;
	int DeadbeatBatAtt = 0;
	int DeadbeatGangAAtt = 0;

};

enum class DeadBeats
{
	Deadbeat,
	DeadbeatBat,
	DeadbeatGangA,
};
