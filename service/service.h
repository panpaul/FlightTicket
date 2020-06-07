#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <iostream>
#include "../model/LinearEngine.h"

namespace Service
{
	extern db::LinearEngine* engine;
	void Shutdown();
}
#endif //_SERVICE_H_
