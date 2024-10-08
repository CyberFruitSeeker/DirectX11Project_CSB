#pragma once
#include<EngineCore/Actor.h>
#include<EngineCore/imgui.h>
#include<EngineCore/TextWidget.h>


// 설명 :
class UIManager : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	UIManager();
	~UIManager();

	// delete Function
	UIManager(const UIManager& _Other) = delete;
	UIManager(UIManager&& _Other) noexcept = delete;
	UIManager& operator=(const UIManager& _Other) = delete;
	UIManager& operator=(UIManager&& _Other) noexcept = delete;

	UTextWidget* KillCountText = nullptr;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UISpawn();
	void TimeUpdate(float _DeltaTime);
	void KillCountUpdate();
	void HPUpdate();

	void ESCPauseChack();
	void LevelPauseChack();
	void PauseChack();
	void SetBurtonColChack();
	void CollisionPos();
	void LevelUpColChack();
	void LevelUpColPos();

	void RendomIcon();

	UImage* Character = nullptr;
	UImage* CharacterFrame = nullptr;
	UImage* HPBar = nullptr;
	UImage* HPBarBack = nullptr;
	UImage* EXPBar = nullptr;
	UImage* EXPBarBack = nullptr;
	UImage* HUDHP = nullptr;
	UImage* HUDFrame = nullptr;

	UImage* Weapon = nullptr;
	UImage* Item = nullptr;

	UImage* StageText = nullptr;
	UImage* Gold = nullptr;
	UImage* KillCount = nullptr;

	UImage* PauseBack = nullptr;
	UImage* PausedText = nullptr;
	UImage* SetBack = nullptr;
	UImage* CharacterBack = nullptr;
	UImage* HP = nullptr;
	UImage* ATK = nullptr;
	UImage* SPD = nullptr;
	UImage* CRT = nullptr;
	UImage* PickUP = nullptr;
	UImage* Haste = nullptr;


	UImage* Charge = nullptr;

	UTextWidget* HPText = nullptr;
	UTextWidget* HPTextBack = nullptr;
	UTextWidget* TimeUI = nullptr;
	UTextWidget* GoldText = nullptr;

	UTextWidget* StateText = nullptr;
	UTextWidget* CharacterName = nullptr;

	// 스탯 Text
	UTextWidget* StatHPText = nullptr;
	UTextWidget* StatATKText = nullptr;
	UTextWidget* StatSPDText = nullptr;
	UTextWidget* StatCRTText = nullptr;
	UTextWidget* StatPickUPText = nullptr;
	UTextWidget* StatHasteText = nullptr;

	UTextWidget* PauseSkillText = nullptr;
	UTextWidget* PauseStampText = nullptr;
	UTextWidget* PauseCollaborationText = nullptr;
	UTextWidget* PauseContinueText = nullptr;
	UTextWidget* PauseSettingText = nullptr;
	UTextWidget* PauseExitText = nullptr;

	// 레벨업 UI
	UImage* LevelUpText = nullptr;
	UImage* LevelUpIconsCross = nullptr;
	//UImage* LevelUpIconsItem = nullptr;
	UImage* LevelUpIconsStar = nullptr;
	//UImage* LevelUpIconsWeapon = nullptr;

	UTextWidget* ItemText = nullptr;
	UTextWidget* CrossText = nullptr;
	UTextWidget* StarText = nullptr;
	UTextWidget* WeaponText = nullptr;

	UTextWidget* ItemTextExplanation = nullptr;
	UTextWidget* CrossTextExplanation = nullptr;
	UTextWidget* StarTextExplanation = nullptr;
	UTextWidget* WeaponTextExplanation = nullptr;

	UTextWidget* New0 = nullptr;
	UTextWidget* New1 = nullptr;
	UTextWidget* New2 = nullptr;
	UTextWidget* New3 = nullptr;

	UCollision* LevelUpCollision0;
	UCollision* LevelUpCollision1;
	UCollision* LevelUpCollision2;
	UCollision* LevelUpCollision3;

	//왼쪽 상단 ICon
	std::vector<UImage*> WeaponIconBack;
	std::vector<std::vector<UImage*>> WeaponIcon;

	std::vector<UImage*> ITemIconBack;
	std::vector<std::vector<UImage*>> ITemIcon;

	std::vector<UImage*> SetBurtonVector;
	std::vector<UImage*>::iterator SetBurtonIter = SetBurtonVector.begin();
	UCollision* SetBurtonCollision0;
	UCollision* SetBurtonCollision1;
	UCollision* SetBurtonCollision2;
	UCollision* SetBurtonCollision3;
	UCollision* SetBurtonCollision4;
	UCollision* SetBurtonCollision5;

	// StatLine
	std::vector<UImage*> StatLineVector;
	std::vector<UImage*>::iterator StatLineIter = StatLineVector.begin();

	//LevelUpSelectBack
	std::vector<UImage*> LevelUpSelectBackVector;
	std::vector<UImage*>::iterator LevelUpSelectBackIter = LevelUpSelectBackVector.begin();

	std::vector<UImage*> ItemSprites;



private:
	float Hp = 0.0f;
	float AtkTime = 0.0f;
	float Atk = 0.0f;
	bool ExitCheck = false;
	bool IsIcon = false;


};

