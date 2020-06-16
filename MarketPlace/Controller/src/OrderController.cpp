#include "OrderController.hpp"

using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::OrderAsJSON(const Order& order)
{
    web::json::value result = web::json::value::object();
    result[U("OrderId")] = web::json::value::number(order.getId());
    result[U("OrderToken")] = web::json::value::number(order.getOrderToken());
    result[U("assigned")] = web::json::value::boolean(order.isAssigned());
    return result;
}

Order JsonConversion::OrderFromJSON(const web::json::value& orderJson)
{
    Order Order;
    order.setOrderToken(OrderJson.at("OrderToken").as_number().to_uint32());
    if (OrderJson.has_field("assigned"))
    {
        if (OrderJson.at("assigned").as_bool())
        {
            order.toggleAssignedState();
        }
    }
    if (OrderJson.has_field("OrderId"))
    {
        order.setId(OrderJson.at("OrderId").as_number().to_uint32());
    }
    return Order;
}