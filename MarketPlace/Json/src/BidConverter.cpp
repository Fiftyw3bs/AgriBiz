#include "BidConverter.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

std::string JsonConversion::BidAsJSON(const Bid& bid)
{
    web::json::value result = web::json::value::object();

    result[U("bid_id")] = web::json::value::parse(JsonConversion::IdentifiableAsJSON(bid));
    result[U("bidder_id")] = web::json::value::parse(JsonConversion::IdentifiableAsJSON(bid.bidder()));
    result[U("bidding_price")] = web::json::value::number(bid.biddingPrice());
    result[U("quantity")] = web::json::value::number(bid.quantity());
    result[U("status")] = web::json::value::string(bid.status(StringOutput()));
    result[U("bid_date")] = web::json::value::string(bid.getTimeString());
    
    return result.serialize();
}

Bid JsonConversion::BidFromJSON(std::string json)
{
    Bid bid;
    auto bidJson = web::json::value::parse(json);

    try
    {
        auto bidId = JsonConversion::IdentifiableFromJSON(bidJson.at("bid_id").serialize());
        bid.setId(bidId.getId());

        auto bidderId = JsonConversion::IdentifiableFromJSON(bidJson.at("bidder_id").serialize());
        User bidder;
        
        bidder.setId(bidderId.getId());
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