#include "AGWServer.hpp"

using namespace demystify;
using namespace subsystem::AntiGhostWorker;

std::unique_ptr<AGWServer> g_http;

void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path$

    uri_builder uri(address);
    uri.append_path(U("Demystify/AntiGhostSystem"));

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

int main()
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