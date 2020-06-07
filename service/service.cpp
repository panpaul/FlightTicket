#include "service.h"

db::LinearEngine* Service::engine = new db::LinearEngine(".");

void Service::Shutdown()
{
	delete engine;
}