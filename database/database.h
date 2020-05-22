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

namespace db
{
	class database
	{
	 public:
		explicit database(const std::string& path);
		~database();
	 private:
		std::string basePath;

	};
}
#endif //_DATABASE_H_
