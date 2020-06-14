#include "FarmProduceCRUD.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace AgriBiz::persistence;

FarmProduceCRUD::FarmProduceCRUD(PGPoolPtr& pgPool) : 
    GenericCRUD(FarmProduceCRUD::crudStatements, pgPool)
{
}

VectorOf<FarmProduce> FarmProduceCRUD::processFetched(const result res)
{
    VectorOf<FarmProduce> tmpFarmProduces;
    FarmProduce farmProduce;

    if (!res.empty() && res.size() > 0)
    {
        for (auto row : res)
        {
            farmProduce.name(row["name"].as<std::string>());
            farmProduce.setId(row["farm_produce_id"].as<uint32_t>());
            farmProduce.description(row["description"].as<std::string>());
            tmpFarmProduces.push_back(farmProduce);
        }
    }
    else
    {
        tmpFarmProduces.push_back(farmProduce);
    }
    

    return tmpFarmProduces;
}

UserID FarmProduceCRUD::add(const FarmProduce& farmProduce)
{
    auto mm = this->performDBOperation(
        "FARM_PRODUCE_CREATE",
        farmProduce.name(),
        farmProduce.description()
    );

    UserID FarmProduceId = 0;

    if (!mm[0]["farm_produce_id"].is_null())
    {
        FarmProduceId = mm[0]["farm_produce_id"].as<UserID>();
    }

    return FarmProduceId;
}
bool FarmProduceCRUD::remove(const FarmProduce& farmProduce)
{
    return this->performDBOperation(
        "FARM_PRODUCE_REMOVE_ONE_BY_ID",
        farmProduce.getId()
    ).empty();
}
bool FarmProduceCRUD::update(const FarmProduce& farmProduce)
{
    return this->performDBOperation(
        "FARM_PRODUCE_MODIFY",
        farmProduce.name(),
        farmProduce.description(),
        farmProduce.getId()
    ).empty();
}

FarmProduce FarmProduceCRUD::fetch(const FarmProduce& farmProduce)
{
    auto retVal = this->performDBOperation(
        "FARM_PRODUCE_FETCH_ONE_BY_ID",
        farmProduce.getId()
    );

    return this->processFetched(retVal)[0];
}
VectorOf<FarmProduce> FarmProduceCRUD::fetch(const Offset& offset, const Limit& limit)
{
    auto retVal = this->performDBOperation(
        "FARM_PRODUCE_FETCH_ALL",
        offset,
        limit
    );

    return this->processFetched(retVal);
}

DBStatements FarmProduceCRUD::crudStatements{
    {"FARM_PRODUCE_CREATE", "INSERT INTO FarmProduce (farm_produce_id, name, description) VALUES (DEFAULT, $1, $2) RETURNING farm_produce_id"},
    {"FARM_PRODUCE_MODIFY", "UPDATE FarmProduce SET name=$1, description=$2 WHERE farm_produce_id = $3"},
    {"FARM_PRODUCE_REMOVE_ONE_BY_ID", "DELETE FROM FarmProduce WHERE farm_produce_id = $1"},
    {"FARM_PRODUCE_FETCH_ONE_BY_ID", "SELECT farm_produce_id, name, description FROM FarmProduce WHERE farm_produce_id = $1 ORDER BY farm_produce_id DESC"},
    {"FARM_PRODUCE_FETCH_ALL", "SELECT farm_produce_id, name, description FROM FarmProduce ORDER BY name ASC OFFSET $1 ROWS FETCH NEXT $2 ROWS ONLY"}
};