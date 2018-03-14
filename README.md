# LatencySim

 ## ROUGH DRAFT
 
 ### EXPLORATORY CODE
 Heuristic to simulate a blocking call to various processes that will take a varying length of time:
 Cache the calls that consistently take the longest, and/or are called the most frequently, into 
 memory so that they can be immediately returned, cutting down on latency. These variables are controlled by magic numbers at the top of the file.

### OPERATION
As each call is made, an execution record saves the following metrics:
- call name
- duration of latency for that call
- moving average of latency
- how many times the call has been made

Each time the same call is made, parts of the execution record are updated, and if the call is cached, it is returned.

Periodically, a sort of "garbage collector" scans through the cache to remove cached calls that don't meet the parameters chosen. Obviously as the cache get's larger, this wouldn't be a great strategy. This activity could possibly be ported to a cronjob, or the cache could be progressively bifurcated and cleaned in paralell processes.

 ### Binary build on OS X system
 To build on your system, you'll require CMake. Then, open a terminal within the
 project and enter:
 ```
 cmake CMakeLists.txt
 ```

