#include "PlanetTable.h"
#include "Global/Global_Define.h"
#include "stdafx.h"
PlanetTable::PlanetTable()
{

}
PlanetTable::~PlanetTable()
{

}
void PlanetTable::readRow(CSVFile &file)
{
	PlanetDB *pDB = new PlanetDB();
	CCAssert(file.readField(pDB->nID, "ID"),"ID cannot find");
	CCAssert(file.readField(pDB->name, "Name"),"name cannot find");
	CCAssert(file.readField(pDB->omega, "Omega"),"omega cannot find");
	CCAssert(file.readField(pDB->orbitRadius, "OrbitRadius"),"orbitRadius cannot find");
	CCAssert(file.readField(pDB->sptVelocity, "SptVelocity"),"sptVelocity cannot find");
	CCAssert(file.readField(pDB->gravityRadius, "GravityRadius"),"gravityRadius cannot find");
	CCAssert(file.readField(pDB->minVelocity, "MinVelocity"),"minVelocity cannot find");
	m_planetRecord[pDB->nID] = pDB;
}
bool PlanetTable::load(const char* pFileName)
{
	CSVFile csvFile;
	std::string strFullFileName(CSVPATH_PALENT);
	strFullFileName += pFileName;
	if (!csvFile.openFile(strFullFileName.c_str()))
	{
		return false;
	}
	while (csvFile.readNextRow())
	{
		readRow(csvFile);
	}
	return true;
}
const Default* PlanetTable::findRecordByID(int id)
{
	//for (auto it:m_planetRecord)
	//	if (it.second->nID == id)
	//	{
	//		return it.second;
	//	}
	for (MAP_PLANETRECORD::iterator it = m_planetRecord.begin(); it != m_planetRecord.end();++it)
		if (it->second->nID == id)
		{
			return dynamic_cast<Default*>(it->second);
		}
	return NULL;
}
const Default* PlanetTable::findRecordByName(const char* pName)
{
	//for (auto it : m_planetRecord)
	//{
	//	if (it.second->name == pName)
	//	{
	//		return it.second;
	//	}	
	//}
	for (MAP_PLANETRECORD::iterator it = m_planetRecord.begin(); it != m_planetRecord.end();++it)
	{
		//if (it->second->name == pName)
		if (strcmp(it->second->name.c_str(),pName)==0)
		{
			return dynamic_cast<Default*>(it->second);
		}	
	}
	return NULL;
}

