#include <iostream>
#include <string>
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

//FORWARD REFS
struct CachedCall;
void pruneCache();


constexp int   WEIGHT      = 2;
constexp float MA          = 2.0;
constexp int   CACHE_SIZE  = 20;
int LENGTH              = 0;

std::vector<CachedCall*> cache { 0, 0, 0, 0, 0 };


struct CachedCall {
    int                 id;
    int                 weight;
    std::vector<int>    duration_sample;
    float               moving_avg;

    CachedCall( int id, int weight, std::vector<int> duration_sample, float moving_avg ) {
        this->id                = id;
        this->weight            = weight;
        this->duration_sample   = duration_sample;
        this->moving_avg        = moving_avg;
    }

    CachedCall MakeCachedCall()
    {
        CachedCall c = { this->id, this->weight, this->duration_sample, this->moving_avg };

        return c;
    }

    void randomLatencyCall() {

        std::cout << "Call arrived from " << this->id << std::endl;

        /* generate secret number between 1 and 10: */
        int irand = rand() % 10 + 1;

        std::cout << "Latency: " << irand << " seconds " << std::endl;

        /* BUMP FREQUENCY OF THIS CALL */
        this->weight++;

        /* STORE AMOUNT OF TIME THIS CALL TOOK */
        this->duration_sample.push_back( irand );

        /* CREATE A MOVING AVERAGE FROM CALL TIMES */
        float moving_average = this->sum() / float( this->duration_sample.size() );

        this->moving_avg = moving_average;

        if ( LENGTH >= 4 ) {
            this->pruneCache();
            //return;
        }

        if ( cache.at(this->id) != 0 ) { /* IT EXISTS IN CACHE */
            cache.at(this->id) = new CachedCall{ this->id, this->weight, this->duration_sample, this->moving_avg };
            std::cout << "Returned from cache " << this->id << " WEIGHT: " << this->weight << " MA: " << this->moving_avg << " SIZE: " << (this->duration_sample).size() << std::endl;
            return;
        } else {
            cache.at(this->id) = new CachedCall{ this->id, this->weight, this->duration_sample, this->moving_avg };
            std::cout << this->id << " was cached " << " WEIGHT: " << this->weight << " MA: " << this->moving_avg << " SIZE: " << (this->duration_sample).size() << std::endl;
            LENGTH++;
            return;
        }
    }

    int sum() {
        int sm  = 0;
        int len = this->duration_sample.size();
        if ( len == 0 ) return 0;

        for( int i = 0; i < len; i++ ) {
            sm += this->duration_sample[i];
        }
        return sm;
    }

    void pruneCache() {
        std::cout << "**** PRUNING ****" << std::endl;
        int len = cache.size();
        for ( int i = 0; i < len; i++ ) {
            if ( cache.at(i) == 0 ) continue;
            //IF WEIGHT AND MOVING AVERAGE ARE NOT AT PRESCRIBED LEVEL, CHUCK CALL IT
            if ( (cache.at(i)->weight < WEIGHT) && (cache.at(i)->moving_avg < MA) ) {
                std::cout << "*** Call " << cache.at(i)->id << " has been removed ***" << std::endl;
                delete cache[i];
                cache[i] = 0;
                LENGTH--;
            }
        }
    }
};



int main( int args,char* argv[] )
{
    /* initialize random seed: */
    srand ( time( NULL ) );

    std::vector<int> a1, a2, a3, a4, a5;

    //INITIALIZE CALLS
    CachedCall *call0 = new CachedCall{ 0,  0, a1, 0 };
    CachedCall *call1 = new CachedCall{ 1,  0, a2, 0 };
    CachedCall *call2 = new CachedCall{ 2,  0, a3, 0 };
    CachedCall *call3 = new CachedCall{ 3,  0, a4, 0 };
    CachedCall *call4 = new CachedCall{ 4,  0, a5, 0 };

    for ( int i = 0; i <= 20; i++ ) {
        int irand = rand() % 5; // 0 - 4
        switch ( irand ) {
            case 0:
                call0->randomLatencyCall();
                break;
            case 1:
                call1->randomLatencyCall();
                break;
            case 2:
                call2->randomLatencyCall();
                break;
            case 3:
                call3->randomLatencyCall();
                break;
            case 4:
                call4->randomLatencyCall();
                break;
        }
    }

    std::cout << "At Bottom " << std::endl;
    int len = cache.size();
    for ( int i = 0; i < len; i++ ) {
        std::cout << "id: " << cache.at(i)->id << " weight: " << cache.at(i)->weight << " ma: " << cache.at(i)->moving_avg << std::endl;
    }
}
