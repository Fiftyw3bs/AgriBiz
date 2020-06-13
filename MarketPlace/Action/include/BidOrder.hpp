#ifndef BID_ORDER_HPP_
#define BID_ORDER_HPP_

#include "Order.hpp"
#include "Bid.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

class BidOrder : public IAction
{
private:
    const Bid& _bid;
    Order& _order;
public:
    BidOrder(const Bid& bid, Order& order);
    bool perform();
    ~BidOrder();
};


} // action

} // namespace AgriBiz

} // namespace demystify


#endif //BID_ORDER_HPP_
