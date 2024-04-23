#pragma once

// Ό³Έν :
class EngineStructuredBuffer
{
public:
	// constrcuter destructer
	EngineStructuredBuffer();
	~EngineStructuredBuffer();

	// delete Function
	EngineStructuredBuffer(const EngineStructuredBuffer& _Other) = delete;
	EngineStructuredBuffer(EngineStructuredBuffer&& _Other) noexcept = delete;
	EngineStructuredBuffer& operator=(const EngineStructuredBuffer& _Other) = delete;
	EngineStructuredBuffer& operator=(EngineStructuredBuffer&& _Other) noexcept = delete;

protected:

private:

};

