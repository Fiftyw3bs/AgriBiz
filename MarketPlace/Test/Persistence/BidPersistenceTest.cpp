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

// TEST(AgriBiz_Persistence, TestFetch)
// {
//     dbBids = tBidCRUD.fetch(5);
//     tBid.setId(dbBids.front().getId());
//     ASSERT_TRUE(dbBids.size() == 5);
// }

TEST(AgriBiz_Persistence, TestAddBid)
{
    User tUser = tUserCRUD.fetchOne(1);
    tBid.status(BidStatus::PENDING);
    tBid.quantity(123.4);
    tBid.bidder(tUser);
    tBid.biddingPrice(4213);
    auto bidId = tBidCRUD.add(tBid);
    tBid.setId(bidId);
    ASSERT_TRUE(bidId != 0);
}

// TEST(AgriBiz_Persistence, TestRemoveBid)
// {
//     ASSERT_TRUE(tBidCRUD.remove(tBid));
// }

} // namespace unittest
} // namespace demystify