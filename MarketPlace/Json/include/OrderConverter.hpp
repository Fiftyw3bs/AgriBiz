#ifndef ORDER_CONTROLLER_HPP_
#define ORDER_CONTROLLER_HPP_

#include "JsonConversion.hpp"
#include "Order.hpp"

using namespace demystify;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    std::string OrderAsJSON(const Order& order);
    Order OrderFromJSON(std::string orderJson);
} // namespace JsonConversion


#endif //ORDER_CONTROLLER_HPP_
