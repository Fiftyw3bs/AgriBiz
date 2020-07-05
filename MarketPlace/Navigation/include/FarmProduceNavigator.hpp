#ifndef FARMPRODUCE_NAVIGATOR_HPP_
#define FARMPRODUCE_NAVIGATOR_HPP_

#include "Server.hpp"
#include "PGPool.hpp"
#include "Models.hpp"
#include "Navigator.hpp"
#include "FarmProduceController.hpp"

#include <string>

namespace demystify
{
namespace AntiGhostWorker
{

using namespace navigation;
using namespace persistence;

using ControllerType = std::string;
using Action = std::string;

class FarmProduceNavigator : public Navigator
{
public:
    FarmProduceNavigator(
        const http_request& message
    );
    virtual web::json::value process(pplx::task<web::json::value> content);

};

} // namespace AntiGhostWorker

} // demystify


#endif //FARMPRODUCE_NAVIGATOR_HPP_
