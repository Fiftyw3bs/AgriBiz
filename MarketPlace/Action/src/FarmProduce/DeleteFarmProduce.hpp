#ifndef DELETE_ORDER_HPP_
#define DELETE_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "PGPool.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class DeleteOrder : public IAction
{
private:
    Order _order;
public:
    DeleteOrder(const Order& order);
    bool perform();
    ~DeleteOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //DELETE_ORDER_HPP_
