#include "LineManager.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace seneca {
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) : m_cntCustomerOrder(0), m_firstStation(nullptr) {
		Utilities util;
		Utilities::setDelimiter('|');

		ifstream infile(file);
		if (!infile) {
			cerr << "Error: Unable to open file: " << file << endl;
			return;
		}



		string record;
		while (!infile.eof()) {
			size_t position = 0u;
			bool more = true;
			getline(infile, record);
			string stationName = util.extractToken(record, position, more);
			for (auto& station : stations) {
				if (station->getItemName() == stationName)
					m_firstStation = station;
			}
			string nextStationName = util.extractToken(record, position, more);
			if (nextStationName.empty()) {
				m_activeLine.push_back(m_firstStation);
				continue;
			}
			for (auto& station : stations) {
				if (station->getItemName() == nextStationName)
					m_firstStation->setNextStation(station);
			}
			m_activeLine.push_back(m_firstStation);
		}
		infile.close();
	}

	void LineManager::reorderStations()
	{
		Workstation* temp = nullptr;
		bool flag = true;
		int pos = m_activeLine.size();
		for (unsigned i = 0; i < m_activeLine.size(); i++) {
			if (m_activeLine[i]->getNextStation() == nullptr) {
				temp = m_activeLine[pos - 1];
				m_activeLine[pos - 1] = m_activeLine[i];
				m_activeLine[i] = temp;
			}
		}
		if (temp != nullptr) {
			string stationName = temp->getItemName();
			pos = pos - 2;
			while (flag) {
				flag = swapNextLine(pos, stationName);
			}
		}
	}

	bool LineManager::swapNextLine(int& pos, string& name) {
		Workstation* temp;
		for (unsigned i = 0; i < m_activeLine.size(); i++) {
			if (m_activeLine[i]->getNextStation() != nullptr && name == m_activeLine[i]->getNextStation()->getItemName()) {
				temp = m_activeLine[pos];
				m_activeLine[pos] = m_activeLine[i];
				name = m_activeLine[i]->getItemName();
				m_activeLine[i] = temp;
				pos--;
				return true;
			}
		}
		return false;
	}

	bool LineManager::run(::ostream& os)
	{
		static size_t iterationCount;
		++iterationCount;

		os << "Line Manager Iteration: " << iterationCount << ::endl;
		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}
		if (m_firstStation->getNextStation()) {
			cout << m_firstStation->getNextStation()->getItemName() << endl;
			m_firstStation = m_firstStation->getNextStation();
		}

	

		for (size_t i = 0; i < m_activeLine.size(); ++i) {
			m_activeLine[i]->fill(os);
		}
		for (size_t i = 0; i < m_activeLine.size(); ++i) {
			m_activeLine[i]->attemptToMoveOrder();
		}
		return g_pending.empty();
	}

	void LineManager::display(ostream& os) const
	{
		for (size_t i = 0; i < m_activeLine.size(); ++i) {
			m_activeLine[i]->display(os);
		}
	}

}