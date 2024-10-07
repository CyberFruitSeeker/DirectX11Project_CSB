#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ASelectBack : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ASelectBack();
	~ASelectBack();

	// delete Function
	ASelectBack(const ASelectBack& _Other) = delete;
	ASelectBack(ASelectBack&& _Other) noexcept = delete;
	ASelectBack& operator=(const ASelectBack& _Other) = delete;
	ASelectBack& operator=(ASelectBack&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void BackMove(float _DeltaTime);


private:

	USpriteRenderer* SelectBack;
	USpriteRenderer* SelectBackGround;

	float MoveSpeed = 0.5f;

};

