//
// File:	INIParser.h
// Desc:	Header of INIParser
//
// Author:	Mana Khamphanpheng
// Mail:	mana.kpp@gmail.com
//

#pragma once

#ifndef __MK2014_CLASS_INIPARSER_H__
#define __MK2014_CLASS_INIPARSER_H__

// Library Includes
#include <map>
#include <string>
#include <fstream>

// Local Includes

// Types

// Constants

// Prototypes


class CINIParser
{
	// Member Functions
public:
	CINIParser();
	~CINIParser();

	bool LoadFile(const char* _pcFilename);

	void GetValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);
	void GetValue(const char* _pcSection, const char* _pcKey, const int _iValue);
	void GetValue(const char* _pcSection, const char* _pcKey, const float  _fValue);
	void GetValue(const char* _pcSection, const char* _pcKey, const bool _bValue);

	bool GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue);
	bool GetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue);
	bool GetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue);
	bool GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue);
	bool UpdateINI();

protected:

private:
	CINIParser(const CINIParser& _kr);
	CINIParser& operator= (const CINIParser& _kr);

	bool FindValue(const char* _pcSection, const char* _pcKey, std::map<std::string, std::string>::iterator& _iter);


	// Member Variables
public:

protected:

private:
	std::map<std::string, std::string> m_mapPairs;
	std::map<std::string, std::string>::iterator m_iter;

	std::string m_strFilename;
	std::fstream m_filestream;

};

#endif // __MK2014_CLASS_INIPARSER_H__