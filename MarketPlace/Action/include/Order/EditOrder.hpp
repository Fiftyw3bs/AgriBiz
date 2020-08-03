#ifndef EDIT_ORDER_HPP_
#define EDIT_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "OrderCRUD.hpp"

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
    PGPoolPtr _pgPool;
public:
    EditOrder(const Order& order, PGPoolPtr pgPool);
    bool perform();
    ~EditOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //EDIT_ORDER_HPP_
