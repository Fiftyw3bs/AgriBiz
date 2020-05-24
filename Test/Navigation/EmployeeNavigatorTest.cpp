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

class NavigationTester
{
private:
    PointerOf<Navigator> navigator;
    pplx::task<web::json::value> content;

public:
    NavigationTester(web::http::http_request request, PGPoolPtr pgPool) : content(request.extract_json())
    {
        NavigationFactory factory;
        this->navigator = factory(request, pgPool);
    }

    web::json::value processTest()
    {
        auto retVal = navigator->process(pplx::create_task([&](){
            return this->content;
        }));

        return retVal;
    }
};

PGPoolPtr pgPool = MakePointerOf<PGPool>(DBInfo());

web::json::value prepareTest(const web::http::method& method, const web::uri& uri, web::json::value content)
{
    web::http::http_request request(method);
    request.set_request_uri(uri);
    request.set_body(content);

    NavigationTester navigator(request, pgPool);
    return navigator.processTest();
}


TEST(AntiGhostWorker_Navigation, EmployeeNavigation_Test)
{
    auto userId = randomFrom(0, 999999);
    auto userId_s = std::to_string(userId);

    auto content = web::json::value::parse(
        "{\n    \"foundational\" : {\n        \"contactDetails\" : {\n            \"address\" : \"Test Address1\",\n            \"city\" : \"Test City\",\n            \"state\" : \"Test state\",\n            \"phone\" : 41546842,\n            \"firstName\" : \"Test Firstname\",\n            \"middleName\" : \"Test MiddleName\",\n            \"lastName\" : \"Test Lastname\",\n            \"postalCode\" : 34323\n        },\n        \"username\" : \"femisko\",\n        \"enabled\" : true,\n        \"lastSeen\" : {\n            \"timeString\" : \"2019-10-10 12:30:30\"\n        },\n        \"wallet\" : {\n            \"balance\" : 1337\n        },\n        \"email\" : \"testEmail@gg.com\",\n        \"id\" : {\n            \"id\" : "+userId_s+"\n        }\n    },\n    \"chip\" : {\n        \"chipToken\" : 1337,\n        \"chipId\" : 10\n    }\n}\n"
    );

    // Test POST
    auto retVal = prepareTest("POST", "employees", content);

    ASSERT_TRUE(retVal.at("successful").as_bool() == true);

    // Test GET
    retVal = prepareTest("GET", "employees/" + userId_s, content);
    ASSERT_TRUE(retVal.at("foundational").at("username").as_string() == "femisko");

    // Test PATCH
    content[U("foundational")]["username"] = web::json::value::string("junisko");
    retVal = prepareTest("PATCH", "employees/" + userId_s, content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == true);

    retVal = prepareTest("GET", "employees/" + userId_s, content);
    ASSERT_TRUE(retVal.at("foundational").at("username").as_string() == "junisko");

    // Test DELETE
    retVal = prepareTest("DELETE", "employees/" + userId_s, content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == true);

    retVal = prepareTest("GET", "employees/" + userId_s, content);
    ASSERT_TRUE(retVal.at("successful").as_bool() == false);
}

} // namespace unittest
} // namespace demystify