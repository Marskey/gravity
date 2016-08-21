#ifndef _PLANETTABLE_H__
#define _PLANETTABLE_H__
#include "DBTable.h"
class PlanetTable : public DBTable
{
public:
	PlanetTable();
	~PlanetTable();
	void readRow(CSVFile &file);
	bool load(const char* pFileName);
	virtual const Default* findRecordByID(int id);
	virtual const Default* findRecordByName(const char* pName);
private:
	MAP_PLANETRECORD m_planetRecord;
public:
};
#endif//_PLANETTABLE_H__