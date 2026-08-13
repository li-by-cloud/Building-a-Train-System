#include <iostream>
#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <string>

using namespace std;

namespace seneca {
	CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {
		m_name = "test";
	}

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(string& record)
	{
		Utilities util;
		size_t next_pos = 0;
		size_t item_starting_pos = 0;
		bool more = true;
		m_cntItem = 0;

		m_name.assign(util.extractToken(record, next_pos, more));
		m_product = util.extractToken(record, next_pos, more);

		item_starting_pos = next_pos;

		while (more) {
			string item = util.extractToken(record, next_pos, more);
			if (!item.empty())
				m_cntItem++;
		}

		m_lstItem = new Item * [m_cntItem];
		more = true;
		next_pos = item_starting_pos;
		size_t idex = 0;

		while (more) {
			std::string item = util.extractToken(record, next_pos, more);
			if (!item.empty()) {
				m_lstItem[idex] = new Item(item);
				if (m_widthField < item.length())
					m_widthField = item.length();
				idex++;
			}
		}


	}

	CustomerOrder::CustomerOrder(const CustomerOrder& other) : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr)
	{

		throw std::logic_error("Copy constructor is not allowed for CustomerOrder");
	}


	CustomerOrder::CustomerOrder(const CustomerOrder&& other) noexcept : m_cntItem(0), m_lstItem(nullptr)
	{
		this->m_name = move(other.m_name);
		this->m_product = move(other.m_product);
		this->m_cntItem = move(other.m_cntItem);
		this->m_lstItem = move(other.m_lstItem);
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i]->m_serialNumber = move(other.m_lstItem[i])->m_serialNumber;
			m_lstItem[i]->m_itemName = move(other.m_lstItem[i])->m_itemName;
			m_lstItem[i]->m_isFilled = move(other.m_lstItem[i])->m_isFilled;
		}
	}

	CustomerOrder& CustomerOrder::operator=(const CustomerOrder&& other) noexcept
	{
		if (this != &other) {
			m_name = move(other.m_name);
			m_product = move(other.m_product);
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
	}

	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled)
				return false;
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
				return false;
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
				}
				os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName
				<< " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}
	}
}