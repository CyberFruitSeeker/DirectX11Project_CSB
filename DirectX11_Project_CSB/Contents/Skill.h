#pragma once

// Ό³Έν :
class ASkill : public AActor
{

	GENERATED_BODY(AActor)

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
	void BeginPlay();
	void Tick(float _DeltaTime);

	void SkillRandomSpawn();






private:

};

