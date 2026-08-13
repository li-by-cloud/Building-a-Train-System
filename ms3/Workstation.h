#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"
#include <string>
#include <queue>
#include <algorithm>
#include <deque>
using namespace std;
namespace seneca {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;
	
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation(const std::string& name);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
		Workstation(const Workstation& ws);
		Workstation& operator=(const Workstation& ws);
		Workstation(Workstation&& ws) noexcept;
		Workstation& operator=(Workstation&& ws) noexcept;
		~Workstation();
	};

	

}
#endif // !SENECA_WORKSTATION_H 

