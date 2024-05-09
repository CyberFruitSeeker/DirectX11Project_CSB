#pragma once

// Ό³Έν :
class Menu
{
public:
	// constrcuter destructer
	Menu();
	~Menu();

	// delete Function
	Menu(const Menu& _Other) = delete;
	Menu(Menu&& _Other) noexcept = delete;
	Menu& operator=(const Menu& _Other) = delete;
	Menu& operator=(Menu&& _Other) noexcept = delete;

protected:

private:

};

