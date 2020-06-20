#include "Controller_Impl.hpp"

using namespace demystify;
using namespace AgriBiz;
using namespace AgriBiz::controller;

template <class CRUDType>
Controller<CRUDType>::Controller(PGPoolPtr& pgPool) : dbo(pgPool)
{
}

template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::add(const pplx::task<web::json::value>& contentAsJson, FUNC jsonConverter)
{
    bool success = false;
    UserID entityId;
    
    contentAsJson.then([&](const web::json::value& entityJson){
        auto entity = jsonConverter(entityJson);
        entityId = this->dbo.add(entity);
        if (entityId != 0)
        {
            success = true;
        }
    }).get();

    auto message = JsonConversion::message(success);
    message[U("entityId")] = web::json::value::number(entityId);

    return message;
}
template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::update(const pplx::task<web::json::value>& contentAsJson, const EntityID& entityId, FUNC jsonConverter)
{
    bool success = false;

    contentAsJson.then([&](const web::json::value& entityJson){
        auto entity = jsonConverter(entityJson);
        entity.setId(entityId);
        success = this->dbo.update(entity);
    }).get();

    return JsonConversion::message(success);
}

template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::remove(const pplx::task<web::json::value>& contentAsJson, const EntityID& entityId, FUNC jsonConverter)
{
    bool success = false;

    contentAsJson.then([&](const web::json::value& entityJson){
        auto entity = jsonConverter(entityJson);
        entity.setId(entityId);
        success = this->dbo.remove(entity);
    }).get();

    return JsonConversion::message(success);

}
template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::fetchOne(const pplx::task<web::json::value>& json, const EntityID& entityId, FUNC jsonConverter)
{
    auto contentAsJson = web::json::value::object();
    auto entity = this->dbo.fetchOne(entityId);

    if (entity.getId() != 0)
    {
        contentAsJson = jsonConverter(entity);
    } else
    {
        contentAsJson = JsonConversion::message(false);
    }

    return contentAsJson;

}
template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::fetchAll(const pplx::task<web::json::value>& json, const Offset& offset, const Limit& limit, FUNC jsonConverter)
{
    auto contentAsJson = web::json::value::object();
    bool success = false;
    uint32_t count = 0;
    auto entities = this->dbo.fetchAll(limit);

    if (!entities.empty())
    {
        success = true;
        
        for (auto &entity : entities)
        {
            auto entityJson = jsonConverter(entity).serialize();
            auto userId = std::to_string(count++);
            auto entityJson1 = web::json::value::parse(entityJson);
            contentAsJson[U("entities")][U(userId)] = entityJson1;
        }
    } 
    else
    {
        contentAsJson = JsonConversion::message(success);
    }
    
    return contentAsJson;
}
