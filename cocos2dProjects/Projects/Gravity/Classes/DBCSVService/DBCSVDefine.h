#ifndef _DBCSVDEFINE_H__
#define _DBCSVDEFINE_H__
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
enum TableType
{
	TT_PLANET,
	TT_STAGE,
	TT_AMOUNT
};
struct Default
{
	int nID;
};
struct PlanetDB :public Default
{
	std::string name;
	int nID;
	float omega;
	float orbitRadius;
	float sptVelocity;
	float gravityRadius;
	float minVelocity;
};
struct StageDB :public Default
{
	int stageID;
	bool isUnlock;
	int evaluation;
	std::string path;
};
typedef std::map<int, Default*> MAP_DEFAULT;
typedef std::map<int, PlanetDB*> MAP_PLANETRECORD;
typedef std::map<int, StageDB*> MAP_STAGERECORD;

#endif //_DBCSVDEFINE_H__