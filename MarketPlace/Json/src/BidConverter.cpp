#include "BidConverter.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

std::string JsonConversion::BidAsJSON(const Bid& bid)
{
    web::json::value result = web::json::value::object();

    // result[U("bid_id")] = web::json::value::parse(JsonConversion::IdentifiableAsJSON(bid));
    result[U("bidder_id")] = web::json::value::string(bid.bidder().getId());
    result[U("bidding_price")] = web::json::value::number(bid.biddingPrice());
    result[U("quantity")] = web::json::value::number(bid.quantity());
    result[U("status")] = web::json::value::string(bid.status(StringOutput()));
    result[U("bid_date")] = web::json::value::string(bid.getTimeString());

    auto ret = result.serialize();
    return ret;
}

Bid JsonConversion::BidFromJSON(std::string json)
{
    Bid bid;
    auto bidJson = web::json::value::parse(json);

    try
    {
        // auto bidId = JsonConversion::IdentifiableFromJSON(bidJson.at("bid_id").serialize());
        // bid.setId(bidId.getId());
        User bidder;
        bidder.setId(bidJson.at("bidder_id").as_string());
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
