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
	// ���� ������ �ľ��� ���� �� �� �������� ��?��
	Super::Tick(_DeltaTime);


}

