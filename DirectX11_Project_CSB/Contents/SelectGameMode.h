#pragma once

// Ό³Έν :
class SelectGameMode
{
public:
	// constrcuter destructer
	SelectGameMode();
	~SelectGameMode();

	// delete Function
	SelectGameMode(const SelectGameMode& _Other) = delete;
	SelectGameMode(SelectGameMode&& _Other) noexcept = delete;
	SelectGameMode& operator=(const SelectGameMode& _Other) = delete;
	SelectGameMode& operator=(SelectGameMode&& _Other) noexcept = delete;

protected:

private:

};

