#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "Menu.h"
#include <EngineCore/Camera.h>
#include "PlayGameMode.h"

std::shared_ptr<class UTitleText> ATitleGameMode::TitleText;

ATitleGameMode::ATitleGameMode()
{
	InputOn();
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	//UEngineTexture::FindRes("HoloCureTitlel.png");

	//std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	//Camera->SetActorLocation(FVector(-150.0f, 100.0f, -100.0f));
	//GetWorld()->SpawnActor<ATitleLogo>("TitleLogo");

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	TitleLogo = GetWorld()->SpawnActor<ATitleLogo>("TitleLogo");
	Menu = GetWorld()->SpawnActor<AMenu>("Menu");

	TitleText = GetWorld()->SpawnActor<UTitleText>("UTitleText");

	std::shared_ptr<ATitleBack> InitialTitleBack = GetWorld()->SpawnActor<ATitleBack>("TitleBack");
	TitleBack.push_back(InitialTitleBack);

	FVector TPos = InitialTitleBack->GetActorLocation();
	for (int i = 1; i < 47; i++)
	{
		std::shared_ptr<ATitleBack> NewTitleBack = GetWorld()->SpawnActor<ATitleBack>("TitleBack");
		NewTitleBack->SetActorLocation({ TPos.X - 38 * i, TPos.Y });
		TitleBack.push_back(NewTitleBack);

	}

	Ame = GetWorld()->SpawnActor<ATitleCharacter>("Ame");
	Gura = GetWorld()->SpawnActor<ATitleCharacter>("Gura");
	//Bae = GetWorld()->SpawnActor<ATitleCharacter>("Bae");
	//Mumei = GetWorld()->SpawnActor<ATitleCharacter>("Mumei");
	//Fauna = GetWorld()->SpawnActor<ATitleCharacter>("Fauna");
	//Ina = GetWorld()->SpawnActor<ATitleCharacter>("Ina");
	//Kiara = GetWorld()->SpawnActor<ATitleCharacter>("Kiara");
	//Kronii = GetWorld()->SpawnActor<ATitleCharacter>("Kiara");


	Mouse = GetWorld()->SpawnActor<AHoloMouse>("Mouse");


}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	AHoloMouse::MouseCursorOn = false;

	//if (true == UEngineInput::IsDown('P') 
	//	/*|| UEngineInput::IsDown(VK_LBUTTON)*/ || UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN) /*|| UEngineInput::IsAnykeyDown()*/)
	//{
	//	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	//	GEngine->ChangeLevel("PlayLevel");
	//}

	SpawnTitleBack(_DeltaTime);
	CursorOFF();

}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}

void ATitleGameMode::SpawnTitleBack(float _DeltaTime)
{

}

void ATitleGameMode::CursorOFF()
{
	ShowCursor(FALSE);
}
