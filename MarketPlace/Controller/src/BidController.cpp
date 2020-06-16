#include "BidController.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::BidAsJSON(const Bid& bid)
{
    web::json::value result = web::json::value::object();
    result[U("bidId")] = web::json::value::number(bid.getId());
    result[U("biddingPrice")] = web::json::value::number(bid.biddingPrice());
    result[U("quantity")] = web::json::value::number(bid.quantity());
    result[U("status")] = web::json::value::boolean(bid.status());
    result[U("bidDate")] = web::json::value::string(bid.getTimeString());
    return result;
}

Bid JsonConversion::BidFromJSON(const web::json::value& bidJson)
{
    Bid bid;

    try
    {
        bid.setId(bidJson.at("bidId").as_number().to_uint32());
        bid.setDate(bidJson.at("bidDate").as_string());
        bid.biddingPrice(bidJson.at("biddingPrice").as_number().to_uint32());
        bid.quantity(bidJson.at("bidId").as_number().to_uint32());
        bid.status(bidJson.at("bidId").as_number().to_uint32());
    } catch(web::json::exception e)
    {
        // Error Here <<
    }
    
    return bid;
}