/**
******************************************************************************
* @file	persistences\AntiGhostWorker\include\EmployeeCRUD.hpp
* @author 	Fiftywebs
* @version
* @date 27.02.2020
* @brief
******************************************************************************
*/

#ifndef EMPLOYEE_CRUD_HPP_
#define EMPLOYEE_CRUD_HPP_

#include "Employee.hpp"
#include "UserCRUD.hpp"
#include "ChipCRUD.hpp"
#include "GenericCRUD.hpp"

namespace demystify
{
    
namespace subsystem
{

namespace AntiGhostWorker 
{
   
using namespace personal;
using EmployeeID = uint32_t;
using FetchLimit = uint32_t;

class EmployeeCRUD : public GenericCRUD
{
public:
    EmployeeCRUD(PGPoolPtr& pgPool);
    EmployeeID add(const Employee& Employee);
    bool remove(const Employee& user);
    bool update(const Employee& user);
    Employee fetchOne(const UserID& employeeId);
    VectorOf<Employee> fetchAll(const FetchLimit& limit);
    
};
 
} // AntiGhostWorker

} // persistence
    
} // namespace demystify

#endif // !EMPLOYEE_CRUD_HPP_
