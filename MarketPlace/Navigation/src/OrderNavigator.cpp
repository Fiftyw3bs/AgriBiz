#include "OrderNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


OrderNavigator::OrderNavigator(const http_request& message, PGPoolPtr& pgPool) : Navigator(message, pgPool)
{
}

web::json::value OrderNavigator::process(pplx::task<web::json::value> content)
{
    Controller<OrderCRUD> OrderController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = OrderController.fetchAll(1000, JsonConversion::OrderAsJSON);
        }
        else if (this->args.size() == 1)
        {
            message = OrderController.fetchOne(stoi(this->args[0]), JsonConversion::OrderAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = OrderController.add(content, JsonConversion::OrderFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = OrderController.update(content, stoi(this->args[0]), JsonConversion::OrderFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = OrderController.remove(content, stoi(this->args[0]), JsonConversion::OrderFromJSON);
        }
    }
    
    return message;
    
}