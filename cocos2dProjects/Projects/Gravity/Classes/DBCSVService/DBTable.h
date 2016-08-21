#ifndef _DBTABLE_H__
#define _DBTABLE_H__
#include "DBCSVDefine.h"
#include "CSVFile.h"
class DBTable
{
public:

	DBTable();
	~DBTable();
	bool load(const char* pFileName);
	void readRow(CSVFile &file);
	virtual const Default* findRecordByID(int id){ return 0; }
	virtual const Default* findRecordByName(const char* pName){ return 0; }
	
};
#endif //_DBTABLE_H__