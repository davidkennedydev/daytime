#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string makeDayTimeString() {
	using namespace std;
	time_t now = time(0);
	return ctime(&now);
}

main() {
	try {
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		while(true) {
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string message = makeDayTimeString();
			
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
}
