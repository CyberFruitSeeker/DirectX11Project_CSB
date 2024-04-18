#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AHoloMouse : public AActor
{
	GENERATED_BODY(AActor)
public:
	static float4 CursorPosZero;
	static bool MouseAimOn;
	
	// constrcuter destructer
	AHoloMouse();
	~AHoloMouse();

	// delete Function
	AHoloMouse(const AHoloMouse& _Other) = delete;
	AHoloMouse(AHoloMouse&& _Other) noexcept = delete;
	AHoloMouse& operator=(const AHoloMouse& _Other) = delete;
	AHoloMouse& operator=(AHoloMouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MouseCursorOff();
	void ChangeCursorAimMode();
	void CheckCursorAimMode();

	USpriteRenderer* Renderer;


private:

};

