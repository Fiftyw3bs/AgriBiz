#ifndef AGW_SERVER_HPP_
#define AGW_SERVER_HPP_

#include "Server.hpp"
#include "PGPool.hpp"
#include "Models.hpp"
#include "AGW_Navigation.hpp"

#include <tuple>
#include <string>

namespace demystify
{

namespace subsystem {

using namespace persistence;

namespace AntiGhostWorker {

class AGWServer : public Server
{
public:
    AGWServer(utility::string_t url);
private:

	void handle_get(http_request message) override;
	void handle_put(http_request message) override;
	void handle_post(http_request message) override;
	void handle_delete(http_request message) override;
	void handle_patch(http_request message) override;
	PGPoolPtr pgPool;

};

} // AntiGhostWorker

} // subsystem

} // namespace demystify

#endif //AGW_SERVER_HPP_
