# MOGSLib Framework
MOGSLib is a library whose name stands for *Metaprogramming-Oriented Global Schedulers Library*. The goal of this library is to provide portability and reuse for scheduling components in different runtime systems (RTS). Moreover, as system-independent components, the schedulers are packed as header-only files within this repository alongside structures, algorithms, and adapters to connect existing runtime systems to the scheduler components.

The portable schedulers' implementation relies on adaptor types at compilation time to link the input data from the RTS to the scheduling component. Seemingly complicated at first, the process of attaching this library's components to an RTS can be easily achieved after the user understands the basic principles of the library.

The main folder of this project is the include folder. The subfolders within serve different purposes and are organized as follows:

## Adaptors
This directory contains all the concrete adaptors that syntactically unify the access to the scheduler inputs from different runtime systems. Each subfolder in this directory represents a different supported RTS.

## Algorithms
Scheduling components use a set of algorithms to compute a schedule. These algorithms can, sometimes, be reused in other policies. As such, this folder is designed to contain algorithms written in a reusable fashion that can used by scheduler implementations. Each subfolder in this directory packs the algorithms of a single scheduling strategy.

## Interfaces
This directory contains all the abstraction interfaces that are used in the library. This is a centralized point to express different concepts in the library such as the input adaptor and the scheduling strategy. Subdirectories in this folder express different entity categories in the library.

## Rts
This directory is used by the code that connects MOGSLib's code to the target RTS. The contents in this folder change depending on the target RTS, the scheduling strategy that will be used in the target RTS and other variables defined at pre-compilation time.

## Strategies
This directory contains all the portable strategies that this library packs. Each subdirectory is meant to house a single strategy that can be used in the supported runtime systems.

## System
This folder contains configuration variables and metaprogramming aspects that will guide the compilation process of the library. These files helps defining types, debuggers and other traits in the library.


## MOGSLib Supported Systems
MOGSLib currently has adapters for the following runtime systems:

* **Charm++**
* **OpenMP** (libgomp)

The process of creating an adapter to a new runtime system revolves around implementing the adaptor interface methods. The new concrete adaptor must then use the system-specific structures of the RTS to provide the existing schedulers with data under the abstract adapter interface.

## MOGSLib Scheduler Policies
MOGSLib currently has the following scheduler implementations:

* **Greedy Strategy** : The greedy load balancer implementation originally found on the Charm++ system.
* **BinLPT** : A greedy load-aware strategy originally implemented on OpenMP to provide a smart task mapping to loop schedulers.

# MOGSLib Integration

In order to ease the configuration of MOGSLib and provide an easier way to attach the library into the RTS, a script has been made to configure the library to portray a single strategy to a target RTS. The script can be found in the scripts directory under the name `configure.py`. Make sure to run this script before compiling the library alongside the RTS in the specific steps to integrate the library in order to link the desired scheduling component to the target RTS through the desired adapter.

## Charm++
MOGSLib can be integrated with the Charm++ runtime system through the following steps.

### Library Configurations

1. Set the library RTS to Charm++ though the configure script. In order to set the library to work with Charm++ using the greedy scheduler, for example, run the following command: `scripts/configure.py -s greedy -a default -rts charm`.

### Charm++ Configurations

#### Clean Installation

1. Download Charm++ source from their repository.
2. Add the MOGSLib load balancer to Charm++ source.
    1. Copy `MOGSLib/externals/charm` files to `Charm/src/ck-ldb` folder in order to add the required files to Charm++.
    2. Edit `the Makefile_lb.sh` in this folder to add the MOGSLibLB load balancer by appending "MOGSLibLB" to the `COMMON_LDBS` variable.
3. Run the build script in Charm++ folder to build Charm and add custom flags to the compiler in order to properly link the MOGSLib's headers.
    1. Add these flags to Charm++ compiler when asked by the build script: `-I/path/to/MOGSLib/include -std=c++14`.

#### Existing Installation

1. Add the MOGSLib load balancer to Charm++ source.
    1. Copy `MOGSLib/externals/charm` files to `Charm/src/ck-ldb` folder in order to add the required files to Charm++
    2. Edit `Makefile_lb.sh` in this folder to add the MOGSLibLB load balancer by appending "MOGSLibLB" to the `COMMON_LDBS` variable.
2. Edit the `Makefile` in the `Charm/tmp` folder to add flags for the compiler.
    1. Add the flags `-I/path/to/MOGSLib/include -std=c++14` to the `CXXFLAGS` variable.
3. Build Charm++ once more to add the load balancer properly.
    1. Run `make clean`
    2. Run `./Makefile_lb.sh`
    3. Run `make depends`
    4. Run `make charm++`
    5. Run ``make everylb``

## OpenMP through libgomp

In this early development stage, the only way to integrate MOGSLib into OpenMP is using a modified version of libGOMP. This version can be found packed in the contrib folder.

## Library Configurations

1. Set the library RTS to OpenMP++ though the configure script. In order to set the library to work with OpenMP++ RTS using the greedy scheduler, for example, run the following command: `scripts/configure.py -s greedy -a default -rts openmp`

## OpenMP application Configurations

1. Unpack the `enhanced-libgomp.tar` file in the `contrib` folder
2. In your OpenMP application makefile or compilation script, add the enhanced-libgomp library path and libraries to the compiler flags as following: `-L path/to/enhanced-libgomp/src/libgomp/build/.libs -lgomp -lm`
3. Also in your OpenMP application makefile or compilation script, add the MOGSLib include path to the include directories as following: `-I path/to/MOGSLib/include -std=c++14`
4. Change the OpenMP scheduling flag in the for loop to "schedule(runtime)"
5. Compile the application
6. Set the OpenMP `OMP_SCHEDULE` system variable to `mogslib` in a terminal or bash script that will invoke the compiled application as following: `export OMP_SCHEDULE=mogslib`
7. Run the application

The actual scheduling policy that will be used to schedule the parallel segment is the same as the one passed to the MOGSLib configure script.
