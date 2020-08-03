#include "OrderController.hpp"
#include "BidController.hpp"
#include "FarmProduceController.hpp"

using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::OrderAsJSON(const Order& order)
{
    web::json::value result = web::json::value::object();

    result[U("farm_produce")] = JsonConversion::FarmProduceAsJSON(order.farmProduce());
    result[U("order_id")] = web::json::value::number(order.getId());
    result[U("orderer_id")] = web::json::value::number(order.orderer().getId());
    Datable date;
    date.setDate(order.getTimeString());
    result[U("order_date")] = JsonConversion::DatableAsJSON(date);
    result[U("cost_per_kg")] = web::json::value::number(order.costPerKg());
    result[U("quantity")] = web::json::value::number(order.quantity());
    result[U("location_id")] = web::json::value::number(order.location().getId());
    result[U("harvest_date")] = JsonConversion::DatableAsJSON(order.harvestDate());
    result[U("description")] = web::json::value::string(order.description());
    result[U("date_completed")] = JsonConversion::DatableAsJSON(order.completionDate());
    result[U("order_type")] = web::json::value::string(order.type(StringOutput()));
    result[U("order_status")] = web::json::value::string(order.status(StringOutput()));

    auto bids = order.getSubscribers();

    if (!bids.empty())
    {
        result[U("bid_count")] = web::json::value::number(bids.size());
        auto bids_array = web::json::value::array();
        auto bid_count = 0;

        for (auto &&bidPtr : bids)
        {
            auto bid = bidPtr.lock();
            bids_array[bid_count++] = JsonConversion::BidAsJSON(*bid);
        }

        result[U("bids")] = bids_array;
    }

    return result;
}

Order JsonConversion::OrderFromJSON(const web::json::value& orderJson)
{
    Order order;
    
    try
    {
        order.setId(orderJson.at("order_id").as_number().to_uint32());
        User orderer;
        orderer.setId(orderJson.at("orderer_id").as_number().to_uint32());
        order.orderer(orderer);
        order.farmProduce(JsonConversion::FarmProduceFromJSON(orderJson.at("farm_produce")));
        order.description(orderJson.at("description").as_string());
        order.quantity(orderJson.at("quantity").as_number().to_double());
        order.costPerKg(orderJson.at("cost_per_kg").as_number().to_double());
        Location location;
        location.setId(orderJson.at("location_id").as_number().to_double());
        order.location(location);
        order.harvestDate(JsonConversion::DatableFromJSON(orderJson.at("harvest_date")));
        order.setDate(JsonConversion::DatableFromJSON(orderJson.at("order_date")).getTimeString());
        order.completionDate(JsonConversion::DatableFromJSON(orderJson.at("date_completed")));
        order.type(orderJson.at("order_type").as_string());
        order.status(orderJson.at("order_status").as_string());

        if (orderJson.at("bid_count").as_number().to_uint32() != 0)
        {
            for (size_t count = 0; count < orderJson.at("bid_count").size(); count++)
            {
                auto bidPtr = MakePointerOf<Bid>(JsonConversion::BidFromJSON(orderJson.at("bids").at(count)));
                order.addSubscriber(bidPtr);
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return order;
}