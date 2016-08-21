#include "DBCSVService.h"
#include "PlanetTable.h"
#include "StageTable.h"
#define LOAD_CSVFILE(className,tableType,fileName) {\
                                                    className *pCSVFile = new className();\
                                                     if(pCSVFile->load(fileName))\
                                                        m_pTables[tableType] = pCSVFile;\
                                                   }
DBCSVService *DBCSVService::_instance = NULL;
DBCSVService::DBCSVService()
{
	init();
}
DBCSVService::~DBCSVService()
{
	shut();
}
DBCSVService *DBCSVService::getInstance()
{
	if (!_instance)
	{
		_instance = new DBCSVService();
	}
	return _instance;
}
bool DBCSVService::init()
{
	LOAD_CSVFILE(PlanetTable, TT_PLANET, "PlanetData.csv");
	//LOAD_CSVFILE(StageTable, TT_STAGE, "StageData.csv");

	return true;
}
void DBCSVService::shut()
{
	delete m_pTables[TT_PLANET];
}
const PlanetDB* DBCSVService::getPlanetRecordByID(int nID)
{
	return (PlanetDB*)(m_pTables[TT_PLANET]->findRecordByID(nID));
}
const PlanetDB* DBCSVService::getPlanetRecordByName(const char* pName)
{
	return (PlanetDB*)(m_pTables[TT_PLANET]->findRecordByName(pName));
}
//const MAP_PLANETRECORD* DBCSVService::getPlanetAllRecord()
//{
//	return static_cast<PlanetTable*>(m_pTables[TT_PLANET])->getAllRecord();
//}

const StageDB* DBCSVService::getStageRecordByID(int nID)
{
	return (StageDB*)(m_pTables[TT_STAGE]->findRecordByID(nID));
}