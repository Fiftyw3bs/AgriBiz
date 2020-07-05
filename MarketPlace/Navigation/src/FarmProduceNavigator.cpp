#include "FarmProduceNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


FarmProduceNavigator::FarmProduceNavigator(const http_request& message, PGPoolPtr& pgPool) : Navigator(message, pgPool)
{
}

web::json::value FarmProduceNavigator::process(pplx::task<web::json::value> content)
{
    Controller<FarmProduceCRUD> FarmProduceController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = FarmProduceController.fetchAll(1000, content, std::make_pair(JsonConversion::FarmProduceAsJSON, JsonConversion::ChipFromJSON));
        }
        else if (this->args.size() == 1) // Fetch by FarmProduce ID
        {
            message = FarmProduceController.fetchOne(stoi(this->args[0]), JsonConversion::FarmProduceAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = FarmProduceController.add(content, JsonConversion::FarmProduceFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = FarmProduceController.update(content, stoi(this->args[0]), JsonConversion::FarmProduceFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = FarmProduceController.remove(content, stoi(this->args[0]), JsonConversion::ChipFromJSON);
        }
        else if (this->args.size() == 0)
        {
            message = FarmProduceController.remove(content, 0, JsonConversion::ChipFromJSON);
        }
        
    }
    
    return message;
    
}