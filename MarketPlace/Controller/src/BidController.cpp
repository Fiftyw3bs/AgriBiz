#include "BidController.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::BidAsJSON(const Bid& bid)
{
    web::json::value result = web::json::value::object();
    result[U("bid_id")] = web::json::value::number(bid.getId());
    result[U("bidder_id")] = web::json::value::number(bid.bidder().getId());
    result[U("bidding_price")] = web::json::value::number(bid.biddingPrice());
    result[U("quantity")] = web::json::value::number(bid.quantity());
    result[U("status")] = web::json::value::string(bid.status(StringOutput()));
    result[U("bid_date")] = web::json::value::string(bid.getTimeString());
    return result;
}

Bid JsonConversion::BidFromJSON(const web::json::value& bidJson)
{
    Bid bid;

    try
    {
        bid.setId(bidJson.at("bid_id").as_number().to_uint32());
        User bidder;
        bidder.setId(bidJson.at("bid_id").as_number().to_uint32());
        bid.bidder(bidder);
        bid.setDate(bidJson.at("bid_date").as_string());
        bid.biddingPrice(bidJson.at("bidding_price").as_number().to_double());
        bid.quantity(bidJson.at("quantity").as_number().to_double());
        bid.status(bidJson.at("status").as_string());
    } catch(web::json::json_exception e)
    {
        // Error Here <<
    }
    
    return bid;
}