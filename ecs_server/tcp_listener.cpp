#include "tcp_listener.h"
#include "tcp_listener_component.h"

using namespace terra;
void TcpListener::InitializeComponents()
{
	Add<TcpListenerComponent>();
}
