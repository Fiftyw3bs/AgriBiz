#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "gtest/gtest.h"

#include "AGW_Persistence.hpp"
#include "AGW_Model.hpp"

namespace demystify
{
namespace unittest
{

using namespace demystify::subsystem::AntiGhostWorker;

VectorOf<Chip> chips;
VectorOf<PointerOf<Stamp>> stampPtrs;

void addStamp(size_t numberOfStamps, Chip chip)
{
    stampPtrs.clear();
    VectorOf<Stamp> stamps;

    for (size_t i = 0; i < numberOfStamps; i++)
    {
        Stamp tempStamp(chip, Datable(), (static_cast<StampType>(i%2==0)));
        tempStamp.setId(i);
        stamps.push_back(tempStamp);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    for (auto stamp : stamps)
    {
        stampPtrs.push_back(MakePointerOf<Stamp>(stamp));
    }

    ASSERT_TRUE(stampPtrs.size() == numberOfStamps);
}

TEST(AntiGhostWorker_Model, TestTeamManager_With_1_Stamp)
{
    Chip chip;
    chip.setId(1);
    chip.setChipToken(232431773);

    addStamp(1, chip);

    ASSERT_TRUE(stampPtrs.size() == 1);

    TimeManager tTimeManager(stampPtrs);
    auto accumulation = tTimeManager.getAccumulation();

    ASSERT_TRUE(accumulation.size() == 1);
    ASSERT_TRUE(accumulation[0].first == *stampPtrs[0].get());
    ASSERT_TRUE(accumulation[0].second == INVALID_STAMP());

    for(auto stampPair : accumulation)
    {
        std::cout << "Chip Token: " << stampPair.first.getChip().getChipToken() << " | " << stampPair.first.getId() << ": " << stampPair.first.getStampTime().getTimeString();
        std::cout << " | " << stampPair.second.getId() << ": " << stampPair.second.getStampTime().getTimeString() << std::endl;
        // ASSERT_TRUE();
    }
}

TEST(AntiGhostWorker_Model, TestTeamManager_With_2_Stamps)
{
    Chip chip;
    chip.setId(2);
    chip.setChipToken(123423);

    addStamp(2, chip);
    TimeManager tTimeManager(stampPtrs);
    auto accumulation = tTimeManager.getAccumulation();

    ASSERT_TRUE(accumulation.size() == 1);
    ASSERT_TRUE(accumulation[0].first == *stampPtrs[1].get());
    ASSERT_TRUE(accumulation[0].second == *stampPtrs[0].get());

    for(auto stampPair : accumulation)
    {
        std::cout << "Chip Token: " << stampPair.first.getChip().getChipToken() << " | " << stampPair.first.getId() << ": " << stampPair.first.getStampTime().getTimeString();
        std::cout << " | " << stampPair.second.getId() << ": " << stampPair.second.getStampTime().getTimeString() << std::endl;
        // ASSERT_TRUE();
    }
}

TEST(AntiGhostWorker_Model, TestTeamManager_With_Even_Stamps)
{
    Chip chip;
    chip.setId(2);
    chip.setChipToken(123423);

    addStamp(4, chip);
    TimeManager tTimeManager(stampPtrs);
    auto accumulation = tTimeManager.getAccumulation();

    ASSERT_TRUE(accumulation.size() == 2);
    ASSERT_TRUE(accumulation[0].first == *stampPtrs[1].get());
    ASSERT_TRUE(accumulation[0].second == *stampPtrs[0].get());

    for(auto stampPair : accumulation)
    {
        std::cout << "Chip Token: " << stampPair.first.getChip().getChipToken() << " | " << stampPair.first.getId() << ": " << stampPair.first.getStampTime().getTimeString();
        std::cout << " | " << stampPair.second.getId() << ": " << stampPair.second.getStampTime().getTimeString() << std::endl;
        // ASSERT_TRUE();
    }
}

TEST(AntiGhostWorker_Model, TestTeamManager_With_Odd_Stamps)
{
    Chip chip;
    chip.setId(2);
    chip.setChipToken(123423);

    addStamp(7, chip);
    TimeManager tTimeManager(stampPtrs);
    auto accumulation = tTimeManager.getAccumulation();

    ASSERT_TRUE(accumulation.size() == 4);
    ASSERT_TRUE(accumulation[0].first == *stampPtrs[1].get());
    ASSERT_TRUE(accumulation[0].second == *stampPtrs[0].get());

    for(auto stampPair : accumulation)
    {
        std::cout << "Chip Token: " << stampPair.first.getChip().getChipToken() << " | " << stampPair.first.getId() << ": " << stampPair.first.getStampTime().getTimeString();
        std::cout << " | " << stampPair.second.getId() << ": " << stampPair.second.getStampTime().getTimeString() << std::endl;
        // ASSERT_TRUE();
    }
}

} // namespace unittest
} // namespace demystify