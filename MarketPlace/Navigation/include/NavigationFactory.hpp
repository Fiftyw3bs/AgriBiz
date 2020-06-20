#ifndef NAVIGATION_FACTORY_HPP_
#define NAVIGATION_FACTORY_HPP_

#include "ChipNavigator.hpp"
#include "Navigator.hpp"
#include "EmployeeNavigator.hpp"
#include "StampNavigator.hpp"
#include "PGPool.hpp"
#include "Server.hpp"

#include <iostream>

namespace demystify
{
namespace subsystem
{
namespace AntiGhostWorker
{

using namespace navigation;
using namespace persistence;

class NavigationFactory
{
public:
    PointerOf<Navigator> operator()(const http_request& message, PGPoolPtr& pgPool);
};
 
} // namespace AntiGhostWorker

} // namespace subsystem
    
} // namespace demystify


#endif //NAVIGATION_FACTORY_HPP_
