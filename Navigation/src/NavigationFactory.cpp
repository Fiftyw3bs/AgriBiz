#include "NavigationFactory.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;

PointerOf<Navigator> NavigationFactory::operator()(const http_request& message, PGPoolPtr& pgPool)
{
    auto [controller, args] = Navigator::parseRequest(message);

    if (controller == "employees")
    {
        EmployeeNavigator navigator(message, pgPool);
        return MakePointerOf<EmployeeNavigator>(navigator);
    }
    else if (controller == "chips")
    {
        ChipNavigator navigator(message, pgPool);
        return MakePointerOf<ChipNavigator>(navigator);
    }
    else if (controller == "stamps")
    {
        StampNavigator navigator(message, pgPool);
        return MakePointerOf<StampNavigator>(navigator);
    }
    
    
}