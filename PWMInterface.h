#include<stdlib.h>

typedef struct List_Long {
    
    size_t size;
    long (*get)( const List_Long*, size_t i );

}

typedef struct PWMInterface {
    
    //virtual PWM methods
    double (*scoreArray)( const PWM*, const long*, const size_t );
    void (*scoreAllArray)( const PWM*, const long*, const size_t, double* );
    double (*maxScoreArray)( const PWM*, const long*, const size_t ); 

    double (*scoreList)( const PWM*, const List_Long* );
    void (*scoreAllList)( const PWM*, const List_Long*, double* );
    double (*maxScoreList)( const PWM*, const List_Long* );

    void (*destroy)( PWM* );


} PWMInterface;

typedef struct PWM {
    
    const size_t n;
    const size_t k;

    //methods table
    const PWMInterface* const methods;

} PWM;

inline double pwm_scoreArray( const PWM* pwm, const long* seq, const size_t len )
{
    return pwm->methods->scoreArray( pwm, seq, len );
}

inline void pwm_scoreAllArray( const PWM* pwm, const long* seq, const size_t len, double* buffer )
{
    return pwm->methods->scoreAllArray( pwm, seq, len, buffer );
}

inline double pwm_maxScoreArray( const PWM* pwm, const long* seq, const size_t len )
{
    return pwm->methods->maxScoreArray( pwm, seq, len );
}

inline double pwm_scoreList( const PWM* pwm, const List_Long* list )
{
    return pwm->methods->scoreList( pwm, list );
}

inline void pwm_scoreAllList( const PWM* pwm, const List_Long* list, double* buffer )
{
    return pwm->methods->scoreAllList( pwm, list, buffer );
}

inline double pwm_maxScoreList( const PWM* pwm, const List_Long* list )
{
    return pwm->methods->maxScoreList( pwm, list );
}

inline void pwm_destroy( const PWM* pwm )
{
    return pwm->methods->destroy( pwm );
}

