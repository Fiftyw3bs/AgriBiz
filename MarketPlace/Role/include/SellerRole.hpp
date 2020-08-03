#ifndef SELLER_ROLE_HPP_
#define SELLER_ROLE_HPP_

#include "IRole.hpp"

namespace demystify
{

namespace AgriBiz
{

class SellerRole : public IRole
{
public:
    const std::string name() const
    {
        return "Seller";
    }

};

} // namespace ASUnity

}

#endif //SELLER_ROLE_HPP_
