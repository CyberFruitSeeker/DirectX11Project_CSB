#pragma once

// Ό³Έν :
class APlayer;
class USpriteRenderer;
class AMelee : public AActor
{
	GENERATED_BODY(AActor);

public:
	// constrcuter destructer
	static EPlayerDir PlayerDir;
	
	
	AMelee();
	~AMelee();

	// delete Function
	AMelee(const AMelee& _Other) = delete;
	AMelee(AMelee&& _Other) noexcept = delete;
	AMelee& operator=(const AMelee& _Other) = delete;
	AMelee& operator=(AMelee&& _Other) noexcept = delete;

	std::shared_ptr<AMelee> Melee;
	std::shared_ptr<APlayer> Player;



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CursorOff();




private:
	USpriteRenderer* Renderer;
	UCollision* Collision;


	void AttackDir();
	void AttackAimDir();
	void MeleeAttack(float _DeltaTime);
	
	float AttackAngle;
	float AttackTime = 0;

};

