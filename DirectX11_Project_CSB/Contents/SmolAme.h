#pragma once

// Ό³Έν :
class ASmolAme : public AActor
{
public:
	// constrcuter destructer
	ASmolAme();
	~ASmolAme();

	// delete Function
	ASmolAme(const ASmolAme& _Other) = delete;
	ASmolAme(ASmolAme&& _Other) noexcept = delete;
	ASmolAme& operator=(const ASmolAme& _Other) = delete;
	ASmolAme& operator=(ASmolAme&& _Other) noexcept = delete;




protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;




private:
	USpriteRenderer* Renderer;
	UStateManager* SmolAmeState;


	int Hp = 25000;
	int Atk = 20;
	float Speed = 1.2f;
	float Exp = 5000.0f;




};

