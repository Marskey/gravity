#ifndef _DBCSVSERVICE_H__
#define _DBCSVSERVICE_H__
#include "PlanetTable.h"
class DBCSVService
{
public:
	static DBCSVService* getInstance();
	const PlanetDB* getPlanetRecordByID(int nID/*primary key*/);
	const PlanetDB* getPlanetRecordByName(const char* pName/*object name*/);
	//const MAP_PLANETRECORD* getPlanetAllRecord();
	const StageDB* getStageRecordByID(int nID);
	
protected:
	DBCSVService();
	~DBCSVService();
private:
	bool init();
	void shut();

	//PlanetTable接口
//成员
private:
	static DBCSVService* _instance;
	DBTable* m_pTables[TT_AMOUNT];

};
#endif //_DBCSVSERVICE_H__ 