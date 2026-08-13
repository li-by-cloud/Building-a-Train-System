#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace seneca {

	int Station::id_generator = 0;

	int Station::m_widthField = 0;


	Station::Station(string nameItem)
	{
		stationId = ++id_generator;

		seneca::Utilities util;
		bool more = true;
		size_t pos = 0u;

		name = util.extractToken(nameItem, pos, more);
		serialNumber = stoi(util.extractToken(nameItem, pos, more));
		stock = stoi(util.extractToken(nameItem, pos, more));
		m_widthField = util.getFieldWidth();
		description = util.extractToken(nameItem, pos, more);
	}

	const std::string& Station::getItemName() const
	{
		return name;
	}

	size_t Station::getNextSerialNumber()
	{
		return serialNumber++;
	}

	size_t Station::getQuantity() const
	{
		return stock;
	}

	void Station::updateQuantity()
	{
		if (stock > 0) {
			stock--;
		}

	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << setw(idWidth) << setfill('0') << stationId << " | "
			<< setw(m_widthField) << setfill(' ') << left << name << " | "
			<< setw(serialWidth) << right << setfill('0') << serialNumber << " | ";
		
		if (full)
			os << right << setw(quantityWidth) << setfill(' ') << stock << " | " << left << description;
		os << endl;
	}

	std::ostream& operator<<(std::ostream& os, const Station& t)
	{
		return os;
	}
}