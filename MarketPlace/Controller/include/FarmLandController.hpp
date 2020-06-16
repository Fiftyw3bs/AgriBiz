#ifndef FARMLAND_CONTROLLER_HPP_
#define FARMLAND_CONTROLLER_HPP_

#include "AgriBiz_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "FarmLand.hpp"
#include "JsonConversion.hpp"

using namespace demystify;

using FarmLandController = demystify::AgriBiz::controller::Controller<FarmLandCRUD>;

namespace demystify::JsonConversion
{
    using namespace subsystem::AntiGhostWorker;
    web::json::value FarmLandAsJSON(const FarmLand& FarmLand);
    FarmLand FarmLandFromJSON(const web::json::value& FarmLandJson);
} // namespace JsonConversion


#endif //FARMLAND_CONTROLLER_HPP_
