#ifndef DELETE_ORDER_HPP_
#define DELETE_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "OrderCRUD.hpp"

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
    PGPoolPtr _pgPool;
public:
    DeleteOrder(const Order& order, PGPoolPtr pgPool);
    bool perform();
    ~DeleteOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //DELETE_ORDER_HPP_
