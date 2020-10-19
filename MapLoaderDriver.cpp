#include "MapLoaderDriver.h"
#include "MapLoader.h"
#include "Map.h"
#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>

MapLoaderDriver::MapLoaderDriver()
{
	MapLoader mapLoad;
	mapLoad.loadmap();
}

MapLoaderDriver::~MapLoaderDriver()
{
}
