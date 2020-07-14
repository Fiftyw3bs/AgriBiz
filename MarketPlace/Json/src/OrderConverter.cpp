#include "OrderConverter.hpp"
#include "BidConverter.hpp"
#include "FarmProduceConverter.hpp"

using namespace demystify;
using namespace personal;
using namespace AgriBiz;

std::string JsonConversion::OrderAsJSON(const Order& order)
{

    web::json::value result = web::json::value::object();

    if (!order.getId().empty())
    {
        result = web::json::value::parse(JsonConversion::IdentifiableAsJSON(order));
    }

    result[U("farm_produce")] = web::json::value::parse(JsonConversion::FarmProduceAsJSON(order.farmProduce()));
    // result[U("order_id")] = web::json::value::string(order.getId());
    result[U("orderer_id")] = web::json::value::string(order.orderer().getId());
    Datable date;
    date.setDate(order.getTimeString());
    result[U("order_date")] = web::json::value::parse(JsonConversion::DatableAsJSON(date));
    result[U("cost_per_kg")] = web::json::value::number(order.costPerKg());
    result[U("quantity")] = web::json::value::number(order.quantity());
    // result[U("location_id")] = web::json::value::string(order.location().getId());
    result[U("harvest_date")] = web::json::value::parse(JsonConversion::DatableAsJSON(order.harvestDate()));
    result[U("description")] = web::json::value::string(order.description());
    result[U("date_completed")] = web::json::value::parse(JsonConversion::DatableAsJSON(order.completionDate()));
    result[U("order_type")] = web::json::value::string(order.type(StringOutput()));
    result[U("order_status")] = web::json::value::string(order.status(StringOutput()));

    auto bids = order.getSubscribers();

    if (!bids.empty())
    {
        auto bids_array = web::json::value::array();
        auto bid_count = 0;

        for (auto &&bidPtr : bids)
        {
            auto bid = bidPtr.lock();
            bids_array[bid_count++] = web::json::value::parse(JsonConversion::BidAsJSON(*bid));
        }

        result[U("bids")] = bids_array;
    } else
    {
        result[U("bids")] = web::json::value::array();
    }


    return result.serialize();
}

Order JsonConversion::OrderFromJSON(std::string json)
{
    Order order;
    auto orderJson = web::json::value::parse(json);

    try
    {
        order.setId(JsonConversion::IdentifiableFromJSON(json).getId());
        User orderer;
        orderer.setId(orderJson.at("orderer_id").as_string());
        order.orderer(orderer);
        order.farmProduce(JsonConversion::FarmProduceFromJSON(orderJson.at("farm_produce").serialize()));
        order.description(orderJson.at("description").as_string());
        order.quantity(orderJson.at("quantity").as_number().to_double());
        order.costPerKg(orderJson.at("cost_per_kg").as_number().to_double());
        // Location location;
        // location.setId(orderJson.at("location_id").as_number().to_double());
        // order.location(location);
        order.harvestDate(JsonConversion::DatableFromJSON(orderJson.at("harvest_date").serialize()));
        order.setDate(JsonConversion::DatableFromJSON(orderJson.at("order_date").serialize()).getTimeString());
        order.completionDate(JsonConversion::DatableFromJSON(orderJson.at("date_completed").serialize()));
        order.type(orderJson.at("order_type").as_string());
        order.status(orderJson.at("order_status").as_string());

        if (orderJson.at("bids").size() != 0)
        {
            for (size_t count = 0; count < orderJson.at("bids").size(); count++)
            {
                auto bidPtr = MakePointerOf<Bid>(JsonConversion::BidFromJSON(orderJson.at("bids")[count].serialize()));
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
