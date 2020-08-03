#ifndef Admin_ROLE_HPP_
#define Admin_ROLE_HPP_

#include "IRole.hpp"

namespace demystify
{

namespace AgriBiz
{

class AdminRole : public IRole
{
public:
    const std::string name() const
    {
        return "Admin";
    }

};

} // namespace ASUnity

}

#endif //Admin_ROLE_HPP_
