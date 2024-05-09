#pragma once
#include "Melee.h"

// 설명 :
class AGura : public AMelee
{

	GENERATED_BODY(AMelee)

public:
	// constrcuter destructer
	AGura();
	~AGura();

	// delete Function
	AGura(const AGura& _Other) = delete;
	AGura(AGura&& _Other) noexcept = delete;
	AGura& operator=(const AGura& _Other) = delete;
	AGura& operator=(AGura&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckHit();

	// POA : 파워 오브 아틀란티스
	void POARandomSpawn();






private:
	UCollision* CollisionR0;
	UCollision* CollisionR1;
	UCollision* CollisionR2;
	UCollision* CollisionR3;
	UCollision* CollisionR4;
	UCollision* CollisionR5;

	

};

