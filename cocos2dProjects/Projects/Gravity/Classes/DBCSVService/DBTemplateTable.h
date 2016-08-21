#ifndef _DBTEMPLATETABLE_H__
#define _DBTEMPLATETABLE_H__
#include "DBCSVDefine.h"
#include "CSVFile.h"
template<typename T_STRUCT, typename T_MAP>//第一个是dbcsvdefine.h里面的struct，第二个是里面的map型
class DBTemplateTable
{
public:
	DBTemplateTable();
	~DBTemplateTable();
	bool load(const char* pFileName);
	void readRow(CSVFile &file);
	const T_STRUCT* findRecordByID(int id);
	const T_STRUCT* findRecordByName(const char* pName);
	const T_MAP* getAllRecord();
private:
	T_MAP m_mapRecord;
};
template <typename T_STRUCT, typename T_MAP>
DBTemplateTable<T_STRUCT, T_MAP>::DBTemplateTable()
{

}
template <typename T_STRUCT, typename T_MAP>
DBTemplateTable<T_STRUCT, T_MAP>::~DBTemplateTable()
{
	m_mapRecord.clear();
	delete m_mapRecord;
}
template < typename T_STRUCT, typename T_MAP >
bool DBTemplateTable < T_STRUCT, T_MAP > ::load(const char* pFileName)
{
	CSVFile csvFile;
	if (!csvFile.openFile(pFileName))
	{
		return false;
	}
	while (csvFile.readNextRow())
	{
		readRow(csvFile);
	}
	return true;
}
template<typename T_STRUCT, typename T_MAP>
void DBTemplateTable < T_STRUCT, T_MAP >::readRow(CSVFile &file)
{
	T_STRUCT *pDB = new T_STRUCT();
	assert(file.readField(pDB->nID, "ID"));
	assert(file.readField(pDB->name, "Name"));
	assert(file.readField(pDB->omega, "Omega"));
	assert(file.readField(pDB->orbitRadius, "OrbitRadius"));
	assert(file.readField(pDB->sptVelocity, "SptVelocity"));
	m_mapRecord[pDB->nID] = pDB;
}

template<typename T_STRUCT, typename T_MAP>
const T_STRUCT* DBTemplateTable < T_STRUCT, T_MAP >::findRecordByID(int id)
{
	for (auto it : m_mapRecord)
		if (it.second->nID == id)
		{
			return it.second;
		}
	return nullptr;
}
template <typename T_STRUCT, typename T_MAP>
const T_STRUCT* DBTemplateTable < T_STRUCT, T_MAP >::findRecordByName(const char* pName)
{
	for (auto it : m_mapRecord)
		if (it.second->name == pName)
		{
			return it.second;
		}
	return nullptr;
}
template <typename T_STRUCT, typename T_MAP>
const T_MAP* DBTemplateTable < T_STRUCT, T_MAP >::getAllRecord()
{
	return m_mapRecord;
}
#endif //_DBTEMPLATETABLE_H__