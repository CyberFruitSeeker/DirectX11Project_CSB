#pragma once

// Ό³Έν :
class ABossMonster : public AActor
{
public:
	// constrcuter destructer
	ABossMonster();
	~ABossMonster();

	// delete Function
	ABossMonster(const ABossMonster& _Other) = delete;
	ABossMonster(ABossMonster&& _Other) noexcept = delete;
	ABossMonster& operator=(const ABossMonster& _Other) = delete;
	ABossMonster& operator=(ABossMonster&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:

};

