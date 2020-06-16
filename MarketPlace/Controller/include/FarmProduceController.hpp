#ifndef FarmProduce_CONTROLLER_HPP_
#define FarmProduce_CONTROLLER_HPP_

#include "AgriBiz_Persistence.hpp"
#include "Controller_Impl.hpp"
#include "FarmProduce.hpp"


using namespace demystify;

using FarmProduceController = demystify::AgriBiz::controller::Controller<FarmProduceCRUD>;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    web::json::value FarmProduceAsJSON(const FarmProduce& FarmProduce);
    FarmProduce FarmProduceFromJSON(const web::json::value& FarmProduceJson);
} // namespace JsonConversion

#endif //FarmProduce_CONTROLLER_HPP_
