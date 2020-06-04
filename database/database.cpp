/**
 * @file database.h
 * @brief interface the database
 * @details the integration of linearEngine and BTree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#include "database.h"

bool db::database::InsertFlight(db::Flight flight)
{
	return false;
}

bool db::database::InsertCustomer(db::Customer customer)
{
	return false;
}

bool db::database::InsertOrder(db::Order order)
{
	return false;
}

db::Flight db::database::QueryFlight(db::Flight flight)
{
	return {};
}

db::Customer db::database::QueryCustomer(db::Customer customer)
{
	return {};
}

db::Order db::database::QueryOrder(db::Order order)
{
	return {};
}

bool db::database::DeleteFlight(int flightId)
{
	return false;
}

bool db::database::DeleteCustomer(int customerId)
{
	return false;
}

bool db::database::DeleteOrder(int orderId)
{
	return false;
}

bool db::database::UpdateFlight(db::Flight flight)
{
	return false;
}

bool db::database::UpdateCustomer(db::Customer customer)
{
	return false;
}

bool db::database::UpdateOrder(db::Order order)
{
	return false;
}
