// 
// File: INIParser.cpp
// Desc: Implementation of INIParser
// 
//  Author:	Mana Khamphanpheng (Originally from MDS school team project with Kieran Thawley and Philip Roigard)
//  Mail:	mana.kpp@gmail.com
// 

// Library Includes
#include <iostream>
#include <algorithm>
#include <sstream>

// Local Includes
#include "Renderer.h"

// This Include
#include "INIParser.h"

// Static Variables

using namespace std;

// Default Constructor
CINIParser::CINIParser()
{
	
}

// Default Destructor
CINIParser::~CINIParser()
{
	m_filestream.close();
}

bool CINIParser::LoadFile(const char *_pcFilename)
{
	m_strFilename = _pcFilename;
	m_strFilename += ".ini";

	m_filestream.open(m_strFilename.c_str());
	if(!m_filestream.is_open())
		return false;
	
	// Define string variables.
	string strLine;
	string strSection;
	string strKey;
	string strValue;
		
	// Loop till end of file
	while(!m_filestream.eof())
	{
		getline(m_filestream, strLine); // Get the next line in the file

		if(strLine.size() == 0)
			continue;

		switch(strLine[0]) // check first character of line
		{
		case '\0':	// blank line
		case ' ':	// invalid line
		case ';':	// comments
			{
				break;
			}
		case '[':	// Section define
			{
				// Only retreave text between [ } and store in strSection
				strSection = strLine.substr( 1, strLine.find(']') - 1);//
				break;
			}
		default:	// Variable define
			{
				size_t iStrPlace = strLine.find('=');	// check location of '='
				if(iStrPlace > strLine.find(' '))		// check for spaces before '='
					iStrPlace = strLine.find(' ');
				if(iStrPlace > strLine.find('	'))		// check for tab before '='
					iStrPlace = strLine.find('	');
					
				strKey = strLine.substr( 0, iStrPlace);	// store key in strKey

				iStrPlace = (strLine.find('='));		// check location of '='
				++iStrPlace;							// increament by one
				// Loop till a none ' ' or '"' is found
				while (strLine[iStrPlace] == ' ' || strLine[iStrPlace] == '	' || strLine[iStrPlace] == '\"')
					++iStrPlace;

				// put first part of value into strValue
				strValue = strLine.substr( iStrPlace, strLine.size() - iStrPlace);

				iStrPlace = strValue.find('\"');
				strValue = strValue.substr( 0, iStrPlace);

				GetValue(strSection.c_str(), strKey.c_str(), strValue.c_str());
				break;
			}
		}
	}
	m_filestream.close();

	return(true);
}

void CINIParser::GetValue(const char *_pcSection, const char *_pcKey, const char *_pcValue)
{
	// Add or Edit a value in the map
	string strKey = static_cast<string>(_pcSection) + "|" + static_cast<string>(_pcKey);
	m_mapPairs[strKey] = static_cast<string>(_pcValue);
}

void CINIParser::GetValue(const char *_pcSection, const char *_pcKey, const int _iValue)
{
	// convert int to char* for GetValue
	stringstream out;
	out << _iValue;

	GetValue(_pcSection, _pcKey, out.str().c_str());
}

void CINIParser::GetValue(const char *_pcSection, const char *_pcKey, const float _fValue)
{
	// convert float to char* for GetValue
	stringstream out;
	out << _fValue;

	GetValue(_pcSection, _pcKey, out.str().c_str());
}

void CINIParser::GetValue(const char *_pcSection, const char *_pcKey, const bool _bValue)
{
	// convert bool to char* for GetValue
	char* pcValue;

	if(_bValue)
	{
		pcValue = "true";
	}
	else
	{
		pcValue = "false";
	}

	GetValue(_pcSection, _pcKey, pcValue);
}

bool CINIParser::GetStringValue(const char *_pcSection, const char *_pcKey, std::string &_rStrValue)
{
	// convert a char* to a string
	if(FindValue(_pcSection, _pcKey, m_iter))
	{
		_rStrValue = m_iter->second;
		return (true);
	}
	else
	{
		return (false);
	}
}

bool CINIParser::GetIntValue(const char *_pcSection, const char *_pcKey, int &_riValue)
{
	// convert a char* to am integer
	if(FindValue(_pcSection, _pcKey, m_iter))
	{
		_riValue = atoi((m_iter->second).c_str());
		return (true);
	}
	else
	{
		return (false);
	}
}

bool CINIParser::GetFloatValue(const char *_pcSection, const char *_pcKey, float &_rfValue)
{
	// convert a char* to a float
	if(FindValue(_pcSection, _pcKey, m_iter))
	{
		_rfValue = static_cast<float>(atof((m_iter->second).c_str()));
		return (true);
	}
	else
	{
		return (false);
	}
}

bool CINIParser::GetBoolValue(const char *_pcSection, const char *_pcKey, bool &_rbValue)
{
	// convert a char* to a bool
	if(FindValue(_pcSection, _pcKey, m_iter))
	{
		if(m_iter->second == "true" || m_iter->second == "True" || m_iter->second == "TRUE" || 
		   m_iter->second == "yes" || m_iter->second == "Yes" || m_iter->second == "YES" || 
		   m_iter->second == "on" || m_iter->second == "On" || m_iter->second == "ON" || 
		   m_iter->second == "1")
		{
			_rbValue = true;
		}
		else if(m_iter->second == "false" || m_iter->second == "False" || m_iter->second == "FALSE" || 
		   m_iter->second == "no" || m_iter->second == "No" || m_iter->second == "NO" || 
		   m_iter->second == "off" || m_iter->second == "Off" || m_iter->second == "OFF" || 
		   m_iter->second == "0")
		{
			_rbValue = false;
		}
		else
		{
			return (false);
		}
		return (true);
	}
	else
	{
		return (false);
	}
}

bool CINIParser::FindValue(const char* _pcSection, const char* _pcKey, std::map<std::string, std::string>::iterator& _iter)
{
	// find a value in the map
	_iter = m_mapPairs.find(static_cast<string>(_pcSection) + "|" + static_cast<string>(_pcKey));
	if(_iter == m_mapPairs.end())
		return(false);
	else
		return(true);
}

bool CINIParser::UpdateINI()
{
	// Update the current .ini file

	m_iter = m_mapPairs.begin();

	m_filestream.clear();

	m_filestream.open(m_strFilename.c_str(), ios::end);

	if(m_filestream.is_open())
	{

		string strLastSection = "";

		while (m_iter != m_mapPairs.end()) // Loop through all items in the map
		{
			// get the section name from map key
			string strSection = "[" + m_iter->first.substr(0, m_iter->first.find('|')) + "]";
			// get the value key from map key
			string strKey = m_iter->first.substr(m_iter->first.find('|') + 1, m_iter->first.size() - m_iter->first.find('|'));

			if (strSection != strLastSection) // check current section with last one
			{
				if(strLastSection != "")
					m_filestream << endl;
				// write a new section to file
				m_filestream << strSection << endl << endl;
			}
			// write a new key and value to file 
			m_filestream << strKey << " = " << m_iter->second << endl;
			
			// update last section
			strLastSection = strSection;

			// move to next map element
			++m_iter;
		}
		// close the current .ini file
		m_filestream.close();
		return(true);
	}
	else
	{
		return(false);
	}
}

