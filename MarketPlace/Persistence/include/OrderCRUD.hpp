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

namespace demystify
{
    
namespace AgriBiz
{

namespace persistence 
{
   
using namespace personal;
using OrderToken = uint32_t;
using OrderID = uint32_t;
using Limit = uint32_t;
using Offset = uint32_t;
using MinimumQuantity = uint32_t;
using MaximumQuantity = uint32_t;

class OrderCRUD : public GenericCRUD
{
private:
    static DBStatements crudStatements;
    static VectorOf<Order> processFetched(const result& res);

public:
    OrderCRUD(PGPoolPtr& pgPool);
    OrderID add(const Order& Order);
    bool remove(const Order& OrderId);
    bool update(const Order& Order);
    bool assignBid(const Bid& bid, const Order& Order);
    Order fetch(const Order& Order);
    // VectorOf<Order> fetch(const OrderStatus& status, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const Order& order, const Offset& offset, const Limit& limit);
    // Order fetch(const Order& order);
    // VectorOf<Order> fetch(const OrderType& orderType, const Offset& offset, const Limit& limit);
    VectorOf<Order> fetch(const User& Orderer, const Offset& offset, const Limit& limit);
    VectorOf<Order> fetch(const Datable& startDate, const Datable& endDate, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const Location& location, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const FarmProduce& location, const Offset& offset, const Limit& limit);
    // VectorOf<Order> fetch(const MinimumQuantity& minQuantity, const MaximumQuantity& maxQuantity, const Offset& offset, const Limit& limit);
};
 
} // AntiGhostWorker

} // persistence
    
} // namespace demystify

#endif // !ORDER_CRUD_HPP_
