#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ATitleLogo : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleLogo();
	~ATitleLogo();

	// delete Function
	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Move(float _DeltaTime);



private:
	USpriteRenderer* Renderer;
	USpriteRenderer* BackRenderer;

	float LogoMoveTime = 0.0f;
	float4 LogoMove = FVector::Down * 10.0f;

};

