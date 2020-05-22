/**
 * @file linearEngine.h
 * @brief the basic storage engine used in database
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

namespace db
{
	/**
	 * @brief the basic storage engine used in database
	 */
	class linearEngine
	{
	 public:
		explicit linearEngine(const std::string& path);
		~linearEngine();

		template<typename T>
		void saveVec(std::vector<T>& vec, int cnt, int size, const std::string& file);
		void loadFlightVec();
		void loadCustomerVec();
		void loadOrderVec();

		bool insertFlight(struct Flight flight);
		bool insertCustomer(struct Customer customer);
		bool insertOrder(struct Order order);

		struct Flight queryFlight(struct Flight flight);
		struct Customer queryCustomer(struct Customer customerCmp);
		struct Order queryOrder(struct Order order);

	 private:
		std::string basePath;
		std::vector<Flight> flightVec;
		std::vector<Customer> customerVec;
		std::vector<Order> orderVec;
		int flightIdCnt = 0, customerIdCnt = 0, orderIdCnt = 0;
	};
}
#endif //_LINEARENGINE_H_
