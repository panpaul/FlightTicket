/**
 * @file base.h
 * @brief interface the model
 * @details the integration of linearEngine and BTree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.2
 * @date 2020-5-22
 */

#include <string>
#include "Base.h"

bool db::Base::InsertFlight(db::Flight flight)
{
	return false;
}

bool db::Base::InsertCustomer(db::Customer customer)
{
	return false;
}

bool db::Base::InsertOrder(db::Order order)
{
	return false;
}

std::vector<db::Flight> db::Base::QueryFlight(db::Flight flight)
{
	return {};
}

std::vector<db::Customer> db::Base::QueryCustomer(db::Customer customer)
{
	return {};
}

std::vector<db::Order> db::Base::QueryOrder(db::Order order)
{
	return {};
}

bool db::Base::DeleteFlight(int flightId)
{
	return false;
}

bool db::Base::DeleteCustomer(int customerId)
{
	return false;
}

bool db::Base::DeleteOrder(int orderId)
{
	return false;
}

bool db::Base::UpdateFlight(db::Flight flight)
{
	return false;
}

bool db::Base::UpdateCustomer(db::Customer customer)
{
	return false;
}

bool db::Base::UpdateOrder(db::Order order)
{
	return false;
}
