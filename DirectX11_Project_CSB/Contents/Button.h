#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AButton : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	AButton();
	~AButton();

	// delete Function
	AButton(const AButton& _Other) = delete;
	AButton(AButton&& _Other) noexcept = delete;
	AButton& operator=(const AButton& _Other) = delete;
	AButton& operator=(AButton&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck();
	bool CurCollision = false;


private:
	USpriteRenderer* MenuRenderer;
	UCollision* Collision;
	UEngineSoundPlayer Sound;

};

