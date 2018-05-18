#include "stdafx.h"
#include "Server.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

extern int MAXDEPTH;
extern unsigned char pcColor;
extern unsigned char playerColor;
extern float secnds;
extern int cv;
extern int numberOfNodes;
extern int confidance;

http_listener m_listener;

void handle_put(http_request message)
{

	cout << "Received a put!" << endl;
	auto stream = message.body();
	auto buf = stream.streambuf();
	//json::value v1 = json::value::parse(stream);

	message.content_ready().wait();

	utility::stringstream_t ss1;

	auto size = buf.in_avail();
	for (int i = 0; i < size; i++)
		ss1 << (char)buf.sbumpc();
	json::value v1 = json::value::parse(ss1);

	ucout << v1[U("Board")];
	auto b = v1[U("Board")].as_array();

	string Request = utility::conversions::to_utf8string(v1[U("Request")].as_string());
	if (Request == "has_won")
	{
		unsigned char** board = new unsigned char*[BSIZE];
		for (int i = 0; i < BSIZE; ++i) {
			board[i] = new unsigned char[BSIZE];
			auto line = b[i].as_array();
			for (int j = 0; j < b.size(); j++)
				board[i][j] = line[j].as_integer();
		}
		json::value value = json::value::parse(U("{ \"Response\" : \"has_won\" }"));
		if (hasWon(board, MINIMIZEPLAYER) || hasWon(board, MAXMIZEPLAYER))
		{
			value[U("Value")] = json::value::boolean(true);
		}
		else
		{
			value[U("Value")] = json::value::boolean(false);
		}

		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
		response.set_body(value);
		message.reply(response);         // reply is done here
		return;

	} else if (Request == "pc_play")
	{
		unsigned char** board = new unsigned char*[BSIZE];
		for (int i = 0; i < BSIZE; ++i) {
			board[i] = new unsigned char[BSIZE];
			auto line = b[i].as_array();
			for (int j = 0; j < b.size(); j++)
				board[i][j] = line[j].as_integer();
		}
		unsigned char pc = v1[U("player")].as_integer();
		unsigned char player = (pc % 2) + 1;
		int dep = v1[U("depth")].as_integer();

		MAXDEPTH = dep;
		pcColor = pc;
		playerColor = player;

		Play* p = choseNextPlay(board);

		json::value value = json::value::parse(U("{ \"Response\" : \"pc_play\" }"));
		value[U("i1")] = p->move_first->i;
		value[U("j1")] = p->move_first->j;
		value[U("i2")] = p->move_second->i;
		value[U("j2")] = p->move_second->j;

		value[U("time")] = secnds;
		value[U("ramification")] = cv;
		value[U("numNodes")] = numberOfNodes;
		value[U("confidance")] = confidance;

		http_response response(status_codes::OK);
		response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
		response.set_body(value);
		message.reply(response);         // reply is done here
		return;
	}

	http_response response(status_codes::OK);
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.set_body(v1);
	message.reply(response);         // reply is done here
};

void handle_options(http_request request)
{
	http_response response(status_codes::OK);
	response.headers().add(U("Allow"), U("GET, PUT, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.headers().add(U("Access-Control-Allow-Methods"), U("GET, PUT, OPTIONS"));
	response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
	request.reply(response);
}

void on_initialize(const string_t& address)
{
	// Build our listener's URI from the configured address and the hard-coded path "blackjack/dealer"

	uri_builder uri(address);

	utility::string_t addr = uri.to_uri().to_string();
	m_listener = http_listener(addr);
	m_listener.support(methods::PUT, std::bind(&handle_put, std::placeholders::_1));
	m_listener.support(methods::OPTIONS, handle_options);
	m_listener.open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

	return;
}

void on_shutdown()
{
	m_listener.close().wait();
	return;
}

void initServer()
{
	utility::string_t port = U("34568");

	utility::string_t address = U("http://localhost:");
	address.append(port);

	on_initialize(address);
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	on_shutdown();
}