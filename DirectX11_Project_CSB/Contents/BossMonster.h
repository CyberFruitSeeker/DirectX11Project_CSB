#pragma once

// ���� :
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

	// �ĺ����� �������ͽ�



	// ���� �Ƹ� �������ͽ�



	// ���ڴٴϿ� �������ͽ�


	// ������ �̷��� �ϸ� �� Ŭ�������ٰ� �ϴ� �ǹ̰� ����...???



};

