#include <iostream>
#include <thread>
#include <utility>
#include "gtest/gtest.h"

#include "Order.hpp"
#include "User.hpp"
#include "UserCRUD.hpp"
#include "AgriBiz_Persistence.hpp"

namespace demystify
{
namespace unittest
{
using namespace std;
using namespace personal;
using namespace AgriBiz;
using namespace AgriBiz::persistence;


    Order tOrder;
    User tUser{};
    ContactDetails cd;
    auto Db = MDBInstance::get_instance();
    MongoDBInfo dbInfo("test_farmer");

TEST(OrderCRUD_Test, TestAddNew)
{
    cd.first_name("Femi");
    cd.last_name("Sko");
    cd.middle_name("Blah");
    cd.address("Where are you from");
    cd.city("Jagunlabi");
    tUser.contact_details(cd);

    Db->create_pool("mongodb://localhost:27017");
    auto db_client = Db->get_client();

    UserCRUD UserDbo(*db_client, dbInfo);

    auto UserId = UserDbo.add(tUser);
    ASSERT_TRUE(!UserId.empty());

    tUser.setId(UserId);

    tOrder.orderer(tUser);
    tOrder.costPerKg(123);
    tOrder.description("This is a new one");
    tOrder.quantity(15);
    tOrder.type(OrderType::SELL);
    Datable date;
    date.setDate("10/10/2020");
    tOrder.harvestDate(date);

    db_client = Db->get_client();

    OrderCRUD orderDbo(*db_client, dbInfo);

    auto orderId = orderDbo.add(tOrder);

    ASSERT_TRUE(!orderId.empty());

    tOrder.setId(orderId);
    ASSERT_TRUE(!tOrder.getId().empty());
    ASSERT_TRUE(tOrder.getId() == orderId);

}

TEST(OrderCRUD_Test, TestFetchOne)
{

    Db = MDBInstance::get_instance();
    Db->create_pool("mongodb://localhost:27017");
    auto db_client = Db->get_client();
    OrderCRUD orderDbo(*db_client, dbInfo);

    auto order = orderDbo.fetch(tOrder);

    ASSERT_EQ(order.costPerKg(), tOrder.costPerKg());

    order = orderDbo.fetch(order);

    ASSERT_TRUE(order.orderer() == tOrder.orderer());
}

TEST(OrderCRUD_Test, TestModify)
{
    Db = MDBInstance::get_instance();
    Db->create_pool("mongodb://localhost:27017");
    MongoDBInfo dbInfo("test_farmer");
    auto db_client = Db->get_client();
    OrderCRUD orderDbo(*db_client, dbInfo);

    auto old_costPerKg = tOrder.costPerKg();
    tOrder.costPerKg(456);
    {
        Bid bid;
        bid.bidder(tUser);
        bid.quantity(132);
        bid.biddingPrice(34);
        bid.status("PENDING");

        tOrder.assignBid(bid);
    }
    {
        Bid bid;
        bid.bidder(tUser);
        bid.quantity(666);
        bid.biddingPrice(99);
        bid.status("ACCEPTED");

        tOrder.assignBid(bid);
    }

    ASSERT_TRUE(orderDbo.update(tOrder));

    auto order = orderDbo.fetch(tOrder);
    // ASSERT_TRUE(order.size() == 2);

    ASSERT_TRUE(order.costPerKg() == tOrder.costPerKg());
    ASSERT_FALSE(order.costPerKg() == old_costPerKg);
}

TEST(OrderCRUD_Test, TestRemove)
{
    Db = MDBInstance::get_instance();
    Db->create_pool("mongodb://localhost:27017");
    MongoDBInfo dbInfo("test_farmer");
    auto db_client = Db->get_client();
    OrderCRUD userDbo(*db_client, dbInfo);

    ASSERT_TRUE(userDbo.remove(tOrder));
    ASSERT_FALSE(!userDbo.fetch(tOrder).getId().empty());
}

// TEST(OrderCRUD_Test, TestFetchMany)
// {
//     Db = MDBInstance::get_instance();
//     Db->create_pool("mongodb://localhost:27017");
//     MongoDBInfo dbInfo("test_farmer");
//     auto db_client = Db->get_client();
//     OrderCRUD UserDbo(*db_client, dbInfo);

//     VectorOf<User> Users;

//     for (size_t i = 0; i < 10; i++) {
//         User User;
//         ContactDetails cd;
//         cd.first_name("User" + std::to_string(i));
//         User.contact_details(cd);
//         auto UserOID = UserDbo.add(User);
//         User.setId(UserOID);
//         Users.push_back(User);
//     }

//     auto fetched_Users = UserDbo.fetch(0, 2);

//     ASSERT_TRUE(!fetched_Users.empty());

// }

} // namespace unittest
} // namespace demystify
