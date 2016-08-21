#include "Config.h"
CCArray *collectionArr;
Config *Config::_instance = NULL;
Config* Config::getInstance()
{
	if (!_instance)
	{
		_instance = new Config();
	}
	return _instance;
}
Config::Config()
{

}
Config::~Config()
{
}
