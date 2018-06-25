#include "render_system.h"
#include "triangle_game.h"
#include <SDL.h>
#include "ecs_iterator.h"
#include "graphics_driver_system.h"
#include "singleton_render.h"
#include "sprite_component.h"
#include "scene_component.h"

using namespace terra;

RenderSystem::RenderSystem(EntityAdmin* admin)
	: BaseSystem(admin)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Render()
{
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);
	admin->GetGraphicsDriverSystem()->Clear();

	RenderComponents();

	admin->GetGraphicsDriverSystem()->Present();
}

void RenderSystem::RenderComponents()
{
	//for (SpriteComponent* c : ComponentItr<SpriteComponent>(admin_))
	//{
	//	
	//}

	for (std::tuple<SpriteComponent*, SceneComponent*>&& tup : ComponentItr<SpriteComponent, SceneComponent>(admin_))
	{
		SpriteComponent* sprite_component = std::get<0>(tup);
		SceneComponent* scene_component = std::get<1>(tup);
		RenderSprite(sprite_component, scene_component);
	}
}

void RenderSystem::RenderSprite(SpriteComponent* sprite_component, SceneComponent* scene_component)
{
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);
	TexturePtr texture = sprite_component->GetTexture();
	if (texture )
	{
		SDL_Rect view_port = admin->GetSingletonRender()->GetLogicalViewport();
		SDL_Rect view_tranform;
		view_tranform.x = view_port.w / 2;
		view_tranform.y = view_port.h / 2;
		view_tranform.w = 100;
		view_tranform.h = 100;

		// Texture color multiplier
		Vector3 color = scene_component->GetColor();
		Uint8 r = static_cast<Uint8>(color.mX * 255);
		Uint8 g = static_cast<Uint8>(color.mY * 255);
		Uint8 b = static_cast<Uint8>(color.mZ * 255);
		SDL_SetTextureColorMod(texture->GetData(), r, g, b);

		// Compute the destination rectangle
		Vector3 objLocation = scene_component->GetLocation();
		float objScale = scene_component->GetScale();
		SDL_Rect dstRect;
		dstRect.w = static_cast<int>(texture->GetWidth() * objScale);
		dstRect.h = static_cast<int>(texture->GetHeight() * objScale);
		dstRect.x = static_cast<int>(objLocation.mX * view_tranform.w + view_tranform.x - dstRect.w / 2);
		dstRect.y = static_cast<int>(objLocation.mY * view_tranform.h + view_tranform.y - dstRect.h / 2);

		// Blit the texture
		SDL_Renderer* renderer = admin->GetSingletonRender()->renderer;
		SDL_RenderCopyEx(renderer, texture->GetData(), nullptr,
			&dstRect, GameMath::ToDegrees(scene_component->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}
