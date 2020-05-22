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
	class linearEngine
	{
	 public:
		explicit linearEngine(const std::string& path);
		~linearEngine();

		template<typename T>
		void saveVec(std::vector<T>& vec, int size, const std::string& file);
		void loadFlightVec();
		void loadCustomerVec();
		void loadOrderVec();

	 private:
		std::string basePath;
		std::vector<Flight> flightVec;
		std::vector<Customer> customerVec;
		std::vector<Order> orderVec;
	};
}
#endif //_LINEARENGINE_H_
