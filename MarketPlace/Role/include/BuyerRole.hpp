#ifndef BUYER_ROLE_HPP_
#define BUYER_ROLE_HPP_

#include "IRole.hpp"

namespace demystify
{

namespace AgriBiz
{

class BuyerRole : public IRole
{
public:
    const std::string name() const
    {
        return "Buyer";
    }

};

} // namespace ASUnity

}

#endif //BUYER_ROLE_HPP_
