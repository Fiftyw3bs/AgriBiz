#include "FarmProduceController.hpp"


using namespace demystify;
using namespace personal;
using namespace AgriBiz;

web::json::value JsonConversion::FarmProduceAsJSON(const FarmProduce& farmProduce)
{
    web::json::value result = web::json::value::object();
    result[U("farm_produce_id")] = web::json::value::number(farmProduce.getId());
    result[U("name")] = web::json::value::string(farmProduce.name());
    result[U("description")] = web::json::value::string(farmProduce.description());
    return result;
}

FarmProduce JsonConversion::FarmProduceFromJSON(const web::json::value& farmProduceJson)
{
    FarmProduce farmProduce;

    try
    {
        farmProduce.setId(farmProduceJson.at("farm_produce_id").as_number().to_uint32());
        farmProduce.name(farmProduceJson.at("name").as_string());
        farmProduce.description(farmProduceJson.at("description").as_string());
    } catch(web::json::json_exception e)
    {
        // Error Here <<
    }

    return farmProduce;
}