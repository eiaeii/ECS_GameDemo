#pragma once

#include "core.h"
#include "entity_admin.h"
#include "server_fwd.h"

namespace terra
{
	class Server : public EntityAdmin
	{
	private:
		bool should_keep_running_{ true };

		//System
		std::unique_ptr<ConnectionSystem> connection_system_;

	public:
		static std::unique_ptr<Server> server_instance_;
		static bool StaticInit();
		Server();
		bool Init() override;
		int Run(); 

		//void HandleNewClient(ClientProxyPtr inClientProxy);
		//void HandleLostClient(ClientProxyPtr inClientProxy);

		//RoboCatPtr	GetCatForPlayer(int inPlayerId);
		//void	SpawnCatForPlayer(int inPlayerId);


	private:
		void	Update(float time_step);
		//bool	InitNetworkManager();
		//void	SetupWorld();

	};
}