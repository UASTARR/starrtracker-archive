# StarrTracker
StarrTracker is the tentative name for our group's program used to remotely track the flight trajectory of our rockets during competitions. Each rocket is equipped with a GPS transmitter that allows us to measure the location and altitude of the rocket in real time. StarrTracker provides an interface for the group to watch the location and altitude of the rocket as it updates us with new geospatial information. StarrTracker is intended to run on STARR's custom ground station computer, which is a computer system to be used in the field at rocketry competition sites. It is equipped with the necessary GPS hardware to exchange information with the rocket during flight, which will allow it to be tracked in real time during flight.

## How to Build
1. Make sure you have all prerequisites installed (see project wiki for more information).
2. In the same directory as the `starrtracker.pro` file, run `qmake` in the terminal. This will generate the Makefile used to build the actual application while automatically linking the QT libraries.
3. Once the Makefile has been built, run `make all` to build the StarrTracker executable.
4. Run the StarrTracker executable with `./starrtracker` (on Linux).
