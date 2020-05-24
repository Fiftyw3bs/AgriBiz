#include "ChipNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


ChipNavigator::ChipNavigator(const http_request& message, PGPoolPtr& pgPool) : Navigator(message, pgPool)
{
}

web::json::value ChipNavigator::process(pplx::task<web::json::value> content)
{
    Controller<ChipCRUD> ChipController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = ChipController.fetchAll(1000, JsonConversion::ChipAsJSON);
        }
        else if (this->args.size() == 1)
        {
            message = ChipController.fetchOne(stoi(this->args[0]), JsonConversion::ChipAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = ChipController.add(content, JsonConversion::ChipFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = ChipController.update(content, stoi(this->args[0]), JsonConversion::ChipFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = ChipController.remove(content, stoi(this->args[0]), JsonConversion::ChipFromJSON);
        }
    }
    
    return message;
    
}