#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include"PositionWeightMatrix.h"
#include"Arrays.h"
#include"Random.h"

typedef struct Times{

    long build_t;
    long build_b;
    long score_t;
    long score_b;

} Times;

inline Times* average( Times** ts, size_t len )
{
    long build_t = 0;
    long build_b = 0;
    long score_t = 0;
    long score_b = 0;

    Times* t;
    size_t i;
    for( i = 0 ; i < len ; ++i )
    {
        t = ts[i];
        build_t += t->build_t;
        build_b += t->build_b;
        score_t += t->score_t;
        score_b += t->score_b;
    }
    
    build_t /= len;
    build_b /= len;
    score_t /= len;
    score_b /= len;

    Times* avg = malloc( sizeof( Times ) );
    avg->build_t = build_t;
    avg->build_b = build_b;
    avg->score_t = score_t;
    avg->score_b = score_b;

    return avg;

}

inline void randomize( size_t* array, size_t len, size_t min, size_t max )
{
    size_t i;
    for( i = 0 ; i < len ; ++i )
    {
        array[i] = randomRangeFast( min, max );
    }
}

Times* runTest( double* M, const size_t K, const size_t N, const size_t L,
                size_t* ARRAY, const size_t T, double* scores_t, double* scores_b  )
{
    Times* times = malloc( sizeof( Times ) );
    long t = clock();
    PWM_traditional* pwm_t = newPWM_traditional( M, K, N );
    t = clock() - t;
    times->build_t = t;
    printf( "PWM traditional build time = %fs\n", ((double) t) / CLOCKS_PER_SEC  );

    t = clock();
    PWM_bitShift* pwm_b = newPWM_bitShift( M, K, N );
    t = clock() - t;
    times->build_b = t;
    printf( "PWM bitShift build time = %fs\n", ((double) t) / CLOCKS_PER_SEC );
    
    t = 0;
    long r = 0;
    long b = 0;
    long c;
    size_t i;
    for( i = 0 ; i < T ; ++i )
    {
        c = clock();
        shuffleSize_ts( ARRAY, L );
        r += clock() - c;
        c = clock();
        scoreAllTraditional( scores_t, ARRAY, L, pwm_t );
        t += clock() - c;
        c = clock();
        scoreAllBitShift( scores_b, ARRAY, L, pwm_b );
        b += clock() - c;
        if( !equalsArrayDouble( scores_t, scores_b, L - K + 1 ) )
        {
            printf( "Error: score discrepency\n" );
        }
    }
    times->score_t = t;
    times->score_b = b;
    printf( "Sequence of size %ld shuffled %ld times in %fs\n", L, T, ((double) r) / CLOCKS_PER_SEC );
    printf( "PWM traditional scored %ld sequences of size %ld in %fs\n", T, L, ((double) t) / CLOCKS_PER_SEC );
    printf( "PWM bitShift scored %ld sequences of size %ld in %fs\n", T, L, ((double) b) / CLOCKS_PER_SEC );
    freePWM_traditional( pwm_t );
    freePWM_bitShift( pwm_b );

    return times;
}

int main( int argc, const char* argv[] )
{
    const size_t K = 10;
    const size_t N = 4;
    double M[] = { 
    0.1, 0.1, 0.1, 0.7,
    0.25, 0.25, 0.25, 0.25, 
    0.6, 0.2, 0.1, 0.1,
    0.25, 0.3, 0.25, 0.2,
    0.01, 0.1, 0.09, 0.8,
    0.9, 0.05, 0.04, 0.01,
    0.4, 0.32, 0.18, 0.1,
    0.3, 0.5, 0.1, 0.1,
    0.2, 0.6, 0.1, 0.1,
    0.25, 0.1, 0.6, 0.05
     };
    logMatrix( M, K, N );
    
    const size_t L = 10000;
    size_t ARRAY[L];
    //init array randomly
    randomize( ARRAY, L, 0, N - 1 );
    const size_t T = 10000;
    double scores_t[L - K + 1];
    double scores_b[L - K + 1];

    if( argc > 1 )
    {
        size_t trials = atoi( argv[1] );
 
        Times* times[trials];
        size_t i;
        for( i = 0 ; i < trials ; ++i )
        {
            printf( "Trial %ld\n", i+1 );
            times[i] = runTest( M, K, N, L, ARRAY, T, scores_t, scores_b );
            printf( "\n" );
        }

        Times* avg = average( times, trials );
        printf( "Average build time (traditional) = %fs\n", ((double) avg->build_t) / CLOCKS_PER_SEC );
        printf( "Average build time (bitShift) = %fs\n", ((double) avg->build_b) / CLOCKS_PER_SEC );
        printf( "Average scoring time (traditional) = %fs\n", ((double) avg->score_t) / CLOCKS_PER_SEC );
        printf( "Average scoring time (bitShift) = %fs\n", ((double) avg->score_b) / CLOCKS_PER_SEC );
        free( avg );
        for( i = 0 ; i < trials ; ++i )
        {
            free( times[i] );
        }
    }
    else
    {
        runTest( M, K, N, L, ARRAY, T, scores_t, scores_b );   
    }
   
    

}

