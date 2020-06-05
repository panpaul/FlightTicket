#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "../model/linearEngine.h"

static db::linearEngine* engine;

void Setup()
{
	engine = new db::linearEngine(".");
}

#endif //_SERVICE_H_
