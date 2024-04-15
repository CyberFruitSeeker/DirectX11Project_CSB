#include "PreCompile.h"
#include "PlayBackLayer.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

APlayBackLayer::APlayBackLayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
	InputOn();

}

APlayBackLayer::~APlayBackLayer()
{
}

void APlayBackLayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Holo_map_01.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Back);


}

void APlayBackLayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할 때가 올 수 있을지도 몰?루
	Super::Tick(_DeltaTime);


}

