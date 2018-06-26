#include "scene_system.h"
#include "triangle_game.h"
#include "game_object.h"
#include "singleton_render.h"
#include "third_person_character.h"

using namespace terra;

SceneSystem::~SceneSystem()
{
}

bool SceneSystem::Init()
{
	SpawnRandomActor(7);
	return true;
}

void SceneSystem::SpawnRandomActor(int ActorCount)
{
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);

	Vector3 range_min(-5.f, -3.f, 0.f);
	Vector3 range_max(5.f, 3.f, 0.f);

	//make a mouse somewhere- where will these come from?
	for (int i = 0; i < ActorCount; ++i)
	{
		GameObject* go = admin_->SpawnEntity<GameObject>();

		go->InitializeComponents();
		Vector3 born_location = GameMath::GetRandomVector(range_min, range_max);
		go->Get<SceneComponent>()->SetLocation(born_location);

		static const std::array<Vector3, 7> colors{ Colors::White, Colors::Green, Colors::Blue, Colors::LightYellow
			, Colors::LightBlue, Colors::LightPink, Colors::LightGreen };
		go->Get<SceneComponent>()->SetColor(colors[i % 7]);
		go->Get<SpriteComponent>()->SetTexture(admin->GetSingletonTexture()->GetTexture("mouse"));
	}

	ThirdPersonCharacter* third_person_character = admin_->SpawnEntity<ThirdPersonCharacter>();
	third_person_character->InitializeComponents();
	third_person_character->Get<SceneComponent>()->SetColor(Colors::LightGreen);
	third_person_character->Get<SpriteComponent>()->SetTexture(admin->GetSingletonTexture()->GetTexture("cat"));
}
