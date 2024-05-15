#include "PreCompile.h"
#include "Menu.h"
#include "Button.h"

AMenu::AMenu()
{
}

AMenu::~AMenu()
{
}



void AMenu::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 8; i++)
	{
		Button = GetWorld()->SpawnActor<AButton>("Button");
		Button->SetActorLocation({ 430.0f, 220.0f - (i * 70.0f) });
	}
}





void AMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
