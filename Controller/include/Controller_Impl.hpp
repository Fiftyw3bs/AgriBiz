#ifndef CONTROLLER_IMPL_HPP_
#define CONTROLLER_IMPL_HPP_

#include "Server.hpp"
#include "AGW_Persistence.hpp"
#include "JsonConversion.hpp"

#include <type_traits>

namespace demystify
{
// Carry out validation here
namespace subsystem {
    
namespace AntiGhostWorker {
    
using ChipID = uint32_t;
using FetchLimit = uint32_t;

template <class CRUDType>
class Controller
{
public:
    Controller(PGPoolPtr& pgPool);
    template <class FUNC>
    web::json::value add(const pplx::task<web::json::value>& Json, FUNC jsonConverter);
    template <class FUNC>
    web::json::value update(const pplx::task<web::json::value>& Json, const UserID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value remove(const pplx::task<web::json::value>& Json, const UserID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value fetchOne(const UserID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value fetchAll(const FetchLimit& limit, FUNC jsonConverter);
    template <class FUNC>
    web::json::value fetchAll(const FetchLimit& limit, const pplx::task<web::json::value>& Json, FUNC jsonConverter);

protected:
    CRUDType dbo;
};

} // AntiGhostWorker

} // subsystems

}

#include "Controller_Impl.inl"

#endif //CONTROLLER_IMPL_HPP_
