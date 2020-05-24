#include "EmployeeNavigator.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;


EmployeeNavigator::EmployeeNavigator(const http_request& message, PGPoolPtr& pgPool) : Navigator(message, pgPool)
{
}

web::json::value EmployeeNavigator::process(pplx::task<web::json::value> content)
{
    Controller<EmployeeCRUD> employeeController(this->pgPool);
    web::json::value message;

    if (this->method == "GET")
    {
        if (this->args.empty())
        {
            message = employeeController.fetchAll(1000, JsonConversion::EmployeeAsJSON);
        }
        else if (this->args.size() == 1)
        {
            message = employeeController.fetchOne(stoi(this->args[0]), JsonConversion::EmployeeAsJSON);
        }
        else
        {
        }
    }
    else if (this->method == "POST")
    {
        message = employeeController.add(content, JsonConversion::EmployeeFromJSON);
    }
    else if(this->method == "PATCH")
    {
        message = employeeController.update(content, stoi(this->args[0]), JsonConversion::EmployeeFromJSON);
    }
    else if(this->method == "DELETE")
    {
        if (this->args.size() == 1)
        {
            message = employeeController.remove(content, stoi(this->args[0]), JsonConversion::EmployeeFromJSON);
        }
    }
    
    return message;
    
}