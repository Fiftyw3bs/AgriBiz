#ifndef GET_ORDER_HPP_
#define GET_ORDER_HPP_

#include "IAction.hpp"
#include "Order.hpp"
#include "OrderCRUD.hpp"

namespace demystify
{
namespace AgriBiz
{

namespace action {

using namespace persistence;

class GetOrder : public IAction
{
private:
    VectorOf<Order> _order;
    PGPoolPtr _pgPool;
    Offset _offset;
    Limit _limit;
public:
    GetOrder(const Order& order, PGPoolPtr pgPool, Offset offset = 0, Limit limit = 1);
    bool perform();
    Order result();
    VectorOf<Order> result(Multiple);
    ~GetOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //GET_ORDER_HPP_
