#ifndef STAMP_CONTROLLER_HPP_
#define STAMP_CONTROLLER_HPP_

#include "AGW_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "ChipController.hpp"
#include "JsonConversion.hpp"

using namespace demystify;

using StampController = demystify::subsystem::AntiGhostWorker::Controller<StampCRUD>;

namespace demystify::JsonConversion
{
    using namespace subsystem::AntiGhostWorker;
    web::json::value StampAsJSON(const Stamp& stamp);
    Stamp StampFromJSON(const web::json::value& stampJson);
} // namespace JsonConversion


#endif //STAMP_CONTROLLER_HPP_
