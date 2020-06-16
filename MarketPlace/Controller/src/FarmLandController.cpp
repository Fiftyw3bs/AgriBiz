#include "FarmLandController.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::FarmLandAsJSON(const FarmLand& FarmLand)
{
    web::json::value result = web::json::value::object();
    result[U("FarmLandId")] = web::json::value::number(FarmLand.getId());
    result[U("FarmLandToken")] = web::json::value::number(FarmLand.getFarmLandToken());
    result[U("assigned")] = web::json::value::boolean(FarmLand.isAssigned());
    return result;
}

FarmLand JsonConversion::FarmLandFromJSON(const web::json::value& FarmLandJson)
{
    FarmLand FarmLand;
    FarmLand.setFarmLandToken(FarmLandJson.at("FarmLandToken").as_number().to_uint32());
    if (FarmLandJson.has_field("assigned"))
    {
        if (FarmLandJson.at("assigned").as_bool())
        {
            FarmLand.toggleAssignedState();
        }
    }
    if (FarmLandJson.has_field("FarmLandId"))
    {
        FarmLand.setId(FarmLandJson.at("FarmLandId").as_number().to_uint32());
    }
    return FarmLand;
}