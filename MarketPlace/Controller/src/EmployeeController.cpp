#include "EmployeeController.hpp"


using namespace demystify;
using namespace ::subsystem::AntiGhostWorker;
using namespace personal;


web::json::value JsonConversion::EmployeeAsJSON(const Employee& employee)
{
    using namespace web::json;

    auto result = value::object();
    auto user = static_cast<personal::User>(employee);

    result[U("foundational")] = web::json::value::parse(
        JsonConversion::UserAsJSON(user).serialize()
    );
    result[U("chip")] = web::json::value::parse(JsonConversion::ChipAsJSON(employee.getChip()).serialize());

    return result;
}

Employee JsonConversion::EmployeeFromJSON(const web::json::value& employeeJson)
{
    Employee tmpEmployee;
    if (employeeJson.has_field("foundational"))
    {
        auto user = JsonConversion::UserFromJSON(employeeJson.at("foundational"));
        tmpEmployee = user;
    }
    if (employeeJson.has_field("chip"))
    {
        tmpEmployee.setChip(JsonConversion::ChipFromJSON(employeeJson.at("chip")));
    }
    
    return tmpEmployee;
}