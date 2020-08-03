#ifndef ADD_ORDER_HPP_
#define ADD_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "OrderCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{
namespace action {

using namespace persistence;

class AddOrder : public IAction
{
private:
    Order _order;
    PGPoolPtr _pgPool;
    OrderID _orderId;
public:
    AddOrder(const Order& Order, PGPoolPtr pgPool);
    bool perform();
    OrderID result();
    ~AddOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //ADD_ORDER_HPP_
