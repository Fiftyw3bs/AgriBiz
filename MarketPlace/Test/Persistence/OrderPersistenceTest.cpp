#include <iostream>
#include "gtest/gtest.h"

#include "AgriBiz_Persistence.hpp"

namespace demystify
{
namespace unittest
{

using namespace AgriBiz;
using namespace AgriBiz::persistence;

extern PGPoolPtr myPool;
extern personal::User tUser;
Order tOrder;
OrderCRUD tOrderCRUD(myPool);
extern UserCRUD tUserCRUD;
VectorOf<Order> dbOrders;

TEST(AgriBiz_Persistence, TestAddOrder)
{
    // User tUser = tUserCRUD.fetchOne(1);
    User tUser;
    tUser.setId(1);
    tOrder.description("New order for the people of the streets");
    tOrder.status(OrderStatus::PENDING);
    tOrder.costPerKg(34.5);
    tOrder.harvestDate(Datable());
    tOrder.orderer(tUser);
    tOrder.farmProduce(FarmProduce("Garri"));
    tOrder.quantity(50);
    tOrder.type(OrderType::SELL);
    tOrder.location(Location());

    auto OrderId = tOrderCRUD.add(tOrder);
    tOrder.setId(OrderId);
    ASSERT_TRUE(OrderId != 0);
}

TEST(AgriBiz_Persistence, TestFetchOrder)
{
    auto Order = tOrderCRUD.fetch(tOrder);
    ASSERT_TRUE(Order.status() == tOrder.status());
}

TEST(AgriBiz_Persistence, TestUpdateOrder)
{
    tOrder.status(OrderStatus::SUSPENDED);
    ASSERT_TRUE(tOrderCRUD.update(tOrder));
    auto Order = tOrderCRUD.fetch(tOrder);
    ASSERT_TRUE(Order.status() == tOrder.status());
}

TEST(AgriBiz_Persistence, TestAddBidToOrder)
{
    Bid bid;
    bid.setId(3);
    ASSERT_TRUE(tOrderCRUD.assignBid(bid, tOrder));
}

TEST(AgriBiz_Persistence, TestRemoveOrder)
{
    ASSERT_TRUE(tOrderCRUD.remove(tOrder));
    auto Order = tOrderCRUD.fetch(tOrder);
    ASSERT_TRUE(Order.getId() == 0);
}

} // namespace unittest
} // namespace demystify