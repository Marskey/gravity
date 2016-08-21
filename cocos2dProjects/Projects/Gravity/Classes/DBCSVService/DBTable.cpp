#include "DBTable.h"
DBTable::DBTable()
{

}
DBTable::~DBTable()
{

}
bool DBTable::load(const char* pFileName)
{
	CSVFile csvFile;
	if (!csvFile.openFile(pFileName))
		return false;
	while (csvFile.readNextRow())
	{
		readRow(csvFile);
	}
	return true;
}
void DBTable::readRow(CSVFile &cf)
{

}
