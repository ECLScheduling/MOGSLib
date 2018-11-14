#include <iostream>
#include <string>
#include <mogslib/mogslib.h>

//#include <boost/python/class.hpp>
//#include <boost/python/module.hpp>
//#include <boost/python/def.hpp>

using Index = MOGSLib::Index;

namespace SchedulerData {
    Index ntasks;
    Index nPEs;
    std::string scheduler;

    std::string get_scheduler () {
        return scheduler;
    }
    void set_scheduler (std::string name) {
        scheduler = name;
    }
}

int main ( int argc, char* argv[] ) {

    // Simple example taking two parameters from the command line
    if(argc < 3) {
        std::cerr << "Usage: " << argv[0] << " ntasks nPEs scheduler" << std::endl;
        return 1;
    }

    SchedulerData::ntasks = std::stoi(argv[1]);
    SchedulerData::nPEs = std::stoi(argv[2]);
    SchedulerData::set_scheduler(argv[3]);

    MOGSLib::RTS::set_ntasks(SchedulerData::ntasks);
    MOGSLib::RTS::set_nPEs(SchedulerData::nPEs);
    MOGSLib::SchedulerCollection::pick_scheduler = SchedulerData::get_scheduler;

    Index* map = MOGSLib::SchedulerCollection::schedule();

    for( decltype(SchedulerData::ntasks) i = 0; i < SchedulerData::ntasks; ++i ) {
        std::cout << "Task " << i << " is mapped to PE " << map[i] << std::endl;
    }

    return 0;
}
