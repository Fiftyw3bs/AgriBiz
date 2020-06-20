#include "StampNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


StampNavigator::StampNavigator(const http_request& message, PGPoolPtr& pgPool) : Navigator(message, pgPool)
{
}

web::json::value StampNavigator::process(pplx::task<web::json::value> content)
{
    Controller<StampCRUD> stampController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = stampController.fetchAll(1000, content, std::make_pair(JsonConversion::StampAsJSON, JsonConversion::ChipFromJSON));
        }
        else if (this->args.size() == 1) // Fetch by Stamp ID
        {
            message = stampController.fetchOne(stoi(this->args[0]), JsonConversion::StampAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = stampController.add(content, JsonConversion::StampFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = stampController.update(content, stoi(this->args[0]), JsonConversion::StampFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = stampController.remove(content, stoi(this->args[0]), JsonConversion::ChipFromJSON);
        }
        else if (this->args.size() == 0)
        {
            message = stampController.remove(content, 0, JsonConversion::ChipFromJSON);
        }
        
    }
    
    return message;
    
}