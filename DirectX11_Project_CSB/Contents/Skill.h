#pragma once

// Ό³Έν :
class Skill
{
public:
	// constrcuter destructer
	Skill();
	~Skill();

	// delete Function
	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;

protected:

private:

};

