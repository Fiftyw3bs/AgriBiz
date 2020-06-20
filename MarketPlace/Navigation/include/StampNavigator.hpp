#ifndef STAMP_NAVIGATOR_HPP_
#define STAMP_NAVIGATOR_HPP_

#include "Server.hpp"
#include "PGPool.hpp"
#include "Models.hpp"
#include "Navigator.hpp"
#include "StampController.hpp"
#include "ChipController.hpp"

#include <string>
#include <utility>

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

class StampNavigator : public Navigator
{
public:
    StampNavigator(
        const http_request& message,
        PGPoolPtr& pgPool
    );
    virtual web::json::value process(pplx::task<web::json::value> content);

};

} // namespace AntiGhostWorker

} // namespace subsystem
    
} // demystify


#endif //STAMP_NAVIGATOR_HPP_
