/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\OrderCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef ORDER_CRUD_HPP_
#define ORDER_CRUD_HPP_

#include "Order.hpp"
#include "Bid.hpp"
#include "User.hpp"
#include "GenericCRUD.hpp"
#include "AgriBiz_JsonConversion.hpp"

namespace demystify
{
    
namespace AgriBiz
{

namespace persistence 
{
   
class OrderCRUD : public GenericCRUD<Order, JsonConversion::OrderAsJSON, JsonConversion::OrderFromJSON>
{
public:
    OrderCRUD(mongocxx::client& client_, const MongoDBInfo dbInfo);
    bool assignBid(const Bid& bid, const Order& Order);
    // VectorOf<Order> fetch(const std::string& orderStatus, const Offset& offset, const Limit& limit);
    // // VectorOf<Order> fetch(const Order& order, const Offset& offset, const Limit& limit);
    // // Order fetch(const Order& order);
    // // VectorOf<Order> fetch(const OrderType& orderType, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const User& Orderer, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const Datable& startDate, const Datable& endDate, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const Location& location, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const FarmProduce& location, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const MinimumQuantity& minQuantity, const MaximumQuantity& maxQuantity, const Offset& offset, const Limit& limit);
};
 
} // AntiGhostWorker

} // persistence
    
} // namespace demystify

#endif // !ORDER_CRUD_HPP_
