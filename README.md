# PBPhys
PBPhys is a C library providing structures and functions to simulate system of moving particles in any dimension.

Each particle is represented by a Shapoid, with a speed and acceleration vector, a mass and a drag coefficient. Particles can be fixed. The PBPhys is defined as GSet of particles. The system can emulate or ignore attraction between particles, downward gravity (applied to the second component of vectors, to simulate earth attraction for example), drag force on particle, elastic collision between particles (considered as perfect spheres). The user can control the system's particle by position, speed or acceleration. The user can step the system by increment of time or until the next collision. The whole system and individual particles can be printed on a stream, saved/loaded in a file.

## How to install this repository
1) Create a directory which will contains this repository and all the repositories it is depending on. Lets call it "Repos"
2) Download the master branch of this repository into "Repos". Unzip it if necessary.
3) The folder's name for the repository should be followed by "-master", rename the folder by removing "-master".
4) cd to the repository's folder
5) If wget is not installed: ```sudo apt-get update && sudo apt-get install wget``` on Ubuntu 16.04, or ```brew install wget``` on Mac OSx
6) If gawk is not installed: ```sudo apt-get update && sudo apt-get install gawk```  on Ubuntu 16.04, ```brew install gawk``` on Mac OSx
7) If this repository is the first one you are installing in "Repos", run the command ```make -k pbmake_wget```
8) Run the command ```make``` to compile the repository. 
9) Eventually, run the command ```main``` to run the unit tests and check everything is ok.
10) Refer to the documentation to learn how to use this repository.

The dependancies to other repositories should be resolved automatically and needed repositories should be installed in the "Repos" folder. However this process is not completely functional and some repositories may need to be installed manually. In this case, you will see a message from the compiler saying it cannot find some headers. Then install the missing repository with the following command, e.g. if "pbmath.h" is missing: ```make pbmath_wget```. The repositories should compile fine on Ubuntu 16.04. On Mac OSx, there is currently a problem with the linker.
If you need assistance feel free to contact me with my gmail address: at bayashipascal.
