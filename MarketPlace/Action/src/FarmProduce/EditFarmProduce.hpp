#ifndef EDIT_ORDER_HPP_
#define EDIT_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "PGPool.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class EditOrder : public IAction
{
private:
    Order _order;
public:
    EditOrder(const Order& order);
    bool perform();
    ~EditOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //EDIT_ORDER_HPP_
