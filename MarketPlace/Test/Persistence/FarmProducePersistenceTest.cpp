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
FarmProduce tFarmProduce;
FarmProduceCRUD tFarmProduceCRUD(myPool);
VectorOf<FarmProduce> dbFarmProduces;

TEST(AgriBiz_Persistence, TestAddFarmProduce)
{
    // User tUser = tUserCRUD.fetchOne(1);
    tFarmProduce.name("Beans");
    auto FarmProduceId = tFarmProduceCRUD.add(tFarmProduce);
    ASSERT_TRUE(FarmProduceId != 0);
    tFarmProduce.name("Rice");
    FarmProduceId = tFarmProduceCRUD.add(tFarmProduce);
    ASSERT_TRUE(FarmProduceId != 0);
    tFarmProduce.name("Garri");
    FarmProduceId = tFarmProduceCRUD.add(tFarmProduce);
    ASSERT_TRUE(FarmProduceId != 0);
    tFarmProduce.setId(FarmProduceId);
}

TEST(AgriBiz_Persistence, TestFetchFarmProduce)
{
    auto FarmProduce = tFarmProduceCRUD.fetch(tFarmProduce);
    ASSERT_TRUE(FarmProduce.name() == tFarmProduce.name());
}

TEST(AgriBiz_Persistence, TestUpdateFarmProduce)
{
    tFarmProduce.description("This is a very nice one");
    ASSERT_TRUE(tFarmProduceCRUD.update(tFarmProduce));
    auto FarmProduce = tFarmProduceCRUD.fetch(tFarmProduce);
    ASSERT_TRUE(FarmProduce.name() == tFarmProduce.name());
    ASSERT_TRUE(FarmProduce.description() == tFarmProduce.description());
}

TEST(AgriBiz_Persistence, TestRemoveFarmProduce)
{
    ASSERT_TRUE(tFarmProduceCRUD.remove(tFarmProduce));
    auto FarmProduce = tFarmProduceCRUD.fetch(tFarmProduce);
    ASSERT_TRUE(FarmProduce.getId() == 0);
}

} // namespace unittest
} // namespace demystify