#include <iostream>
#include "gtest/gtest.h"

#include "stdafx.h"
#include "AGWServer.hpp"

namespace demystify
{
namespace unittest
{

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace subsystem::AntiGhostWorker;

std::unique_ptr<AGWServer> g_http;

void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path$

    uri_builder uri(address);
    uri.append_path(U("Demystify"));

    auto addr = uri.to_uri().to_string();
        g_http = std::unique_ptr<AGWServer>(new AGWServer(addr));
        g_http->open().wait();
    
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
        g_http->close().wait();
    return;
}

TEST(Subsystems_AntiGhostWorker, TestInitialize)
{
    utility::string_t port = U("8123");
    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();

}
// TEST(AGWSubsystems_Server, TestInitialize)
// {
//     tChip.setChipToken(1092332);
//     AddChip tAddCHip;
//     ASSERT_TRUE(tAddCHip(tChip, myPool));
// }

} // namespace unittest
} // namespace demystify