#include <iostream>
#include "gtest/gtest.h"

#include "AGW_Persistence.hpp"

namespace demystify
{
namespace unittest
{

using namespace subsystem::AntiGhostWorker;
using namespace persistence;

PGPoolPtr myPool = std::make_shared<PGPool>(DBInfo());
personal::User tUser("Username");
Chip tChip;
ChipCRUD tChipCRUD(myPool);
UserCRUD tUserCRUD(myPool);
VectorOf<Chip> dbChips;

TEST(AntiGhostWorker_Persistence, TestFetchAll)
{
    dbChips = tChipCRUD.fetchAll(5);
    tChip.setId(dbChips.front().getId());
    ASSERT_TRUE(dbChips.size() == 5);
}

TEST(AntiGhostWorker_Persistence, TestAssign)
{
    UserID id = tUserCRUD.fetchAll(1)[0].getId();
    tUser.setId(id);
    ASSERT_TRUE(tChipCRUD.assign(tUser.getId(), tChip.getId()));
}

TEST(AntiGhostWorker_Persistence, TestAddChip)
{
    tChip.setChipToken(1092332);
    ASSERT_TRUE(tChipCRUD.add(tChip));
}

TEST(AntiGhostWorker_Persistence, TestRevokeAccess)
{
    ASSERT_TRUE(tChipCRUD.revoke(tUser.getId(), tChip.getId()));
}

TEST(AntiGhostWorker_Persistence, TestRemoveChip)
{
    ASSERT_TRUE(tChipCRUD.remove(tChip));
}

} // namespace unittest
} // namespace demystify