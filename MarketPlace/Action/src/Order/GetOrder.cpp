#include "GetOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

GetOrder::GetOrder(const Order& order, PGPoolPtr pgPool) : _order{order}, _pgPool{pgPool}
{
}

bool GetOrder::perform()
{
    auto OrderDbo = OrderCRUD(this->_pgPool);
    this->_order = OrderDbo.fetch(this->_order);
    return this->_order.getId() != 0;
}

Order GetOrder::result()
{
    return this->_order;
}