/************************************************************************
*  Name: StageTable.h
*  Purpose:
*  Author: Marskey
*  time: 2015-06-09	
*  version: 1.0
/************************************************************************/
#ifndef HEADER__STAGETABLE
#define HEADER__STAGETABLE
#include "DBTable.h"
class StageTable : public DBTable
{
public:
	StageTable();
	~StageTable();
	void readRow(CSVFile &file);
	bool load(const char* pFileName);
	virtual const Default* findRecordByID(int id);
private:
	MAP_STAGERECORD _mapRecord;
};

#endif // HEADER__STAGETABLE