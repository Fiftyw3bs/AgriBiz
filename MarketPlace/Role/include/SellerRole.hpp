#ifndef TENANT_ROLE_HPP_
#define TENANT_ROLE_HPP_

#include "IRole.hpp"

namespace demystify
{

namespace ASUnity
{

class TenantRole : public IRole
{
public:
    const std::string name() const
    {
        return "Tenant";
    }

};

} // namespace ASUnity

}

#endif //TENANT_ROLE_HPP_
