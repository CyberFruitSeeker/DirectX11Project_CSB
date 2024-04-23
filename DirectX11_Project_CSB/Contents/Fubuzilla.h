#pragma once

// Ό³Έν :
class AFubuzilla : public AActor
{
public:
	// constrcuter destructer
	AFubuzilla();
	~AFubuzilla();

	// delete Function
	AFubuzilla(const AFubuzilla& _Other) = delete;
	AFubuzilla(AFubuzilla&& _Other) noexcept = delete;
	AFubuzilla& operator=(const AFubuzilla& _Other) = delete;
	AFubuzilla& operator=(AFubuzilla&& _Other) noexcept = delete;




protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);





private:
	int Hp = 8000;
	int Atk = 15;
	float Speed = 0.8f;
	float Exp = 2000.0f;






};

