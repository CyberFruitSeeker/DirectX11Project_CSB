#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class PlayBackLayer : public AActor
{
	GENERATED_BODY(AActor)


public:
	// constrcuter destructer
	PlayBackLayer();
	~PlayBackLayer();

	// delete Function
	PlayBackLayer(const PlayBackLayer& _Other) = delete;
	PlayBackLayer(PlayBackLayer&& _Other) noexcept = delete;
	PlayBackLayer& operator=(const PlayBackLayer& _Other) = delete;
	PlayBackLayer& operator=(PlayBackLayer&& _Other) noexcept = delete;

	USpriteRenderer* Renderer;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	float4 Color;


};

