#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main()
{
    try
    {
        // Create an I/O context
        boost::asio::io_context io_context;

        // Create a TCP acceptor
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 25000));

        while (true)
        {
            std::cout << "waiting" << std::endl;
            // Wait for a connection
            tcp::socket socket(io_context);
            std::cout << "waiting" << std::endl;
            acceptor.accept(socket);

            std::cout << "Accepted connection from " << socket.remote_endpoint() << std::endl;

            // Handle the connection
            boost::system::error_code error;
            
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\0");
            std::string data{
                std::istreambuf_iterator<char>(&buffer), 
                std::istreambuf_iterator<char>() 
            };
            if (error == boost::asio::error::eof)
            {
                std::cout << "Connection closed by peer" << std::endl;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }
            else
            {
                std::cout << "Received: " << data << std::endl;
                // Send a response
                std::string response = "Hello, client!";
                boost::asio::write(socket, boost::asio::buffer(response));
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}