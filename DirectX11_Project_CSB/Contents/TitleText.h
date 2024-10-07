#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Image.h>
#include <EngineCore/TextWidget.h>

// Ό³Έν :
class UTitleText : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UTitleText();
	~UTitleText();

	// delete Function
	UTitleText(const UTitleText& _Other) = delete;
	UTitleText(UTitleText&& _Other) noexcept = delete;
	UTitleText& operator=(const UTitleText& _Other) = delete;
	UTitleText& operator=(UTitleText&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void UISpawn();
	void CollisionCheck();


private:
	UTextWidget* NewGame = nullptr;
	UTextWidget* HoloHouse = nullptr;
	UTextWidget* Shop = nullptr;
	UTextWidget* Scoreboard = nullptr;
	UTextWidget* Challenge = nullptr;
	UTextWidget* Setting = nullptr;
	UTextWidget* Producer = nullptr;
	UTextWidget* Exit = nullptr;

	UCollision* NewGameCol = nullptr;
	UCollision* HoloHouseCol = nullptr;
	UCollision* ShopCol = nullptr;
	UCollision* ScoreboardCol = nullptr;
	UCollision* ChallengeCol = nullptr;
	UCollision* SettingCol = nullptr;
	UCollision* ProducerCol = nullptr;
	UCollision* ExitCol = nullptr;

	UEngineSoundPlayer Sound;
	bool ColChack = false;
	bool ExitChack = false;


};

