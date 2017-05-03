# LatencySim

 ## NOT YET COMPLETE
 
 ### EXPLORATORY CODE
 Heuristic to simulate a blocking call to various processes that will take a varying length of time:
 Cache the calls that consistently take the longest into memory so that they can be
 immediately returned, cutting down on latency.

 ### ASSUMPTION:
 The bulk of the calls will be to a statistically significant and quantifiably repetitive group
 out of the whole, thereby requiring a small sample of the whole to be cached

 Single function simulateProcess() will represent the various processes taking various amounts of time
 caused in the function by randomly generating a time to respond.

 ### Binary build on OS X system