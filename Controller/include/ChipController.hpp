#ifndef CHIP_CONTROLLER_HPP_
#define CHIP_CONTROLLER_HPP_

#include "AGW_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "JsonConversion.hpp"

using namespace demystify;

using ChipController = demystify::subsystem::AntiGhostWorker::Controller<ChipCRUD>;

namespace demystify::JsonConversion
{
    using namespace subsystem::AntiGhostWorker;
    web::json::value ChipAsJSON(const Chip& chip);
    Chip ChipFromJSON(const web::json::value& ChipJson);
} // namespace JsonConversion


#endif //CHIP_CONTROLLER_HPP_
