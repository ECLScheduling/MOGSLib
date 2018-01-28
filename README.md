# LoadBalancer-Framework
Repository for the LB framework project.


# Integrate with Charm++
This library can be integrated with the Charm++ runtime system following the following steps.

## Library Configurations

1) Set the library RTS to Charm++
  In order to set the library to work with Charm++ RTS, navigate to the home folder of MOGSLib and run "./build.sh charm"

## Charm++ Configurations

### Clean Instalation

1) Donwload Charm++ source from their git address.
2) Add the MOGSLib load balancer to Charm++ source.
  2.a) Copy "MOGSLib/externals/charm" files to "Charm/src/ck-ldb" folder in order to add the required files to Charm++
  2.b) Edit the Makefile_lb.sh in this folder to add the MOGSLibLB load balancer by appending "MOGSLibLB" to the COMMON_LDBS variable.
3) Run the build script in Charm++ folder to build Charm and add custom flags to the compiler in order to properly link the MOGSLib's headers.
  3.a) Add these flags to Charm++ compiler when asked by the build script: "-I/path/to/MOGSLib/include -std=c++14"

### Existing Instalation

1) Add the MOGSLib load balancer to Charm++ source.
  1.a) Copy "MOGSLib/externals/charm" files to "Charm/src/ck-ldb" folder in order to add the required files to Charm++
  1.b) Edit the Makefile_lb.sh in this folder to add the MOGSLibLB load balancer by appending "MOGSLibLB" to the COMMON_LDBS variable.
2) Edit the "Makefile" in Charm/tmp folder to add flags for the compiler.
  2.a) Add the flags "-I/path/to/MOGSLib/include -std=c++14" to the CXXFLAGS variable.
3) Build charm once more to add the load balancer properly
  3.a) Run make clean
  3.b) Run ./Makefile_lb.sh
  3.c) Run make depends
  3.d) Run make charm++
  3.e) Run make everylb