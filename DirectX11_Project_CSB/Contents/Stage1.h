#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AStage1 : public AActor
{
public:
	// constrcuter destructer
	AStage1();
	~AStage1();

	// delete Function
	AStage1(const AStage1& _Other) = delete;
	AStage1(AStage1&& _Other) noexcept = delete;
	AStage1& operator=(const AStage1& _Other) = delete;
	AStage1& operator=(AStage1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:

};

