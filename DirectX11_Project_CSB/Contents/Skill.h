#pragma once

// Ό³Έν :
class ASkill
{
public:
	// constrcuter destructer
	ASkill();
	~ASkill();

	// delete Function
	ASkill(const ASkill& _Other) = delete;
	ASkill(ASkill&& _Other) noexcept = delete;
	ASkill& operator=(const ASkill& _Other) = delete;
	ASkill& operator=(ASkill&& _Other) noexcept = delete;

protected:

private:

};

