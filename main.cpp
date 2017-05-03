#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

/*
 * Nicholas Sardo
 * 5/2/2017
 *
 * NOT YET COMPLETE
 *
 * EXPLORATORY CODE
 * Heuristic to simulate a blocking call to various processes that will take a varying length of time:
 * Cache the calls that consistently take the longest into memory so that they can be
 * immediately returned, cutting down on latency.
 *
 * ASSUMPTION:
 * The bulk of the calls will be to a statistically significant and quantifiably repetitive group
 * out of the whole, thereby requiring a small sample of the whole to be cached
 *
 * Single function simulateProcess() will represent the various processes taking various amounts of time
 * caused in the function by randomly generating a time to respond.
 */


struct CachedCall {
    int id;         //position in cache is id for purposes of this code
    int weight;     //weight is indication of frequency called
};

size_t size = 10;
std::vector<CachedCall*> calls(size);


/**
 * Simulate process taking various amounts of time
 * @return success when random time has elapsed
 */
int simulateProcess() {

    /* initialize random seed: */
    srand ( time( NULL ) );

    /* generate secret number between 1 and 10: */
    int irand = rand() % 10 + 1;

    double totalSeconds;
    double delay = (double) irand;

    std::cout << "Time to delay: " << irand << " seconds " << std::endl;

    /* start timer */
    clock_t startTime = clock();

    while( true )
    {
        totalSeconds = ( clock() - startTime ) / CLOCKS_PER_SEC;
        if( totalSeconds >= delay )
        {
            return 1;
        }
    }
}

/*
 * Mock function simulating call to lengthy process
 */
int makeMockCall( std::vector<CachedCall*> &ptr, int call_number ) {

    std::clock_t start;
    double duration;
    start = std::clock();

    while(1)
        if ( simulateProcess() == 1 ) {
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

            if ( duration >= 3 ) {

                // ADD THIS data TO VECTOR
                ptr[call_number]->weight++;

                std::cout << "Long Query!!" << std::endl;
            } else {
                std::cout << "Short Query" << std::endl;
            }

            std::cout <<  duration << " seconds have passed..." << std::endl;
            return 1;
        }
}


int main( int args,char* argv[] )
{
    //INITIALIZE VECTOR
    for ( int i = 0; i < calls.size(); i++ ) {
        CachedCall *cptr = new CachedCall;
        cptr->id = i;
        cptr->weight = 0;
        calls[i] = cptr;
    }

    makeMockCall( calls, 0 );
    makeMockCall( calls, 1 );

    std::cout << "success" << std::endl;
    std::cout << calls[0]->id << " " << calls[0]->weight << std::endl;
    std::cout << calls[1]->id << " " << calls[1]->weight << std::endl;
}
