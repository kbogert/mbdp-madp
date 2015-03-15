# Extending the MADP Toolbox #

# Background #

The original [MADP toolbox](http://staff.science.uva.nl/~faolieho/index.php?fuseaction=software.madp#download) runs in Linux only.  Adding to the toolbox means downloading the source code, adding your own code in the proper directories, modifying the build configuration to include your added code, then finally building the new system with your added code.

This document summarizes the process above in just a few steps.  But, before we begin, it's assumed you have already downloaded the source code and unpacked it to a directory of your choice.

Without yet adding any new code, configuring and building the system is as simple as:

```
# ./configure
# make
# make install [optional]
```


# Let's Begin! #

Let's consider our implementation of the MBDP planning algorithm extending the MADP toolbox as a running example.  Let's say we have three files we want to add:

```
//The algorithm:
src/planning/MBDPPlanner.h
src/planning/MBDPPlanner.cpp

//The sample code which also produces an executable:
src/examples/MBDP.cpp
```

1. The first thing we need to do to add our planning code is to edit the **Makefile.am** used by _Automake_ to build the code.  Because this is part of the Planning system we edit:

**src/planning/Makefile.am**

2. Look for the section labeled **PLANNING\_CPPFILES**, and add **MBDPPlanner.cpp**:

**Note:** No need to add **MBDPPlanner.h** to the **PLANNING\_HFILES** planning files section because it has the same name as our **MBDPPlanner.cpp** and is captured by **$(PLANNING\_CPPFILES:.cpp=.h)**

3. We're pretty much done with the planning section.  Now let's look at **src/example/MBDP.cpp**.  Edit:

**src/examples/Makefile.am**  (again the file used by Automake)

Add the program prefix name (**MBDP**) to the **PROGRAMS\_NORMAL** variable, just like all the others.

4. Now use the other "Build" sections of the other programs to build your own Build section.

```
# Build MBDP
MBDP_SOURCES = MBDP.cpp
MBDP_LDADD = $(MADPLIBS_NORMAL) $(MADP_LD)
MBDP_LDFLAGS = $(AM_LDFLAGS) 
MBDP_DEPENDENCIES = $(MADPLIBS_NORMAL)
MBDP_CPPFLAGS= $(AM_CPPFLAGS) $(CPP_OPTIMIZATION_FLAGS)
MBDP_CXXFLAGS=
MBDP_CFLAGS=
```

5. The final step is to actually build it, putting it all together.  In order to do that we have to get _Autoconf_ to reconfigure the MakefileS, then we just have to "make" the program so that Automake can use our new Makefile.am.

First make sure you have Automake and libtool installed, i.e.:

```
sudo apt-get install automake libtool
```

Also you may have to create an m4 directory:

```
mkdir m4
```

In the **root** directory of your downloaded system, i.e. **~/downloads/madp-0.2/**  (as an example) do the following

```
autoreconf --install
make
```

6. That's it!  Now throughout your development of those 3 files we are working with, we just have to run "make" in the respective directories (i.e., src/planning/  or src/examples/) to compile our changes.