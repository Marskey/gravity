#include "stdafx.h"
#ifndef _CSVFILE_H__
#define _CSVFILE_H__
class CSVFile
{
public:
	bool openFile(const char* pFileName);
	bool readNextRow();
private:
	typedef std::vector<std::string> ROWVEC;
	ROWVEC m_csvHead;
	ROWVEC m_csvCurRow;
	std::string fileContent;
	unsigned int lineBegin;
	unsigned long maxSize;
private:
	void readHead();
	bool rowParse(const char* pCurRow,ROWVEC &result);
	int findField(const char* pAttributeName);
public:
	template<typename T>
	bool readField(T& data, const char* pFieldName)
	{
		int n = findField(pFieldName);
		if (n == -1 || n >= m_csvCurRow.size())
		{
			return false;
		}
		std::stringstream strFieldData;
		strFieldData << m_csvCurRow[n];
		strFieldData >> data;
		return true;
	}
};
#endif //_CSVFILE_H__