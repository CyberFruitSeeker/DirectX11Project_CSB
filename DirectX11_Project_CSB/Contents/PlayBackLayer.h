#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class APlayBackLayer : public AActor
{
	GENERATED_BODY(AActor)


public:
	// constrcuter destructer
	APlayBackLayer();
	~APlayBackLayer();

	// delete Function
	APlayBackLayer(const APlayBackLayer& _Other) = delete;
	APlayBackLayer(APlayBackLayer&& _Other) noexcept = delete;
	APlayBackLayer& operator=(const APlayBackLayer& _Other) = delete;
	APlayBackLayer& operator=(APlayBackLayer&& _Other) noexcept = delete;

	USpriteRenderer* Renderer;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	float4 Color;


};

