
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"
#include <cstdlib>
#include "boost/bind.hpp"
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>

#include "../redis4cpp/interface.h"
#include "../redis4cpp/connection.h"

#include <unistd.h>

using namespace std;

boost::mutex _print;

void PrintResult(redis4cpp::CommandBasePtr cmd)
{
    boost::mutex::scoped_lock lock(_print);
    std::cout << cmd->Result() << std::endl;
}

void LoopExecute(redis4cpp::Connection* conn)
{
    while(true) {
        //boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        conn->AsyncCommand(
            new redis4cpp::CommandBase("*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$7\r\nmyvalue\r\n",
                                    boost::bind(&PrintResult, _1)));
        conn->AsyncCommand(
            new redis4cpp::CommandBase("*2\r\n$3\r\nGET\r\n$5\r\nmykey\r\n",
                boost::bind(&PrintResult, _1)));
        
        usleep(10);
    }
}



int main(int argc, char** argv) {

  try
  {            
    boost::asio::io_service io_service;
    redis4cpp::Connection conn(io_service);

    // Create a pool of threads to run all of the io_services.
    boost::thread_group threads;

    // Create threads for read/write async operations
    for (std::size_t i = 0; i < 3; ++i)
        threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));

    boost::thread thread(boost::bind(&LoopExecute,  &conn));

    // wait for them
    threads.join_all();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
  
    //redis4cpp::Connection 
    //redis4cpp::CommandBase cmd1("*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$7\r\nmyvalue\r\n");
   // redis4cpp::CommandBase cmd2("*23\r\n$3\r\nSET\r\n$5\r\nmykey\r\n");
    //return 0;
}

