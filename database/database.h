/**
 * @file database.h
 * @brief interface the database
 * @details the integration of linearEngine and BTree
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <string>
#include "struct.h"

namespace db
{
	/**
	 * @brief interface the database
	 */
	class database
	{
	 protected:
		virtual bool InsertFlight(struct Flight flight);
		virtual bool InsertCustomer(struct Customer customer);
		virtual bool InsertOrder(struct Order order);

		virtual struct Flight QueryFlight(struct Flight flight);
		virtual struct Customer QueryCustomer(struct Customer customer);
		virtual struct Order QueryOrder(struct Order order);

		virtual bool DeleteFlight(int flightId);
		virtual bool DeleteCustomer(int customerId);
		virtual bool DeleteOrder(int orderId);

		virtual bool UpdateFlight(struct Flight flight);
		virtual bool UpdateCustomer(struct Customer customer);
		virtual bool UpdateOrder(struct Order order);
	};
}
#endif //_DATABASE_H_
