#include "Global/Global_Define.h"
#include "CSVFile.h"
bool CSVFile::openFile(const char* pFileName)
{
	maxSize = 0;
	unsigned char* buffer = NULL;
	buffer = CCFileUtils::sharedFileUtils()->getFileData(pFileName,"r",&maxSize);
	if (!buffer)
	{
		CCLog("open m_csvFile in CSVFile.cpp in line 12 failed");
		return false;
	}
	fileContent = (char*)buffer;
	fileContent = fileContent.substr(0, maxSize);
	readHead();
	return true;
}
bool CSVFile::readNextRow()
{
	if (lineBegin == maxSize)
	{
		return false;
	}
	unsigned int lineEnd = fileContent.find('\n', lineBegin);
	std::string tempStr = fileContent.substr(lineBegin, lineEnd - lineBegin + 1);
	rowParse(tempStr.c_str(), m_csvCurRow);
	lineBegin = lineEnd + 1;
	return true;
}
void CSVFile::readHead()
{
	lineBegin = 0;
	unsigned int lineEnd = fileContent.find('\n', 0);
	std::string tempStr = fileContent.substr(lineBegin, lineEnd-lineBegin+1);
	rowParse(tempStr.c_str(), m_csvHead);
	lineBegin = lineEnd + 1;
}
bool CSVFile::rowParse(const char* pCurRow, ROWVEC &result)
{
	int strSize = strlen(pCurRow);
	result.clear();
	if (!strSize)
	{
		return false;
	}
	enum stateType
	{
		//新字段的开始
		NEWFIELDSTART,
		//非引号字段
		NONQUOTESFIELD,
		//引号字段
		QUOTESFIELD,
		//字段分隔
		FIELDSEPARATOR,
		//引号字段中的引号
		QUOTESINQUOTESFIELD,
		//语法错误
		MYERROR,
	};
	std::string  tempField;
	stateType state = NEWFIELDSTART;
	for (int i = 0; i <= strSize; ++i)
	{
		const char ch = pCurRow[i];
		switch (state)
		{
		case NEWFIELDSTART:
		{
			if (ch == '"')
			{
				state = QUOTESFIELD;
			}
			else if (ch == ',')
			{
				state = FIELDSEPARATOR;
			}
			else if (ch == '\r' || ch == '\n')
			{
				state = MYERROR;
			}
			else
			{
				tempField.push_back(ch);
				state = NONQUOTESFIELD;
			}
		}
			break;
		case NONQUOTESFIELD:
		{
			if (ch == ',')
			{
				result.push_back(tempField);
				tempField.clear();
				state = FIELDSEPARATOR;
			}
			else if (ch == '\n'||ch == '\r')
			{
				result.push_back(tempField);
			}
			else
			{
				tempField.push_back(ch);
			}
		}
			break;
		case QUOTESFIELD:
		{
			if (ch == '"')
			{
				state = QUOTESINQUOTESFIELD;
			}
			else	
			{
				tempField.push_back(ch);
			}
		}
			break;
		case FIELDSEPARATOR:
		{
			if (ch == '"')
			{
				state = QUOTESFIELD;
			}
			else 
			{
				tempField.push_back(ch);
				state = NONQUOTESFIELD;
			}
		}
			break;
		case QUOTESINQUOTESFIELD:
		{
			if (ch == ',')
			{
				result.push_back(tempField);
				tempField.clear();
				state = FIELDSEPARATOR;
			}
			else if (ch == '"')
			{
				tempField.push_back(ch);
				state = QUOTESFIELD;
			}
			else if (ch == '\n')
			{
				result.push_back(tempField);
			}
			else
			{
				CCLog("erroraaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
				state = MYERROR;
			}
		}
			break;
		case MYERROR:
		{
			return false;
		}
			break;
		default:
			break;
		}
	}
	return true;
}
int CSVFile::findField(const char* pAttributeName)
{
	//for (auto it = m_csvHead.begin(); it != m_csvHead.end(); ++it)
	//{
	//	if (*it == pAttributeName)
	//	{
	//		return int(it - m_csvHead.begin());
	//	}
	//}
	//for (std::vector<std::string>::iterator it = m_csvHead.begin(); it != m_csvHead.end(); ++it)
	//{
	//	if (*it == pAttributeName)
	//	{
	//		if (pAttributeName == "MinVelocity")
	//		{
	//			CCLog("is MinVelocity");
	//			CCLog("%d", int(it - m_csvHead.begin()));
	//		}
	//		return int(it - m_csvHead.begin());
	//	}
	//}
	for (int i = 0; i < m_csvHead.size();++i)
	{
		//if (m_csvHead[i] == pAttributeName)
		if (strcmp(m_csvHead[i].c_str(),pAttributeName)==0)
		{
			return i;
		}
	}
	return -1;
}

