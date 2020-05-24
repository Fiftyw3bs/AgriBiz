#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "gtest/gtest.h"

#include "Server.hpp"
#include "AGW_Navigation.hpp"

namespace demystify
{
namespace unittest
{

using namespace demystify::subsystem::AntiGhostWorker;
extern web::json::value prepareTest(const web::http::method& method, const web::uri& uri, web::json::value content);

TEST(AntiGhostWorker_Navigation, StampNavigation_Test)
{
    auto chipToken = randomFrom(0, 999999);
    auto chipId = randomFrom(0, 999);
    auto chipToken_s = std::to_string(chipToken);
    auto chipId_s = std::to_string(chipId);

    auto content = web::json::value::parse(
        "{ \n    \"chip\" : {\n        \"chipToken\" : "+chipToken_s+",\n        \"chipId\" : 184\n    },\n    \"stampId\" : {\n        \"id\" : 12\n    },\n    \"stampTime\" : {\n        \"timeString\" : \"2019-10-10 12:30:30\"\n    },\n    \"stampType\" : \"ARIVAL\"\n}\n"
    );

    // Test POST
    auto retVal = prepareTest("POST", "stamps", content);
    auto stampId = retVal.at("entityId").as_integer();

    ASSERT_TRUE(retVal.at("successful").as_bool() == true);


    // Test GET
    retVal = prepareTest("GET", "stamps/" + std::to_string(stampId), content); // DateTime correction to be made
    ASSERT_TRUE(retVal.at("stampTime").at("timeString").as_string() == "2019-10-10 14:30:30");
    
    // Test PATCH
    content[U("stampType")] = web::json::value::string("DEPARTURE");
    retVal = prepareTest("PATCH", "stamps/" + std::to_string(stampId), content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == true);
    // verify
    retVal = prepareTest("GET", "stamps/" + std::to_string(stampId), content); // DateTime correction to be made
    auto stamp = JsonConversion::StampFromJSON(retVal);
    ASSERT_TRUE(retVal.at("stampType").as_string() == web::json::value::string("DEPARTURE").as_string());

    // Test DELETE
    retVal = prepareTest("DELETE", "stamps/" + std::to_string(stampId), content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == true);
    // verify
    retVal = prepareTest("GET", "stamps/" + std::to_string(stampId), content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == false);
}

} // namespace unittest
} // namespace demystify