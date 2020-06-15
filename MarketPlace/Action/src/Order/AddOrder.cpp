#include "AddOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;


AddOrder::AddOrder(const Order& order, PGPoolPtr pgPool) : _order{order}, _pgPool{pgPool}
{
}
bool AddOrder::perform()
{
    auto orderDbo = OrderCRUD(this->_pgPool);
    this->_orderId = orderDbo.add(this->_order);
    return this->_orderId != 0;
}
OrderID AddOrder::result()
{
    return this->_orderId;
}