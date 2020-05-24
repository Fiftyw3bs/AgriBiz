#ifndef EMPLOYEE_NAVIGATOR_HPP_
#define EMPLOYEE_NAVIGATOR_HPP_

#include "Server.hpp"
#include "PGPool.hpp"
#include "Models.hpp"
#include "Navigator.hpp"
#include "EmployeeController.hpp"

#include <string>

namespace demystify 
{
namespace subsystem
{
namespace AntiGhostWorker
{

using namespace navigation;
using namespace persistence;
    
using ControllerType = std::string;
using Action = std::string;

class EmployeeNavigator : public Navigator
{
public:
    EmployeeNavigator(
        const http_request& message,
        PGPoolPtr& pgPool
    );
    virtual web::json::value process(pplx::task<web::json::value> content);

};

} // namespace AntiGhostWorker

} // namespace subsystem
    
} // demystify


#endif //EMPLOYEE_NAVIGATOR_HPP_
