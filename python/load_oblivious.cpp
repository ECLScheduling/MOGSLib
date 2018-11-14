#include <iostream>
#include <string>
#include <mogslib/mogslib.h>

#include <boost/python.hpp>

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

struct Schedule {
    boost::python::list load_oblivious (
            int ntasks,
            int nPEs,
            std::string scheduler
        ) {

    SchedulerData::ntasks = ntasks;
    SchedulerData::nPEs = nPEs;
    SchedulerData::scheduler = scheduler;

    MOGSLib::RTS::set_ntasks(ntasks);
    MOGSLib::RTS::set_nPEs(nPEs);
    MOGSLib::SchedulerCollection::pick_scheduler = SchedulerData::get_scheduler;

    Index* map = MOGSLib::SchedulerCollection::schedule();
    boost::python::list list;

    for( decltype(SchedulerData::ntasks) i = 0; i < SchedulerData::ntasks; ++i )
        list.append(map[i]);

    return list;
}
};

BOOST_PYTHON_MODULE(mogslib)
{
    using namespace boost::python;
    class_<Schedule>("Schedule")
        .def("load_oblivious", &Schedule::load_oblivious)
        ;
}

