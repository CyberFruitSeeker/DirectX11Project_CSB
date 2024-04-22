#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// ���� :
class AHoloMouse : public AActor
{
	GENERATED_BODY(AActor)
public:
	static FVector MousePos;
	static bool MouseCursorOn;
	
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

	void SetMousePos();

	USpriteRenderer* Renderer;


private:

};

