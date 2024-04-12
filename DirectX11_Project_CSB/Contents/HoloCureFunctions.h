#pragma once

// Ό³Έν :
class HoloCureFunctions
{
public:
	// constrcuter destructer
	HoloCureFunctions();
	~HoloCureFunctions();

	// delete Function
	HoloCureFunctions(const HoloCureFunctions& _Other) = delete;
	HoloCureFunctions(HoloCureFunctions&& _Other) noexcept = delete;
	HoloCureFunctions& operator=(const HoloCureFunctions& _Other) = delete;
	HoloCureFunctions& operator=(HoloCureFunctions&& _Other) noexcept = delete;

protected:

private:

};

