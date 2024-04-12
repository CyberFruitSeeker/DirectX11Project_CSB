#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "PlayBackLayer.h"
#include "HoloCureConstValue.h"
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

	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::FindRes("Holo_map_01.png");

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<APlayer>("Player");

	{

	}

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	// µð¹ö±ë¿ë UI ·»´õ¸µ
	{
		/*float4 PlayerPos = Player->GetActorLocation();*/
		//FIntPoint Index = PosToIndex(PlayerPos);
		//CurIndex = Index;
		/*UEngineDebugMsgWindow::PushMsg(std::format("PlayerPos : {}", PlayerPos.ToString()));*/
		//UEngineDebugMsgWindow::PushMsg(std::format("PlayerIndex : {}, {}", Index.X, Index.Y));
	}


}