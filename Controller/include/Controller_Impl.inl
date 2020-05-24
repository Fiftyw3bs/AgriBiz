#include "Controller_Impl.hpp"

using namespace demystify;
using namespace persistence;
using namespace ::subsystem::AntiGhostWorker;

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
web::json::value Controller<CRUDType>::update(const pplx::task<web::json::value>& contentAsJson, const UserID& entityId, FUNC jsonConverter)
{
    bool success = false;

    if constexpr(std::is_same_v<CRUDType, ChipCRUD>)
    {
        contentAsJson.then([&](const web::json::value& chipJson){
            if (chipJson.has_field("update_type"))
            {
                auto userId = chipJson.at("userId").as_integer();
                auto chipId = chipJson.at("chipId").as_integer();
                auto action = chipJson.at("update_type").as_string();

                if (action == "revoke")
                {
                    if (auto retVal = this->dbo.fetchOne(userId); retVal.isAssigned())
                    {
                        success = this->dbo.revoke(userId, chipId);
                    }
                }
                else if (action == "assign")
                {
                    if (auto retVal = this->dbo.fetchOne(userId); !retVal.isAssigned())
                    {
                        success = this->dbo.assign(userId, chipId);
                    }
                }
                else
                {
                    
                }                
            }
        }).get();
    }
    else
    {
        contentAsJson.then([&](const web::json::value& entityJson){
            auto entity = jsonConverter(entityJson);
            entity.setId(entityId);
            success = this->dbo.update(entity);
        }).get();
    }


    return JsonConversion::message(success);
}

template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::remove(const pplx::task<web::json::value>& contentAsJson, const UserID& entityId, FUNC jsonConverter)
{
    bool success = false;

    contentAsJson.then([&](const web::json::value& entityJson){
        if constexpr(std::is_same_v<CRUDType, StampCRUD>)
        {
            if (entityId == 0)
            {
                if (!entityJson.at("chip").is_null())
                {
                    auto chip = jsonConverter(entityJson.at("chip"));
                    success = this->dbo.removeAllByChip(chip);
                }
            }
            else
            {
                success = this->dbo.remove(entityId);
            }
        }
        else
        {
            auto entity = jsonConverter(entityJson);
            entity.setId(entityId);
            success = this->dbo.remove(entity);
        }
    }).get();

    return JsonConversion::message(success);

}
template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::fetchOne(const UserID& entityId, FUNC jsonConverter)
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
web::json::value Controller<CRUDType>::fetchAll(const FetchLimit& limit, FUNC jsonConverter)
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

template <class CRUDType>
template <class FUNC>
web::json::value Controller<CRUDType>::fetchAll(const FetchLimit& limit, const pplx::task<web::json::value>& Json, FUNC jsonConverter)
{
    auto contentAsJson = web::json::value::object();
    VectorOf<Stamp> stamps;
    uint32_t count = 0;

    Json.then([&](const web::json::value& entityJson){
        if constexpr(std::is_same_v<CRUDType, StampCRUD>)
        {
            if (auto chipJson = entityJson.at("chip"); !chipJson.is_null())
            {
                if (entityJson.at("startDate").is_null())
                {
                    auto chip = jsonConverter.second(chipJson);
                    stamps = this->dbo.fetchByChip(chip);
                }
                else
                {
                    auto chip = jsonConverter.second(chipJson);
                    auto startDate = JsonConversion::DatableFromJSON(entityJson.at("startDate"));
                    auto endDate = JsonConversion::DatableFromJSON(entityJson.at("endDate"));
                    stamps = this->dbo.fetchByStampTime(chip, startDate, endDate);
                }
            }
            else
            {
                auto chip = jsonConverter.second(chipJson);
                auto startDate = JsonConversion::DatableFromJSON(entityJson.at("startDate"));
                auto endDate = JsonConversion::DatableFromJSON(entityJson.at("endDate"));
                stamps = this->dbo.fetchAllByStampTime(startDate, endDate);
            }
        }

        for (auto &stamp : stamps)
        {
            contentAsJson[U(std::to_string(count))] = jsonConverter.first(stamp);
            ++count;
        }
        
    }).get();
    
    return contentAsJson;
}
