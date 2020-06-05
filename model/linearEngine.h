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

#include <vector>
#include "model.h"
#include "Base.h"

namespace db
{
	/**
	 * @brief the basic storage engine used in model
	 */
	class linearEngine : Base
	{
	 public:
		explicit linearEngine(const std::string& path);
		~linearEngine();

		int InsertFlight(struct Flight flight) override;
		int InsertCustomer(struct Customer customer) override;
		int InsertOrder(struct Order order) override;

		std::vector<Flight> QueryFlight(struct Flight flight) override;
		std::vector<Customer> QueryCustomer(struct Customer customer) override;
		std::vector<Order> QueryOrder(struct Order order) override;

		bool DeleteFlight(int flightId) override;
		bool DeleteCustomer(int customerId) override;
		bool DeleteOrder(int orderId) override;

		bool UpdateFlight(struct Flight flight) override;
		bool UpdateCustomer(struct Customer customer) override;
		bool UpdateOrder(struct Order order) override;

	 private:
		std::string BasePath;
		std::vector<Flight> FlightVec;
		std::vector<Customer> CustomerVec;
		std::vector<Order> OrderVec;
		int FlightIdCnt = 0, CustomerIdCnt = 0, OrderIdCnt = 0;

		template<typename T>
		void SaveVec(std::vector<T>& vec, int cnt, int size, const std::string& file);
		void LoadFlightVec();
		void LoadCustomerVec();
		void LoadOrderVec();

		template<typename T, typename Cmp>
		std::vector<T> FindMatch(std::vector<T>& vec, Cmp cmp);
	};
}
#endif //_LINEARENGINE_H_
