#ifndef ORDER_CONTROLLER_HPP_
#define ORDER_CONTROLLER_HPP_

#include "AgriBiz_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "JsonConversion.hpp"
#include "Order.hpp"

using namespace demystify;

using OrderController = demystify::AgriBiz::controller::Controller<OrderCRUD>;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    web::json::value OrderAsJSON(const Order& order);
    Order OrderFromJSON(const web::json::value& orderJson);
} // namespace JsonConversion


#endif //ORDER_CONTROLLER_HPP_
