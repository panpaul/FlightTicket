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

db::database::database(const std::string& path)
{
	basePath = path;
}

db::database::~database()
{

}
