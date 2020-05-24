#include <iostream>
#include "gtest/gtest.h"

#include "AGW_Persistence.hpp"

#include <thread>

namespace demystify
{
namespace unittest
{

using namespace subsystem::AntiGhostWorker;
using namespace persistence;

extern PGPoolPtr myPool;
extern Chip tChip;
extern ChipCRUD tChipCRUD;
StampCRUD tStampCRUD(myPool);
extern VectorOf<Chip> dbChips;
VectorOf<UserID> stampIds;
Datable time1, time2;
uint32_t numberOfStamps;

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_Add)
{
    numberOfStamps = 10;

    dbChips = tChipCRUD.fetchAll(100);
    tChip = dbChips[randomFrom(0, 100)];
    
    ASSERT_TRUE(dbChips.size() == 100);

    time1 = Datable();
    for (size_t i = 0; i < numberOfStamps; i++)
    {
        Stamp tempStamp(tChip, Datable(), (static_cast<StampType>(i%2==0)));
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto stampId = tStampCRUD.add(tempStamp);
        stampIds.push_back(stampId);

        ASSERT_TRUE(stampId != 0);
    }
    time2 = Datable();

}

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_FetchByChip)
{
    auto stamps = tStampCRUD.fetchByChip(tChip);
    ASSERT_TRUE(!stamps.empty());
}

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_FetchByStampTime)
{
    auto stamps = tStampCRUD.fetchByStampTime(tChip, time1, time2);
    ASSERT_TRUE(stamps.size() == numberOfStamps);
}

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_FetchAllByStampTime)
{
    auto stamps = tStampCRUD.fetchAllByStampTime(time1, time2);
    ASSERT_TRUE(stamps.size() == numberOfStamps);
}

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_Remove)
{
    auto success = tStampCRUD.remove(stampIds.front());
    ASSERT_TRUE(success);
}

TEST(AntiGhostWorker_Persistence, Test_StampCRUD_Update)
{
    Stamp tempStamp(tChip, Datable(), StampType::DEPARTURE);
    tempStamp.setId(stampIds.front());

    auto success = tStampCRUD.update(tempStamp);
    ASSERT_TRUE(success);    
}

} // namespace unittest
} // namespace demystify