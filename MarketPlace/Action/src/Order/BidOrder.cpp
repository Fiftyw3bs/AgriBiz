#include "BidOrder.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace action;

BidOrder::BidOrder(const Bid& bid, Order& order, PGPoolPtr pgPool) : _bid{bid}, _order{order}, _pgPool{pgPool}
{
}
bool BidOrder::perform()
{
    auto orderDbo = OrderCRUD(this->_pgPool);
    return orderDbo.assignBid(this->_bid, this->_order);
}