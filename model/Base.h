/**
 * @file base.h
 * @brief interface the model
 * @details the integration of linearEngine and BTree
 * @author Paul
 * @version 0.0.2
 * @date 2020-5-22
 */

#ifndef _BASE_H_
#define _BASE_H_

#include <vector>
#include "model.h"

namespace db
{
	/**
	 * @brief interface the model
	 */
	class Base
	{
	 protected:
		virtual ~Base();

		virtual int InsertFlight(struct Flight flight);
		virtual int InsertCustomer(struct Customer customer);
		virtual int InsertOrder(struct Order order);

		virtual std::vector<Flight> QueryFlight(struct Flight flight);
		virtual std::vector<Customer> QueryCustomer(struct Customer customer);
		virtual std::vector<Order> QueryOrder(struct Order order);

		virtual bool DeleteFlight(int flightId);
		virtual bool DeleteCustomer(int customerId);
		virtual bool DeleteOrder(int orderId);

		virtual bool UpdateFlight(struct Flight flight);
		virtual bool UpdateCustomer(struct Customer customer);
		virtual bool UpdateOrder(struct Order order);
	};
}
#endif //_BASE_H_
