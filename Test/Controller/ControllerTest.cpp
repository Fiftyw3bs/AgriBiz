#include <iostream>
#include "gtest/gtest.h"

#include "Controller.hpp"
#include "EmployeeController.hpp"
#include "ChipController.hpp"
#include "JsonConversion.hpp"
#include "PGPool.hpp"
#include "Wallet.hpp"

#include <random>

#include "stdafx.h"

namespace demystify
{
namespace unittest
{

using namespace web;
using namespace persistence;
using namespace subsystem::AntiGhostWorker;
using namespace utilities;

auto pgPool = MakePointerOf<PGPool>(DBInfo());

UserID userId = 0;
ChipID chipId = 0;
auto maxCount = 100;

TEST(AGW_Controller, Employee_ControllerTest)
{
    auto randi = randomFrom(0, 1000);
    auto randVal = std::to_string(randi);

    utility::string_t jsonContent{
    "\n{\n    \"foundational\" : {\n        \"contactDetails\" : {\n            \"address\" : \"Test Address1\",\n            \"city\" : \"Test City1\",\n            \"state\" : \"Test state1\",\n            \"phone\" : 222222,\n            \"firstName\" : \"Test Firstname1\",\n            \"middleName\" : \"Test MiddleName1\",\n            \"lastName\" : \"Test Lastname1\",\n            \"postalCode\" : 311111\n        },\n        \"username\" : \"testUsername1\",\n        \"enabled\" : false,\n        \"lastSeen\" : {\n            \"timeString\" : \"2019-10-10 12:30:30\"\n        },\n        \"wallet\" : {\n            \"balance\" : 1337331\n        },\n        \"email\" : \"testEmail@gg12.com\",\n        \"id\" : {\n            \"id\" : "+randVal+"\n        }\n    },\n    \"chip\" : {\n        \"chipToken\" : 1337,\n        \"chipId\" : 10\n    }\n}\n"};

    auto requestt = web::json::value::parse(jsonContent);

    auto controller = Controller<EmployeeCRUD>(pgPool);
    auto retVal = controller.add(pplx::create_task([=](){
        return requestt;
    }), JsonConversion::EmployeeFromJSON);

    ASSERT_TRUE(retVal.at("successful").as_bool());

    retVal = controller.fetchOne(JsonConversion::IdentifiableFromJSON(requestt.at("foundational").at("id")), JsonConversion::EmployeeAsJSON);

    ASSERT_TRUE((retVal.at("foundational").at("contactDetails").at("firstName").as_string()
                ==
                requestt.at("foundational").at("contactDetails").at("firstName").as_string())
    );

    retVal = controller.fetchAll(maxCount, JsonConversion::EmployeeAsJSON);
    // std::cout << retVal.at("entities").serialize() << std::endl;


    userId = retVal.at("entities").at(std::to_string(randomFrom(0, maxCount))).at("foundational").at("id").at("id").as_integer();
}


TEST(AGW_Controller, Chip_AddTest)
{
    auto randVal = std::to_string(randomFrom(0, 1000));

    utility::string_t jsonContent{
    "\n{\n  \"chipToken\" : "+randVal+"\n}\n"};

    auto requestt = web::json::value::parse(jsonContent);


    auto controller = Controller<ChipCRUD>(pgPool);
    auto retVal = controller.add(pplx::create_task([=](){
        return requestt;
    }), JsonConversion::ChipFromJSON);

    ASSERT_TRUE(retVal.at("successful").as_bool());

    retVal = controller.fetchAll(maxCount, JsonConversion::ChipAsJSON);
    // std::cout << retVal.at("entities").serialize() << std::endl;

    chipId = retVal.at("entities").at(std::to_string(randomFrom(0, maxCount))).at("chipId").as_integer();
}

TEST(AGW_Controller, Chip_Assign_Revoke_Test)
{
    auto randVal = std::to_string(userId);
    auto randChip = std::to_string(chipId);

    utility::string_t jsonContent{
    "{\n    \"update_type\" : \"assign\",\n    \"chipId\" : "+randChip+",\n    \"userId\" : "+randVal+"\n}"};

    auto requestt = web::json::value::parse(jsonContent);

    auto controller = Controller<ChipCRUD>(pgPool);
    auto retVal = controller.update(pplx::create_task([=](){
        return requestt;
    }), userId, JsonConversion::ChipFromJSON);

    ASSERT_TRUE(retVal.at("successful").as_bool());

    jsonContent = {
    "{\n    \"update_type\" : \"revoke\",\n    \"chipId\" : "+randChip+",\n    \"userId\" : "+randVal+"\n}"};

    retVal = controller.update(pplx::create_task([=](){
        return web::json::value::parse(jsonContent);
    }), userId, JsonConversion::ChipFromJSON);

    ASSERT_TRUE(retVal.at("successful").as_bool());
}


}
}