#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
#include "Utilities.h"
using namespace std;
namespace seneca {

	class Station {
		int idStation;
		string name;
		string description;
		unsigned serialNumber;
		unsigned stock;
		int m_widthField = 0;
        int id_generator = 0;
	public:
		 
		Station(string nameItem, unsigned serialNum, unsigned qunatityStock, string desc);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
	 
    
}
#endif // !SENECA_STATION_H

