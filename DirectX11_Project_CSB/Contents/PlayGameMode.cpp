#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBackLayer.h"

#include <random>
#include <EngineCore/Camera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineDebugMsgWindow.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::FindRes("Holo_map_04.png");

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<APlayer>("Player");

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}