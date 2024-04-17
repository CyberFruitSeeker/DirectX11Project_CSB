#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// Ό³Έν :
class AHoloMouse
{
public:
	// constrcuter destructer
	AHoloMouse();
	~AHoloMouse();

	// delete Function
	AHoloMouse(const AHoloMouse& _Other) = delete;
	AHoloMouse(AHoloMouse&& _Other) noexcept = delete;
	AHoloMouse& operator=(const AHoloMouse& _Other) = delete;
	AHoloMouse& operator=(AHoloMouse&& _Other) noexcept = delete;

protected:

private:

};

