/*

Author: Tristan Bepler

*/

#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

inline int equalsArrayDouble( double* a, double* b, size_t len )
{
    size_t i;
    for( i = 0 ; i < len ; ++i )
    {
        if( a[i] != b[i] ) return 0;
    }
    return 1;
}

inline void swapDoubles( double* a, double* b )
{
	double temp = *a;
	*a = *b;
	*b = temp;
}

inline void swapLongs( long* a, long* b )
{
	long temp = *a;
	*a = *b;
	*b = temp;
}	

inline void swapInts( int* a, int* b )
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

inline void swapSize_ts( size_t* a, size_t* b )
{
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

inline void swap( void* i, void* j, size_t size )
{
	char temp[size];
	memcpy(temp, i, size);
	memcpy(i, j, size);
	memcpy(j, temp, size);
}

inline size_t partitionDoublesAscending( double* array, size_t low, size_t up )
{
	//pick middle element as pivot
	size_t pivot = low + ( up - low ) / 2;
	double val = array[pivot];
	
	//swap pivot to the end
	swapDoubles( &array[pivot], &array[up] );
	size_t i = low;
	size_t j;
	for( j = low ; j < up ; ++j )
	{
		if( array[j] <= val )
		{
			swapDoubles( &array[i++], &array[j] );
		}
	}
	//swap pivot to correct position
	swapDoubles( &array[i], &array[up] );
	return i;
}

inline size_t partitionDoublesDescending( double* array, size_t low, size_t up )
{
	//pick middle element as pivot
	size_t pivot = low + ( up - low ) / 2;
	double val = array[pivot];
	
	//swap pivot to the end
	swapDoubles( &array[pivot], &array[up] );
	size_t i = low;
	size_t j;
	for( j = low ; j < up ; ++j )
	{
		if( array[j] >= val )
		{
			swapDoubles( &array[i++], &array[j] );
		}
	}
	//swap pivot to correct position
	swapDoubles( &array[i], &array[up] );
	return i;
}

//courtesy of http://alienryderflex.com/quicksort/
inline void quicksortDoublesAscending(double *arr, size_t len) {
 	#define  MAX_LEVELS  300
	double piv;
	size_t beg[MAX_LEVELS];
	size_t end[MAX_LEVELS];
	size_t L, R;
	int i = 0;
	int swap;

 	beg[0] = 0;
	end[0] = len;
  	while ( i >= 0 ) {
    		L = beg[i];
		R = end[i] - 1;
    		if ( L < R )
		{
      			piv = arr[L];
      			while ( L < R )
			{
        			while ( arr[R] >= piv && L < R )
				{
					--R;
					if ( L < R )
					{
						arr[L++] = arr[R];
					}
				}
        			while ( arr[L] <= piv && L < R )
				{
					++L;
					if ( L < R )
					{
						arr[R--] = arr[L];
					}
				}
			}
      			arr[L] = piv;
			beg[ i + 1 ] = L + 1;
			end[ i + 1 ] = end[i];
			end[ i++ ] = L;
      			if ( end[i] - beg[i] > end[ i - 1 ] - beg[ i - 1 ] )
			{
        			swap = beg[i];
				beg[i] = beg[ i - 1 ];
				beg[ i - 1 ] = swap;
        			swap = end[i];
				end[i] = end[ i - 1 ];
				end[ i - 1 ] = swap;
			}
		}
    		else
		{
      			i--; 
		}
	}
}

//courtesy of http://alienryderflex.com/quicksort/
inline void quicksortDoublesDescending(double *arr, size_t len) {
 	#define  MAX_LEVELS  300
	double piv;
	size_t beg[MAX_LEVELS];
	size_t end[MAX_LEVELS];
	size_t L, R;
	int i = 0;
	int swap;

 	beg[0] = 0;
	end[0] = len;
  	while ( i >= 0 ) {
    		L = beg[i];
		R = end[i] - 1;
    		if ( L < R )
		{
      			piv = arr[L];
      			while ( L < R )
			{
        			while ( arr[R] <= piv && L < R )
				{
					--R;
					if ( L < R )
					{
						arr[L++] = arr[R];
					}
				}
        			while ( arr[L] >= piv && L < R )
				{
					++L;
					if ( L < R )
					{
						arr[R--] = arr[L];
					}
				}
			}
      			arr[L] = piv;
			beg[ i + 1 ] = L + 1;
			end[ i + 1 ] = end[i];
			end[ i++ ] = L;
      			if ( end[i] - beg[i] > end[ i - 1 ] - beg[ i - 1 ] )
			{
        			swap = beg[i];
				beg[i] = beg[ i - 1 ];
				beg[ i - 1 ] = swap;
        			swap = end[i];
				end[i] = end[ i - 1 ];
				end[ i - 1 ] = swap;
			}
		}
    		else
		{
      			i--; 
		}
	}
}

inline size_t partition( void* array, size_t size, size_t low, size_t up, int (*compare)( const void*, const void* ) )
{
	char* arr;
	arr = (char*) array;
	char* pivot = arr + ( low + ((( up - low ) / size) / 2 ) * size );
	char x[size];
	memcpy( x, pivot, size );

	//swap pivot to the end
	swap( pivot, arr + up, size );	

	size_t i = low;
	size_t j;
	for( j = low ; j < up ; j += size )
	{
		//printf( "j = %d\n", j );
		if( compare( arr + j, &x ) <= 0 )
		{
			swap( arr + i , arr + j, size );
			i += size;
		}
	}
	//swap pivot into correct position
	swap( arr + i, arr + up, size );
	return i;
}

inline void printDoubleArray( double* arr, size_t len )
{
	int i;
	for( i = 0 ; i < len ; ++i )
	{
		printf( "%f", arr[i] );
		if( i != len -1 )
		{
			printf( ", " );
		}
	}
	printf( "\n" );
}	

inline void quicksort( void* array, size_t len, size_t size, int (*compare)( const void*, const void* ) )
{
	
	char* arr = (char*) array;	
	
	size_t low = 0;
	size_t up = (len - 1) * size;

	size_t stack[ len - 1 ];
	ssize_t top = 0;
	
	stack[ top ] = low;
	stack[ ++top ] = up;

	size_t part;
	while( top >= 0 )
	{
		up = stack[ top-- ];
		low = stack[ top-- ];

		part = partition( arr, size, low, up, compare );

		if( part > low + size )
		{
			stack[ ++top ] = low;
			stack[ ++top ] = part - size;
		}
		if( part + size < up )
		{
			stack[ ++top ] = part + size;
			stack[ ++top ] = up;
		}
	}
}

inline int isSorted( const void* array, size_t len, size_t size, int (*compare)( const void*, const void* ) )
{
	char* arr = (char*) array;
	size_t i;
	size_t end = ( len - 1 ) * size;
	for( i = 0 ; i < end ; i += size )
	{
		if( compare( arr + i, arr + i + size ) > 0 )
		{
			return 0;
		}
	}
	return 1;
}

inline int compareDoubleAscending( const void* i, const void* j )
{
	double a = * (double*) i;
	double b = * (double*) j;
	if( a < b )
	{
		return -1;
	}
	if( a > b )
	{
		return 1;
	}
	return 0;
}

inline int compareDoubleDescending( const void* i, const void* j )
{
	double a = * (double*) i;
	double b = * (double*) j;
	if( a > b )
	{
		return -1;
	}
	if( a < b )
	{
		return 1;
	}
	return 0;
}





#endif /* ARRAYS_H */

