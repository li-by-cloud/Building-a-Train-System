#include <iostream>
#include "Station.h"
#include <iomanip>
namespace seneca {
	Station::Station(string nameItem, unsigned serialNum, unsigned qunatityStock, string desc)
	{
	}
	const std::string& Station::getItemName() const
	{
		return name;
	}
	size_t Station::getNextSerialNumber()
	{
		return serialNumber;
	}
	size_t Station::getQuantity() const
	{
		return stock;
	}
	void Station::updateQuantity()
	{
		if (stock > 0)
			stock--;

	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (full = false) {
			os << id_generator << setfill(3)  << "| " << name << setfill(m_widthField) << "| " << serialNumber << setfill(6) << "| " << endl;
			os << "| " << serialNumber << setfill(6) << "| " << stock << setfill(4) << "| " << description << endl;
		}
	}
}