
#include "Workstation.h"
#include "CustomerOrder.h"

using namespace std;

namespace seneca {

	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_incomplete;
	std::deque<CustomerOrder> g_completed;

	Workstation::Workstation(const std::string& name) : Station(name), m_pNextStation(nullptr) {}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}

	}

	bool Workstation::attemptToMoveOrder() {
		if (!m_orders.empty()) {
			if (m_orders.front().isOrderFilled()) {
				if (m_pNextStation) {
				}
				else {
					g_completed.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
				return true;
			}
			else {
				if (m_pNextStation) {
					cout << "next station name: " << m_pNextStation->getItemName() << endl;
				}
				else {
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
				return true;
			}
		}
		return false;

	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName();
		if (m_pNextStation)
			os << " --> " << m_pNextStation->getItemName();
		else
			os << " --> End of Line";
		os << "\n";
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

	Workstation::Workstation(const Workstation& ws) : Station(ws), m_orders(ws.m_orders)
	{
		m_pNextStation = ws.m_pNextStation;
	}

	Workstation& Workstation::operator=(const Workstation& ws)
	{
		

		return *this;
	}

	Workstation::Workstation(Workstation&& ws) noexcept : Station(std::move(ws)), m_orders(std::move(ws.m_orders)), m_pNextStation(ws.m_pNextStation)
	{
	
	}

	Workstation& Workstation::operator=(Workstation&& ws) noexcept {
		if (this != &ws) {
			Station::operator=(std::move(ws));
			m_orders = std::move(ws.m_orders);
			m_pNextStation = ws.m_pNextStation;
			ws.m_pNextStation = nullptr;
		}
		return *this;
	}

	Workstation::~Workstation()
	{
	

	}
}