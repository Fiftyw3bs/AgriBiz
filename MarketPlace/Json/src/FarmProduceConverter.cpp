#include "FarmProduceConverter.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

std::string JsonConversion::FarmProduceAsJSON(const FarmProduce& farmProduce)
{
    web::json::value result = web::json::value::object();

    auto bidId = JsonConversion::IdentifiableAsJSON(farmProduce);
    result[U("name")] = web::json::value::string(farmProduce.name());
    result[U("description")] = web::json::value::string(farmProduce.description());

    return result.serialize();
}

FarmProduce JsonConversion::FarmProduceFromJSON(std::string json)
{
    FarmProduce farmProduce;
    auto farmProduceJson = web::json::value::parse(json);

    try
    {
        farmProduce.setId(JsonConversion::IdentifiableFromJSON(farmProduceJson.serialize()).getId());
        farmProduce.name(farmProduceJson.at("name").as_string());
        farmProduce.description(farmProduceJson.at("description").as_string());
    } catch(web::json::json_exception e)
    {
        // Error Here <<
    }

    return farmProduce;
}