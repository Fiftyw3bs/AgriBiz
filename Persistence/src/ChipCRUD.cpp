#include "ChipCRUD.hpp"

using namespace demystify;
using namespace persistence;
using namespace subsystem::AntiGhostWorker;

ChipCRUD::ChipCRUD(PGPoolPtr& pgPool) : 
    GenericCRUD(ChipCRUD::crudStatements, pgPool)
{
}

ChipID ChipCRUD::add(const Chip& chip)
{
    ChipID chipId = 0;

    auto mm = this->performDBOperation(
        "CHIP_CREATE",
        chip.getChipToken()
    );
    
    if (!mm[0]["chip_id"].is_null())
    {
        chipId = mm[0]["chip_id"].as<ChipID>();
    }

    return chipId;
}

bool ChipCRUD::remove(const Chip& chip)
{
    return this->performDBOperation(
        "CHIP_REMOVE_ONE_BY_ID",
        chip.getId()
    ).empty();
}

bool ChipCRUD::update(const Chip& chip)
{
    return this->performDBOperation(
        "CHIP_MODIFY",
        chip.isAssigned(),
        chip.getId()
    ).empty();    
}
Chip ChipCRUD::fetchOne(const UserID& userId)
{
    auto retVal = this->performDBOperation("CHIP_FETCH_ONE_BY_USER_ID", userId);

    return this->processFetched(retVal)[0];

}
VectorOf<Chip> ChipCRUD::processFetched(const result& res)
{

    VectorOf<Chip> tmpChips;
    Chip tmpChip;

    if (!res.empty() && res.size() > 0)
    {
        for (auto row : res)
        {
            tmpChip.setId(row["chip_id"].as<uint32_t>());
            tmpChip.setChipToken(row["chipToken"].as<uint32_t>());

            if (row["assigned"].as<bool>())
            {
                tmpChip.toggleAssignedState();
            }

            UserID tmpUserId;

            if (!row["user_id"].is_null())
            {
                tmpUserId = row["user_id"].as<uint32_t>();
            }
            else
            {
                tmpUserId = 0;                
            }

            tmpChips.push_back(tmpChip);
        }
    }
    else
    {
        tmpChips.push_back(tmpChip);
    }
    

    return tmpChips;
}
VectorOf<Chip> ChipCRUD::fetchAll(const FetchLimit& limit)
{
    auto retVal = this->performDBOperation("CHIP_FETCH_ALL", limit);

    return this->processFetched(retVal);
}

bool ChipCRUD::assign(const UserID& userId, const ChipID& chipId)
{
    Chip tmpChip;
    tmpChip.setId(chipId);
    tmpChip.toggleAssignedState();

    return (this->performDBOperation(
        "CHIP_ASSIGN_TO_USER",
        chipId,
        userId
    ).empty() && this->update(tmpChip));
}
bool ChipCRUD::revoke(const UserID& userId, const ChipID& chipId)
{
    Chip tmpChip;
    tmpChip.setId(chipId);

    return (this->performDBOperation(
        "CHIP_RESCIND_FROM_USER",
        userId,
        chipId
    ).empty() && this->update(tmpChip));    
}
DBStatements ChipCRUD::crudStatements{
    {"CHIP_FETCH_ALL", 
        "SELECT \
            t1.chip_id, \
            t1.chipToken, \
            t1.assigned, \
            t2.user_id \
         FROM Chip t1 \
         LEFT JOIN user_chip t2 on t1.chip_id = t2.chip_id \
         LIMIT $1"
    },
    {"CHIP_FETCH_ONE_BY_USER_ID", 
        "SELECT \
            t1.chip_id, \
            t1.chipToken, \
            t1.assigned, \
            t2.user_id \
         FROM Chip t1 \
         LEFT JOIN user_chip t2 on t1.chip_id = t2.chip_id \
         WHERE t2.user_id = $1"
    },
    {"CHIP_CREATE", "INSERT INTO Chip (chip_id, chipToken) VALUES (DEFAULT, $1) RETURNING chip_id"},
    {"CHIP_REMOVE_ONE_BY_ID", "DELETE FROM Chip WHERE CHIP_id = $1"},
    {"CHIP_ASSIGN_TO_USER", "INSERT INTO User_Chip (CHIP_id, user_id) VALUES($1, $2)"},
    {"CHIP_RESCIND_FROM_USER", "DELETE FROM User_Chip WHERE CHIP_id=$1 AND user_id=$2"},
    {"CHIP_MODIFY", "UPDATE Chip SET assigned=$1 WHERE chip_id=$2"}
};