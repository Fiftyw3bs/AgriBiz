#include "ChipController.hpp"


using namespace demystify;
using namespace ::subsystem::AntiGhostWorker;
using namespace personal;

web::json::value JsonConversion::ChipAsJSON(const Chip& chip)
{
    web::json::value result = web::json::value::object();
    result[U("chipId")] = web::json::value::number(chip.getId());
    result[U("chipToken")] = web::json::value::number(chip.getChipToken());
    result[U("assigned")] = web::json::value::boolean(chip.isAssigned());
    return result;
}

Chip JsonConversion::ChipFromJSON(const web::json::value& ChipJson)
{
    Chip chip;
    chip.setChipToken(ChipJson.at("chipToken").as_number().to_uint32());
    if (ChipJson.has_field("assigned"))
    {
        if (ChipJson.at("assigned").as_bool())
        {
            chip.toggleAssignedState();
        }
    }
    if (ChipJson.has_field("chipId"))
    {
        chip.setId(ChipJson.at("chipId").as_number().to_uint32());
    }
    return chip;
}