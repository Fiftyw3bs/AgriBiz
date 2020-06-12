#ifndef LANDLORD_ROLE_HPP_
#define LANDLORD_ROLE_HPP_

#include "IRole.hpp"

namespace demystify
{

namespace ASUnity
{

class LandlordRole : public IRole
{
public:
    const std::string name() const
    {
        return "Landlord";
    }

};

} // namespace ASUnity

}

#endif //LANDLORD_ROLE_HPP_
