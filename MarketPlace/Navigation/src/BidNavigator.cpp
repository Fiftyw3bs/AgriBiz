#include "BidNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


BidNavigator::BidNavigator(const http_request& message, mongocxx::client& mdb_client) : Navigator(message, pgPool)
{
}

web::json::value BidNavigator::process(pplx::task<web::json::value> content)
{
    Controller<BidCRUD> BidController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = BidController.fetchAll(1000, JsonConversion::BidAsJSON);
        }
        else if (this->args.size() == 1)
        {
            message = BidController.fetchOne(stoi(this->args[0]), JsonConversion::BidAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = BidController.add(content, JsonConversion::BidFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = BidController.update(content, stoi(this->args[0]), JsonConversion::BidFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = BidController.remove(content, stoi(this->args[0]), JsonConversion::BidFromJSON);
        }
    }
    
    return message;
    
}