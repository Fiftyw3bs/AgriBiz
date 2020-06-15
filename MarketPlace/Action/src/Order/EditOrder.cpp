#include "EditOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

EditOrder::EditOrder(const Order& order, PGPoolPtr pgPool) : _order{order}, _pgPool{pgPool}
{
}

bool EditOrder::perform()
{
    auto OrderDbo = OrderCRUD(this->_pgPool);
    return OrderDbo.update(this->_order);
}