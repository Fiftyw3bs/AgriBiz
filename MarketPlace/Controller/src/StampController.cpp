#include "StampController.hpp"


using namespace demystify;
using namespace ::subsystem::AntiGhostWorker;
using namespace personal;

web::json::value JsonConversion::StampAsJSON(const Stamp& stamp)
{
    web::json::value result = web::json::value::object();

    try
    {
        result[U("chip")] = web::json::value::parse(JsonConversion::ChipAsJSON(stamp.getChip()).serialize());
        result[U("stampId")] = web::json::value::parse(JsonConversion::IdentifiableAsJSON(stamp.getId()).serialize());
        result[U("stampTime")] = web::json::value::parse(JsonConversion::DatableAsJSON(stamp.getStampTime()).serialize());
        result[U("stampType")] = web::json::value::string(
            (stamp.getStampType() == StampType::ARIVAL) ? "ARIVAL" : "DEPARTURE"
        );
    }
    catch(const web::json::json_exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return result;
}

Stamp JsonConversion::StampFromJSON(const web::json::value& stampJson)
{
    auto chip = JsonConversion::ChipFromJSON(stampJson.at("chip"));
    auto stampId = JsonConversion::IdentifiableFromJSON(stampJson.at("stampId"));
    auto stampTime = JsonConversion::DatableFromJSON(stampJson.at("stampTime"));
    StampType stampType = (stampJson.at("stampType").as_string() == "ARIVAL") ? ARIVAL : DEPARTURE;

    Stamp stamp(chip, stampTime, stampType);
    stamp.setId(stampId);
    
    return stamp;
}