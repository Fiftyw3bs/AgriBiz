#ifndef ADD_ORDER_HPP_
#define ADD_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

class AddOrder : public IAction
{
private:
    Order _order;
public:
    AddOrder(const Order& order);
    bool perform();
    ~AddOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_ORDER_HPP_
