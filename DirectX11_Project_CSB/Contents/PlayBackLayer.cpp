#include "PreCompile.h"
#include "PlayBackLayer.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

PlayBackLayer::PlayBackLayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
	// ��ġ�Ŀ� SetRoot �־������
	SetRoot(Renderer);

}

PlayBackLayer::~PlayBackLayer()
{
}

void PlayBackLayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Holo_map_01.png");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Back);


}

void PlayBackLayer::Tick(float _DeltaTime)
{
	// ���� ������ �ľ��� ���� �� �� �������� ��?��
	Super::Tick(_DeltaTime);


}

