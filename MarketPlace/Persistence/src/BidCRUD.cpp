#include "BidCRUD.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace AgriBiz::persistence;

BidCRUD::BidCRUD(PGPoolPtr& pgPool) : GenericCRUD(BidCRUD::crudStatements, pgPool)
{
}

BidID BidCRUD::add(const Bid& bid)
{
    BidID bidId = 0;

    auto mm = this->performDBOperation(
        "BID_CREATE",
        bid.biddingPrice(),
        bid.quantity(),
        bid.status(StringOutput()),
        bid.getTimeString(),
        bid.bidder().getId()
    );
    
    if (!mm[0]["bid_id"].is_null())
    {
        bidId = mm[0]["bid_id"].as<BidID>();
    }

    return bidId;
}

bool BidCRUD::remove(const Bid& bid)
{
    return this->performDBOperation(
        "BID_REMOVE_ONE_BY_ID",
        bid.getId()
    ).empty();
}

bool BidCRUD::update(const Bid& bid)
{
    return this->performDBOperation(
        "BID_MODIFY",
        bid.biddingPrice(),
        bid.quantity(),
        bid.status(StringOutput()),
        bid.getId()
    ).empty();
}

Bid BidCRUD::fetch(const Bid& bid)
{
    auto retVal = this->performDBOperation(
        "BID_FETCH_ONE_BY_BID_ID",
        bid.getId()
    );

    return this->processFetched(retVal)[0];
}

VectorOf<Bid> BidCRUD::processFetched(const result res)
{

    VectorOf<Bid> tmpBids;
    Bid tmpBid;

    if (!res.empty() && res.size() > 0)
    {
        for (auto row : res)
        {
            tmpBid.setId(row["bid_id"].as<uint32_t>());
            tmpBid.biddingPrice(row["bidding_price"].as<float>());
            tmpBid.quantity(row["quantity"].as<float>());
            User tUser;
            tUser.setId(row["bidder_id"].as<UserID>());
            tmpBid.bidder(tUser);
            tmpBid.status(row["bid_status"].as<std::string>());
            tmpBids.push_back(tmpBid);
        }
    }
    else
    {
        tmpBids.push_back(tmpBid);
    }
    

    return tmpBids;
}

DBStatements BidCRUD::crudStatements{
    {"BID_FETCH_ONE_BY_BID_ID", 
        "SELECT \
            bid_id, \
            bidding_price, \
            bidder_id, \
            quantity, \
            bid_status, \
            bid_date \
         FROM Bid \
         WHERE bid_id = $1"
    },
    {"BID_CREATE", "INSERT INTO Bid (bid_id, bidding_price, quantity, bid_status, bid_date, bidder_id) VALUES (DEFAULT, $1, $2, $3, $4, $5) RETURNING bid_id"},
    {"BID_REMOVE_ONE_BY_ID", "DELETE FROM Bid WHERE bid_id = $1"},
    {"BID_MODIFY", "UPDATE Bid SET bidding_price=$1, quantity=$2, bid_status=$3 WHERE bid_id=$4"}
};