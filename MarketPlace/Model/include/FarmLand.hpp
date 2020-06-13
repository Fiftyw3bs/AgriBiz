#ifndef FARM_LAND_HPP_
#define FARM_LAND_HPP_

#include "Models.hpp"
#include "FarmProduce.hpp"

namespace demystify
{
namespace AgriBiz
{
    
class FarmLand : public Identifiable, public Subscribable<FarmProduce>
{
};

} // namespace AgriBiz
    
} // namespace demystify

#endif //FARM_LAND_HPP_
