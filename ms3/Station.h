#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
#include <iostream>
#include <iomanip>
namespace seneca {

	class Station {

		static const int idWidth = 3;
		static const int serialWidth = 6;
		static const int quantityWidth = 4;


		static int id_generator;

		int stationId;
		std::string name;
		std::string description;
		unsigned int serialNumber;
		unsigned int stock;
		static int m_widthField;

	public:
		Station();
		Station(std::string nameItem);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

		friend std::ostream& operator << (std::ostream& os, const Station& t);
	};


}
#endif // !SENECA_STATION_H

