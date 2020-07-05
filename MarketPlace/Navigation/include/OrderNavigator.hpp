#ifndef ORDER_NAVIGATOR_HPP_
#define ORDER_NAVIGATOR_HPP_

#include "Server.hpp"
#include "PGPool.hpp"
#include "Models.hpp"
#include "Navigator.hpp"
#include "OrderController.hpp"
#include "ChipController.hpp"

#include <string>
#include <utility>

namespace demystify
{
namespace AgriBiz
{

using namespace navigation;
using namespace persistence;

using ControllerType = std::string;
using Action = std::string;

class OrderNavigator : public Navigator
{
public:
    OrderNavigator(
        const http_request& message
    );
    virtual web::json::value process(pplx::task<web::json::value> content);

};

} // namespace AntiGhostWorker

} // demystify


#endif //ORDER_NAVIGATOR_HPP_
