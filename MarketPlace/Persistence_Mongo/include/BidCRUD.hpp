/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\BidCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef BID_CRUD_HPP_
#define BID_CRUD_HPP_

#include "Bid.hpp"
#include "MongoPark.hpp"
#include "AgriBiz_JsonConversion.hpp"

namespace demystify
{

namespace AgriBiz
{

namespace persistence
{

using namespace persistence;

using BidCRUD = GenericCRUD<Bid, JsonConversion::BidAsJSON, JsonConversion::BidFromJSON>;

} // persistence

} // AgriBiz

} // namespace demystify

#endif // !BID_CRUD_HPP_
