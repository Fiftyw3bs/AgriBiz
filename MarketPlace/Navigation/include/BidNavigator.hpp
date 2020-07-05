#ifndef BID_NAVIGATOR_HPP_
#define BID_NAVIGATOR_HPP_

#include "Server.hpp"
#include "MongoPark.hpp"
#include "Models.hpp"
#include "Navigator.hpp"
#include "BidController.hpp"

#include <string>

namespace demystify
{
namespace AgriBiz
{

using namespace navigation;
using namespace persistence;

using ControllerType = std::string;
using Action = std::string;

class BidNavigator : public Navigator
{
public:
    BidNavigator(
        const http_request& message
    );
    virtual web::json::value process(pplx::task<web::json::value> content);

};

} // namespace AntiGhostWorker

} // demystify


#endif //BID_NAVIGATOR_HPP_
