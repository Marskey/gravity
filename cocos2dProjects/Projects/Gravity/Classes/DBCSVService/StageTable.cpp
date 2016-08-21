#include "StageTable.h"
#include "stdafx.h"
#include "Global/Global_Define.h"
StageTable::StageTable()
{

}
StageTable::~StageTable()
{

}
void StageTable::readRow(CSVFile &file)
{
	StageDB *pDB = new StageDB();
	CCAssert(file.readField(pDB->stageID, "StageID"),"ID cannot find");
	CCAssert(file.readField(pDB->isUnlock, "Unlock"),"unlock cannot find");
	CCAssert(file.readField(pDB->evaluation, "Evaluation"),"evaluation cannot find");
	CCAssert(file.readField(pDB->path, "PngFilePath"),"png cannot find");
	_mapRecord[pDB->stageID] = pDB;
}
bool StageTable::load(const char* pFileName)
{
	CSVFile csvFile;
	std::string strFullFileName(CSVPATH_STAGE);
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
const Default* StageTable::findRecordByID(int id)
{
	for (MAP_STAGERECORD::iterator it = _mapRecord.begin(); it != _mapRecord.end();++it)
		if (it->second->stageID == id)
		{
			return dynamic_cast<Default*>(it->second);
		}
	return NULL;
}

