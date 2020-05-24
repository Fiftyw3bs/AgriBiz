#include "AGWServer.hpp"

#include <iostream>

#include "AGW_Controller.hpp"
#include "AuthController.hpp"
#include "JsonConversion.hpp"

using namespace demystify;
using namespace std;
using namespace pplx;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace demystify::subsystem::AntiGhostWorker;
using namespace persistence;
using namespace controller;

AGWServer::AGWServer(utility::string_t url) : Server(url)
{
	this->pgPool = std::make_shared<PGPool>(DBInfo());
}

void AGWServer::handle_get(http_request message)
{
	auto task1 = create_task([=]() {
		
		NavigationFactory navFact;
		auto nav = navFact(message, this->pgPool);

		message.reply(status_codes::OK, nav->process(message.extract_json()));
	})
	.wait();
};

void AGWServer::handle_post(http_request message)
{
	auto task1 = create_task([=]() {
		
		NavigationFactory navFact;
		auto nav = navFact(message, this->pgPool);

		message.reply(status_codes::OK, nav->process(message.extract_json()));
	})
	.wait();
};

void AGWServer::handle_delete(http_request message)
{
	auto task1 = create_task([=]() {
		
		NavigationFactory navFact;
		auto nav = navFact(message, this->pgPool);

		message.reply(status_codes::OK, nav->process(message.extract_json()));
	})
	.wait();
}

void AGWServer::handle_put(http_request message)
{
	auto task1 = create_task([=]() {
		
		NavigationFactory navFact;
		auto nav = navFact(message, this->pgPool);

		message.reply(status_codes::OK, nav->process(message.extract_json()));
	})
	.wait();
};

void AGWServer::handle_patch(http_request message)
{
	auto task1 = create_task([=]() {
		
		NavigationFactory navFact;
		auto nav = navFact(message, this->pgPool);

		message.reply(status_codes::OK, nav->process(message.extract_json()));
	})
	.wait();
};
