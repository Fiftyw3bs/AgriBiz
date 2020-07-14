#ifndef FarmProduce_CONTROLLER_HPP_
#define FarmProduce_CONTROLLER_HPP_

#include "JsonConversion.hpp"
#include "FarmProduce.hpp"


using namespace demystify;

namespace demystify::JsonConversion
{
    using namespace AgriBiz;
    std::string FarmProduceAsJSON(const FarmProduce& FarmProduce);
    FarmProduce FarmProduceFromJSON(std::string FarmProduceJson);
} // namespace JsonConversion

#endif //FarmProduce_CONTROLLER_HPP_
