#include "GetOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

GetOrder::GetOrder(const Order& order, PGPoolPtr pgPool, Offset offset, Limit limit) 
    : _pgPool{pgPool}, _offset{offset}, _limit{limit}
{
    this->_order.push_back(order);
}

bool GetOrder::perform()
{
    auto OrderDbo = OrderCRUD(this->_pgPool);
    if (this->_order[0].getId() != 0)
    {
        this->_order = OrderDbo.fetch(this->_order[0].orderer(), this->_offset, this->_limit);
    } else
    {
        this->_order = OrderDbo.fetch(this->_order[0].orderer(), this->_offset, this->_limit);
    }
    
    
    return !this->_order.empty();
}

Order GetOrder::result()
{
    return this->_order[0];
}

VectorOf<Order> GetOrder::result(Multiple)
{
    return this->_order;
}