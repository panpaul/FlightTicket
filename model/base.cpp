/**
 * @file base.h
 * @brief interface the model
 * @details the integration of linearEngine and BTree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#include <string>
#include "base.h"

bool db::base::InsertFlight(db::Flight flight)
{
	return false;
}

bool db::base::InsertCustomer(db::Customer customer)
{
	return false;
}

bool db::base::InsertOrder(db::Order order)
{
	return false;
}

std::vector<db::Flight> db::base::QueryFlight(db::Flight flight)
{
	return {};
}

std::vector<db::Customer> db::base::QueryCustomer(db::Customer customer)
{
	return {};
}

std::vector<db::Order> db::base::QueryOrder(db::Order order)
{
	return {};
}

bool db::base::DeleteFlight(int flightId)
{
	return false;
}

bool db::base::DeleteCustomer(int customerId)
{
	return false;
}

bool db::base::DeleteOrder(int orderId)
{
	return false;
}

bool db::base::UpdateFlight(db::Flight flight)
{
	return false;
}

bool db::base::UpdateCustomer(db::Customer customer)
{
	return false;
}

bool db::base::UpdateOrder(db::Order order)
{
	return false;
}
