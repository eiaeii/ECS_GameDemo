#include "triangle_game.h"
#include "singleton_input.h"
#include "singleton_render.h"
#include "input_system.h"
#include "window_system.h"
#include "graphics_driver_system.h"
#include "render_system.h"
#include "scene_system.h"
#include "texture_system.h"
#include "character_movement_system.h"
#include "player_command_system.h"
using namespace terra;

TriangleGame::TriangleGame()
{
	single_input_ = std::make_unique<SingletonInput>();
	single_window_ = std::make_unique<SingletonWindow>();
	single_renderer_ = std::make_unique<SingletonRenderer>();
	single_texture_ = std::make_unique<SingletonTexture>();

	window_system_ = std::make_unique<WindowSystem>(this);
	graphics_driver_system_ = std::make_unique<GraphicsDriverSystem>(this);
	input_system_ = std::make_unique<InputSystem>(this);
	render_system_ = std::make_unique<RenderSystem>(this);
	scene_system_ = std::make_unique<SceneSystem>(this);
	texture_system_ = std::make_unique<TextureSystem>(this);
	character_movement_system_ = std::make_unique<CharacterMovementSystem>(this);
	player_command_system_ = std::make_unique<PlayerCommandSystem>(this);
}

TriangleGame::~TriangleGame()
{

}

bool TriangleGame::Init()
{
	if (!window_system_->Init())
	{
		return false;
	}
	if (!graphics_driver_system_->Init(single_window_->main_window))
	{
		return false;
	}
	if (!texture_system_->Init())
	{
		return false;
	}
	if (!input_system_->Init())
	{
		return false;
	}
	if (!scene_system_->Init())
	{
		return false;
	}
	return true;
}

void TriangleGame::Update(float time_step)
{
	player_command_system_->Update(time_step);
	character_movement_system_->Update(time_step);
	//world->update

	render_system_->Render();

	Sleep(1);
}

void TriangleGame::Exit()
{
}
