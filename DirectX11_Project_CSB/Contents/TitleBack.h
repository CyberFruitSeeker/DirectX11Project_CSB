#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class ATitleBack : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ATitleBack();
	~ATitleBack();

	// delete Function
	ATitleBack(const ATitleBack& _Other) = delete;
	ATitleBack(ATitleBack&& _Other) noexcept = delete;
	ATitleBack& operator=(const ATitleBack& _Other) = delete;
	ATitleBack& operator=(ATitleBack&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void BackMove(float _DeltaTime);




private:
	USpriteRenderer* TitleBack;

	float MoveSpeed = 0.5f;


};

