
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
#include "../redis4cpp/dataaccess.h"

#include <unistd.h>

using namespace std;

boost::mutex _print;

void PrintResult(redis4cpp::CommandBase* cmd)
{
    try
    {
        boost::mutex::scoped_lock lock(_print);
        std::cout << cmd->Result() << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << "PrintResult Exception: " << e.what() << "\n";
    }
    
    delete cmd;
}

void LoopExecute(redis4cpp::DataAccess* db)
{
    try
    {
        redis4cpp::CommandBase* cmd1 = new redis4cpp::CommandBase("SET", boost::bind(&PrintResult, _1));
        cmd1->AddArgument("nmykey");
        cmd1->AddArgument("nmyvalue");
        db->AsyncCommand(cmd1);
        
        /*
        redis4cpp::CommandBase* cmd = new redis4cpp::CommandBase("GET", boost::bind(&PrintResult, _1));
        cmd->AddArgument("nmykey");
        db->AsyncCommand(cmd);
            
        redis4cpp::CommandBase* cmd2 = new redis4cpp::CommandBase("SET", boost::bind(&PrintResult, _1));
        cmd2->AddArgument("nmykey");
        cmd2->AddArgument("nmyvalue");
        db->AsyncCommand(cmd2);
         */
        
        /*
        int count;
        while(count < 1000000) {
            db->AsyncCommand(
                new redis4cpp::CommandBase("*3\r\n$3\r\nSET\r\n$5\r\nmykey\r\n$7\r\nmyvalue\r\n",
                                        boost::bind(&PrintResult, _1)));
            db->AsyncCommand(
                new redis4cpp::CommandBase("*2\r\n$3\r\nGET\r\n$5\r\nmykey\r\n",
                    boost::bind(&PrintResult, _1)));

            usleep(100);
            count++;
        }
        */ 
    }
    catch(std::exception& e)
    {
        std::cerr << "LoopExecute Exception: " << e.what() << "\n";
    }
}



int main(int argc, char** argv) {

    try
    {            
        boost::asio::io_service io_service;
        redis4cpp::DataAccess db(io_service);

        // Create a pool of threads to run all of the io_services.
        boost::thread_group threads;

        // Create threads for read/write async operations
        for (std::size_t i = 0; i < 1; ++i)
            threads.create_thread(boost::bind(&boost::asio::io_service::run, &io_service));

        boost::thread thread(boost::bind(&LoopExecute,  &db));

        // wait for them
        threads.join_all();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}

