#include <iostream>
#include "Utilities.h"

namespace seneca {
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string token;
		size_t delimiter = str.find(m_delimiter, next_pos);
		if (delimiter != string::npos) {
			token = str.substr(next_pos, delimiter - next_pos);
			next_pos = delimiter + 1;
			more = true;
		}
		else {
			token = str.substr(next_pos);
			next_pos = str.length();
			more = false;
		}
		if (token.length() > m_widthField)
			m_widthField = token.length();

		return token;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}