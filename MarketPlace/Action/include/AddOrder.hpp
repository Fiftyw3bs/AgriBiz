#ifndef ADD_ORDER_HPP_
#define ADD_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "PGPool.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

class AddOrder : public IAction
{
private:
    Order _order;
    PGPoolPtr _pgPool;
public:
    AddOrder(const Order& order, PGPoolPtr pgPool);
    bool perform();
    ~AddOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_ORDER_HPP_
