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
    Order _order;
    PGPoolPtr _pgPool;
public:
    GetOrder(const Order& order, PGPoolPtr pgPool);
    bool perform();
    Order result();
    ~GetOrder();
};

} // action

} // namespace AgriBiz

} // namespace demystify


#endif //GET_ORDER_HPP_
