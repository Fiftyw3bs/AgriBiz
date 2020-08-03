#include <iostream>
#include "gtest/gtest.h"

#include "AgriBiz_Persistence.hpp"

namespace demystify
{
namespace unittest
{

using namespace AgriBiz;
using namespace AgriBiz::persistence;

PGPoolPtr myPool = std::make_shared<PGPool>(DBInfo());
personal::User tUser("Username");
Bid tBid;
BidCRUD tBidCRUD(myPool);
UserCRUD tUserCRUD(myPool);
VectorOf<Bid> dbBids;

TEST(AgriBiz_Persistence, TestAddBid)
{
    // User tUser = tUserCRUD.fetchOne(1);
    User tUser;
    tUser.setId(1);
    tBid.status(BidStatus::PENDING);
    tBid.quantity(123.4);
    tBid.bidder(tUser);
    tBid.biddingPrice(4213);
    auto bidId = tBidCRUD.add(tBid);
    tBid.setId(bidId);
    ASSERT_TRUE(bidId != 0);
}

TEST(AgriBiz_Persistence, TestFetchBid)
{
    auto bid = tBidCRUD.fetch(tBid);
    ASSERT_TRUE(bid.status() == tBid.status());
    ASSERT_TRUE(bid.quantity() == tBid.quantity());
    ASSERT_TRUE(bid.bidder() == tBid.bidder());
    ASSERT_TRUE(bid.biddingPrice() == tBid.biddingPrice());
}

TEST(AgriBiz_Persistence, TestUpdateBid)
{
    tBid.status(BidStatus::DECLINED);
    ASSERT_TRUE(tBidCRUD.update(tBid));
    auto bid = tBidCRUD.fetch(tBid);
    ASSERT_TRUE(bid.status() == tBid.status());
}

TEST(AgriBiz_Persistence, TestRemoveBid)
{
    tBid.status(BidStatus::DECLINED);
    ASSERT_TRUE(tBidCRUD.remove(tBid));
    auto bid = tBidCRUD.fetch(tBid);
    ASSERT_TRUE(bid.getId() == 0);
}

} // namespace unittest
} // namespace demystify