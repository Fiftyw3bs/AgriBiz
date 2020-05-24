#include "EmployeeCRUD.hpp"

using namespace demystify;
using namespace persistence;
using namespace subsystem::AntiGhostWorker;

EmployeeCRUD::EmployeeCRUD(PGPoolPtr& pgPool) : GenericCRUD(UserCRUD::crudStatements, pgPool)
{
}

EmployeeID EmployeeCRUD::add(const Employee& employee)
{
    UserCRUD userDbo(this->pgPool);
    auto employeeId = userDbo.add(employee);

    return employeeId;
}

Employee EmployeeCRUD::fetchOne(const UserID& employeeId)
{
    ChipCRUD chipDbo(this->pgPool);
    UserCRUD userDbo(this->pgPool);
    Employee employee = userDbo.fetchOne(employeeId);
    employee.setChip(chipDbo.fetchOne(employeeId));

    return employee;

}
VectorOf<Employee> EmployeeCRUD::fetchAll(const FetchLimit& limit)
{
    VectorOf<Employee> employees;

    ChipCRUD chipDbo(this->pgPool);
    UserCRUD userDbo(this->pgPool);
    auto users = userDbo.fetchAll(limit);
    for (auto &user : users)
    {
        Employee employee(user);
        employee.setChip(chipDbo.fetchOne(user.getId()));
        employees.push_back(employee);
    }

    return employees;
}

bool EmployeeCRUD::remove(const Employee& employee)
{
    UserCRUD userDbo(this->pgPool);
    return userDbo.remove(employee);
}

bool EmployeeCRUD::update(const Employee& employee)
{
    UserCRUD userDbo(this->pgPool);
    return userDbo.update(employee);
}
