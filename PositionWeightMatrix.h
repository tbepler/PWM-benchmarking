#include<stdlib.h>
#include<string.h>
#include<math.h>

inline void logMatrix( double* matrix, size_t k, size_t n )
{
    size_t i;
    for( i = 0 ; i < k * n ; ++i )
    {
        matrix[i] = log( matrix[i] );
    }
}

inline double log2( double n )
{
    return log( n ) / log ( 2 );
}

inline size_t nextPowerOf2( size_t n )
{
    double exp = ceil( log2( n ) );
    n = (size_t) pow( 2, exp );
    return n;
}

typedef struct PWM_1
{
    
    size_t k;
    size_t n;
    double* matrix;

} PWM_traditional;

inline double score( size_t* array, double* matrix, size_t k, size_t n )
{
    double score = 0;
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        score += matrix[ n * i + array[i] ];
    }
    return score;
}

inline double scoreIndex( size_t* array, size_t idx, double* matrix, size_t k, size_t n )
{
    double score = 0;
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        score += matrix[ n * i + array[i + idx] ];
    }
    return score;
}

inline void scoreAll( double* scores, size_t* array, size_t len, double* matrix, size_t k, size_t n )
{
    size_t i;
    size_t end = len - k + 1;
    for( i = 0 ; i < end ; ++i )
    {
        scores[i] = scoreIndex( array, i, matrix, k, n );
    }
}

inline void scoreAllTraditional( double* scores, size_t* array, size_t len, PWM_traditional* pwm )
{
    scoreAll( scores, array, len, pwm->matrix, pwm->k, pwm->n );
}

PWM_traditional* newPWM_traditional( double* matrix, size_t k, size_t n )
{
    PWM_traditional* pwm = malloc( sizeof( PWM_traditional ) );
    pwm->k = k;
    pwm->n = n;
    size_t bytes = k * n * sizeof( double );
    pwm->matrix = malloc( bytes );
    memcpy( pwm->matrix, matrix, bytes );
    return pwm;
}

void freePWM_traditional( PWM_traditional* pwm )
{
    free( pwm->matrix );
    free( pwm );
}



inline int allElementsEqual( size_t* array, size_t k, size_t val )
{
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        if( array[i] != val )
        {
            return 0;
        }
    }
    return 1;
}

inline void increment( size_t* array, size_t k, size_t n )
{
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        array[i] += 1;
        if( array[i] >= n )
        {
            array[i] = 0;
        }
        else
        {
            break;
        }
    }
}

inline size_t hash( size_t* array, size_t k, size_t bits )
{
    size_t h = 0;
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        h <<= bits;
        h += array[i];
    }
    return h;
}

inline size_t shift( size_t h, size_t next, size_t bits, size_t mask )
{
    //shift bits left
    h <<= bits;
    //zero the top bits
    h &= mask;
    //add the next entry
    h += next;
    return h;
}

inline void scoreAllHash( double* storeScores, size_t* array, size_t len,
                            double* scores, size_t k, size_t bits, size_t mask )
{
    //initialize hash
    size_t h = hash( array, k, bits );
    storeScores[ 0 ] = scores[ h ];
    size_t i = k;
    while( i < len )
    {
        h = shift( h, array[i], bits, mask );
        storeScores[ i - k + 1 ] = scores[ h ];
        ++i;
    }
}

typedef struct PMW_2
{

    size_t k;
    size_t bits;
    size_t mask;
    double* scores;

} PWM_bitShift;

inline void scoreAllBitShift( double* scores, size_t* array, size_t len, PWM_bitShift* pwm )
{
    scoreAllHash( scores, array, len, pwm->scores, pwm->k, pwm->bits, pwm->mask );
}

PWM_bitShift* newPWM_bitShift( double* matrix, size_t k, size_t n )
{
    //let a be n adjusted upwards to nearest power of 2 -- this ensures that the score array is indexed correctly
    size_t a = nextPowerOf2( n );
    size_t bits = log2( a );

    size_t size = (size_t) pow( a, k );
    double* scores = malloc( size * sizeof( double ) );
    //iterate over the k-mers and store their scores
    size_t array[k];
    size_t i;
    for( i = 0 ; i < k ; ++i )
    {
        array[i] = 0;
    }
    scores[ hash( array, k, bits ) ] = score( array, matrix, k, n );
    while( !allElementsEqual( array, k, n - 1 ) )
    {
        increment( array, k, n );
        scores[ hash( array, k, bits ) ] = score( array, matrix, k, n );
    }
    
    PWM_bitShift* pwm = malloc ( sizeof( PWM_bitShift ) );
    pwm->k = k;
    pwm->bits = bits;
    pwm->mask = (size_t) pow( a, k ) - 1;
    pwm->scores = scores;

}

void freePWM_bitShift( PWM_bitShift* pwm )
{
    free( pwm->scores );
    free( pwm );
}



