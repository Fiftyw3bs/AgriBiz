#ifndef BID_ORDER_HPP_
#define BID_ORDER_HPP_

#include "Order.hpp"
#include "Bid.hpp"
#include "PGPool.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class BidOrder : public IAction
{
private:
    const Bid& _bid;
    Order _order;
public:
    BidOrder(const Bid& bid, Order& order, PGPoolPtr pgPool);
    bool perform();
    ~BidOrder();
};


} // action

} // namespace AgriBiz

} // namespace demystify


#endif //BID_ORDER_HPP_
