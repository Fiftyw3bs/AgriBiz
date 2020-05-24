#include "StampCRUD.hpp"

using namespace demystify;
using namespace persistence;
using namespace personal;
using namespace demystify::subsystem::AntiGhostWorker;

StampCRUD::StampCRUD(PGPoolPtr& pgPool) : 
    GenericCRUD(StampCRUD::crudStatements, pgPool)
{
}

VectorOf<Stamp> StampCRUD::processFetched(const result res)
{
    VectorOf<Stamp> tmpStamps;
    Chip chip;

    if (!res.empty() && res.size() > 0)
    {
        for (auto row : res)
        {
            Datable tmpDate;
            tmpDate.setDate(row["stampTime"].as<std::string>());
            chip.setId(row["chip_id"].as<uint32_t>());

            StampType stampType = NOT_YET;

            if (!row["stampType"].as<bool>())
            {
                stampType = ARIVAL;
            } else
            {
                stampType = DEPARTURE;
            }

            Stamp stamp(chip, tmpDate, stampType);
            stamp.setId(row["stamp_id"].as<uint32_t>());
            tmpStamps.push_back(stamp);
        }
    }
    else
    {
        tmpStamps.push_back(INVALID_STAMP());
    }
    

    return tmpStamps;
}

UserID StampCRUD::add(const Stamp& stamp)
{
    auto mm = this->performDBOperation(
        "STAMP_CREATE",
        stamp.getChip().getId(),
        stamp.getStampTime().getTimeString(),
        static_cast<bool>(stamp.getStampType())
    );

    UserID chipId = 0;

    if (!mm[0]["stamp_id"].is_null())
    {
        chipId = mm[0]["stamp_id"].as<UserID>();
    }

    return chipId;
}
bool StampCRUD::remove(const StampID& stampId)
{
    return this->performDBOperation(
        "STAMP_REMOVE_ONE_BY_ID",
        stampId
    ).empty();
}
bool StampCRUD::removeAllByChip(const Chip& chip)
{
    return this->performDBOperation(
        "STAMP_REMOVE_ALL_BY_CHIP_ID",
        chip.getId()
    ).empty();
}
bool StampCRUD::update(const Stamp& stamp)
{
    return this->performDBOperation(
        "STAMP_MODIFY",
        static_cast<bool>(stamp.getStampType()),
        stamp.getId()
    ).empty();
}
VectorOf<Stamp> StampCRUD::fetchByChip(const Chip& chip)
{
    auto retVal = this->performDBOperation("STAMP_FETCH_ALL_BY_CHIP_ID", chip.getId());
    
    return this->processFetched(retVal);
}

Stamp StampCRUD::fetchOne(const StampID& stampId)
{
    auto retVal = this->performDBOperation("STAMP_FETCH_ONE_BY_STAMP_ID", stampId);

    return this->processFetched(retVal)[0];
}

VectorOf<Stamp> StampCRUD::fetchByStampTime(const Chip& chip, const Datable& startDate, const Datable& endDate)
{
    auto retVal = this->performDBOperation("STAMP_FETCH_BY_STAMPTIME_CHIP_ID", chip.getId(), startDate.getTimeString(), endDate.getTimeString());

    return this->processFetched(retVal);
}

VectorOf<Stamp> StampCRUD::fetchAllByStampTime(const Datable& startDate, const Datable& endDate)
{
    auto retVal = this->performDBOperation("STAMP_FETCH_ALL_BY_STAMPTIME", startDate.getTimeString(), endDate.getTimeString());

    return this->processFetched(retVal);
}

DBStatements StampCRUD::crudStatements{
    {"STAMP_CREATE", "INSERT INTO Stamp (chip_id, stamp_id, stampTime, stampType) VALUES ($1, DEFAULT, $2, $3) RETURNING stamp_id"},
    {"STAMP_MODIFY", "UPDATE Stamp SET stampType=$1 WHERE stamp_id = $2"},
    {"STAMP_REMOVE_ONE_BY_ID", "DELETE FROM Stamp WHERE stamp_id = $1"},
    {"STAMP_REMOVE_ALL_BY_CHIP_ID", "DELETE FROM Stamp WHERE chip_id = $1"},
    {"STAMP_FETCH_ALL_BY_CHIP_ID", "SELECT chip_id, stamp_id, stampTime, stampType FROM Stamp WHERE chip_id = $1 ORDER BY stampTime ASC"},
    {"STAMP_FETCH_ONE_BY_STAMP_ID", "SELECT chip_id, stamp_id, stampTime, stampType FROM Stamp WHERE stamp_id = $1"},
    {"STAMP_FETCH_ALL_BY_STAMPTIME", "SELECT chip_id, stamp_id, stampTime, stampType FROM Stamp WHERE stampTime BETWEEN $1 AND $2"},
    {"STAMP_FETCH_BY_STAMPTIME_CHIP_ID", "SELECT chip_id, stamp_id, stampTime, stampType FROM Stamp WHERE chip_id=$1 AND stampTime BETWEEN $2 AND $3"}
};