#include "DeleteOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

DeleteOrder::DeleteOrder(const Order& order, PGPoolPtr pgPool) : _order{order}, _pgPool{pgPool}
{
}

bool DeleteOrder::perform()
{
    auto OrderDbo = OrderCRUD(this->_pgPool);
    return OrderDbo.remove(this->_order);
}