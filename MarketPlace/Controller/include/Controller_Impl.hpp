#ifndef CONTROLLER_IMPL_HPP_
#define CONTROLLER_IMPL_HPP_

#include "AgriBiz_Persistence.hpp"
#include "JsonConversion.hpp"

#include <type_traits>

namespace demystify
{
// Carry out validation here
namespace AgriBiz {
    
namespace controller {

using namespace persistence;

using EntityID = uint32_t;

template <class CRUDType>
class Controller
{
public:
    Controller(PGPoolPtr& pgPool);
    template <class FUNC>
    web::json::value add(const pplx::task<web::json::value>& Json, FUNC jsonConverter);
    template <class FUNC>
    web::json::value update(const pplx::task<web::json::value>& Json, const EntityID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value remove(const pplx::task<web::json::value>& Json, const EntityID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value fetchOne(const pplx::task<web::json::value>& Json, const EntityID& Id, FUNC jsonConverter);
    template <class FUNC>
    web::json::value fetchAll(const pplx::task<web::json::value>& Json, const Offset& offset, const Limit& limit, FUNC jsonConverter);

protected:
    CRUDType dbo;
};

} // AntiGhostWorker

} // subsystems

}

#include "Controller_Impl.inl"

#endif //CONTROLLER_IMPL_HPP_
