#pragma once

// 설명 :
class USpriteRenderer;
class ABossMonster : public AActor
{

	GENERATED_BODY(AActor)

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

	// 후부질라 스테이터스



	// 스몰 아메 스테이터스



	// 미코다니에 스테이터스


	// 하지만 이렇게 하면 한 클래스에다가 하는 의미가 없네...???



};

