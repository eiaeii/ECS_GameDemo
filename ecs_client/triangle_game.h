#pragma once

#include "entity_admin.h"
#include <SDL_events.h>
#include "game_fwd.h"

namespace terra
{
	class TriangleGame : public EntityAdmin
	{
	private:
		//Singleton
		std::unique_ptr<SingletonInput> single_input_;
		std::unique_ptr<SingletonWindow> single_window_;
		std::unique_ptr<SingletonRenderer> single_renderer_;
		std::unique_ptr<SingletonTexture> single_texture_;
		//System
		std::unique_ptr<InputSystem> input_system_;
		std::unique_ptr<WindowSystem> window_system_;
		std::unique_ptr<GraphicsDriverSystem> graphics_driver_system_;
		std::unique_ptr<RenderSystem> render_system_;
		std::unique_ptr<SceneSystem> scene_system_;
		std::unique_ptr<TextureSystem> texture_system_;
		std::unique_ptr<CharacterMovementSystem> character_movement_system_;
		std::unique_ptr<PlayerCommandSystem> player_command_system_;
	public:
		TriangleGame();
		~TriangleGame();

		virtual bool Init() override;
		virtual void Update(float time_step) override;
		virtual void Exit() override;

		//Singleton
		SingletonInput* GetSingletonInput() { return single_input_.get(); }
		SingletonWindow* GetSingletonWindow() { return single_window_.get(); }
		SingletonRenderer* GetSingletonRender() { return single_renderer_.get(); }
		SingletonTexture* GetSingletonTexture() { return single_texture_.get(); }
		//System
		InputSystem* GetInputSystem() { return input_system_.get(); }
		WindowSystem* GetWindowSystem() { return window_system_.get(); }
		GraphicsDriverSystem* GetGraphicsDriverSystem() { return graphics_driver_system_.get(); }
		RenderSystem* GetRenderSystem() { return render_system_.get(); }

	};
}