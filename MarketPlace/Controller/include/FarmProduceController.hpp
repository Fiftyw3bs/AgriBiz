#ifndef EMPLOYEE_CONTROLLER_HPP_
#define EMPLOYEE_CONTROLLER_HPP_

#include "AGW_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "ChipController.hpp"


using namespace demystify;

using EmployeeController = demystify::subsystem::AntiGhostWorker::Controller<EmployeeCRUD>;

namespace demystify::JsonConversion
{
    using namespace subsystem::AntiGhostWorker;
    web::json::value EmployeeAsJSON(const Employee& employee);
    Employee EmployeeFromJSON(const web::json::value& EmployeeJson);
} // namespace JsonConversion

#endif //EMPLOYEE_CONTROLLER_HPP_
