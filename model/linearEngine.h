/**
 * @file linearEngine.h
 * @brief the basic storage engine used in model
 * @details file I/O, basic query with O(n)
 * @author Paul
 * @email panyuxuan@hotmail.com
 * @version 0.0.1
 * @date 2020-5-22
 */

#ifndef _LINEARENGINE_H_
#define _LINEARENGINE_H_

#include <string>
#include <vector>
#include "struct.h"
#include "base.h"

namespace db
{
	/**
	 * @brief the basic storage engine used in model
	 */
	class linearEngine : base
	{
	 public:
		explicit linearEngine(const std::string& path);
		~linearEngine();

		bool InsertFlight(struct Flight flight) override;
		bool InsertCustomer(struct Customer customer) override;
		bool InsertOrder(struct Order order) override;

		struct Flight QueryFlight(struct Flight flight) override;
		struct Customer QueryCustomer(struct Customer customer) override;
		struct Order QueryOrder(struct Order order) override;

		bool DeleteFlight(int flightId) override;
		bool DeleteCustomer(int customerId) override;
		bool DeleteOrder(int orderId) override;

		bool UpdateFlight(struct Flight flight) override;
		bool UpdateCustomer(struct Customer customer) override;
		bool UpdateOrder(struct Order order) override;

	 private:
		std::string basePath;
		std::vector<Flight> flightVec;
		std::vector<Customer> customerVec;
		std::vector<Order> orderVec;
		int flightIdCnt = 0, customerIdCnt = 0, orderIdCnt = 0;

		template<typename T>
		void saveVec(std::vector<T>& vec, int cnt, int size, const std::string& file);
		void loadFlightVec();
		void loadCustomerVec();
		void loadOrderVec();
	};
}
#endif //_LINEARENGINE_H_
