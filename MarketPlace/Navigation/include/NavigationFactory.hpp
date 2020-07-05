#ifndef NAVIGATION_FACTORY_HPP_
#define NAVIGATION_FACTORY_HPP_

#include "OrderNavigator.hpp"
#include "Navigator.hpp"
#include "FarmProduceNavigator.hpp"
#include "OrderNavigator.hpp"
#include "MongoPark.hpp"
#include "Server.hpp"

#include <iostream>

namespace demystify
{
namespace AgriBiz
{

using namespace navigation;
using namespace persistence;

class NavigationFactory
{
public:
    PointerOf<Navigator> operator()(const http_request& message, PGPoolPtr& pgPool);
};
 
} // namespace AntiGhostWorker

} // namespace demystify


#endif //NAVIGATION_FACTORY_HPP_
