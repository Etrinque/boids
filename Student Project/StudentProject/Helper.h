#pragma once
#include <conio.h>

#include <climits>

#ifndef HELPER_H
#define HELPER_H

namespace Helper
{

// Manipulation
    static void IntegerSwap( int* num1, int* num2 )
    {
        if ( num1 == nullptr || num2 == nullptr )
        {
            return;
        }
        int tmp = *num1;
        *num1 = *num2;
        *num2 = tmp;
    }
    // ascending only bSort
    static void BubbleSort( int* arr, int size )
    {
        for ( int i = 0; i < size - 1; i++ )
        {
            for ( int j = 0; j < size - i - 1; j++ )
            {
                if ( arr[ j ] > arr[ j + 1 ] )
                {
                    Helper::IntegerSwap( &arr[ j ], &arr[ j + 1 ] );
                }
            }
        }
    };
    static int _partition( int* arr, int low, int high )
    {
        int pivot = arr[ high ];
        int partition = low - 1;

        for ( int j = low; j < high; j++ )
        {
            if ( arr[ j ] <= pivot )
            {
                partition++;
                Helper::IntegerSwap( &arr[ partition ], &arr[ j ] );
            }
        }
        Helper::IntegerSwap( &arr[ partition + 1 ], &arr[ high ] );
        return partition + 1;
    };
    // ascending only qSort;
    static void QuickSort( int* arr, int low, int high )
    {
        if ( low < high )
        {
            int pivotIdx = _partition( arr, low, high );
            QuickSort( arr, low, pivotIdx - 1 );
            QuickSort( arr, pivotIdx + 1, high );
        }
    };
    // Retrieval
    static int ClampInteger( int* val, int min, int max )
    {
        if ( *val > max )
        {
            return *val = max;
        }
        else if ( *val < min )
        {
            return *val = min;
        }
        return *val;
    };
    static float ClampFloat( float* val, float min, float max )
    {
        if ( *val > max )
        {
            return *val = max;
        }
        else if ( *val < min )
        {
            return *val = min;
        }
        return *val;
    };
    static int GetMinValue( int* num1, int* num2 )
    {
        return *num1 < *num2 ? *num1 : *num2;
    };
    static int GetMaxValue( int* num1, int* num2 )
    {
        return *num1 > *num2 ? *num1 : *num2;
    };

    // I/O
    static void ClearInputBuffer( )
    {
        std::cout << "Press any key to continue...";
        std::cin.ignore( INT_MAX, '\n' );
    };
    static void PauseConsoleOutput( )
    {
        std::cout << "Press any key to continue...";
        ( void )_getch( );
    };
    static void ClearConsoleWindow( )
    {
        if ( _WIN32 )
        {
            system( "cls" );
        }
        else
        {
            system( "clear" );
        }
        return;
    }

    // Print
    static void PrintIntegerBinary( int* num )
    {
        if ( num == nullptr )
        {
            std::cout << "Null Value" << std::endl;
            return;
        }
        else
        {
            std::cout << "0b";
            for ( int i = 31; i >= 0; --i )
            {
                std::cout << ( ( *num >> i ) & 1 );
            }
        }
        std::cout << std::endl;
    };
    static void PrintIntegerHex( int* num )
    {
        if ( num == nullptr )
        {
            std::cout << "Null Value" << std::endl;
            return;
        }
        else
        {
            int nib;
            std::cout << "0x";
            for ( int i = 7; i >= 0; --i )
            {
                nib = ( *num >> ( i * 4 ) ) & 0xF;
                if ( nib < 10 )
                {
                    std::cout << char( '0' + nib );
                }
                else
                {
                    std::cout << char( 'A' + ( nib - 10 ) );
                }
            }
            std::cout << std::endl;
        }
    };
    static void PrintIntegerOctal( int* num )
    {
        if ( num == nullptr )
        {
            std::cout << "Null Value" << std::endl;
            return;
        }
        else
        {
            int oct;
            std::cout << "0o";
            for ( int i = 10; i >= 0; --i )
            {
                oct = ( *num >> ( i * 3 ) ) & 0x7;
                std::cout << oct;
            }
            std::cout << std::endl;
        }
    };

    // Validation
    static bool IsInteger( char* input ) { return ( *input >= 48 && *input < 58 ); };
    static bool IsInteger( const char* input )
    {
        if ( input == nullptr || input[ 0 ] == '\0' )
        {
            return false;
        };

        int i = 0;
        if ( input[ 0 ] == '-' ) i++;

        do
        {
            if ( !( input[ i ] >= 48 && input[ i ] < 58 ) )
            {
                return false;
            };
            i++;
        } while ( input[ i ] != '\0' );
        return true;
    };

    static bool IsPositiveInteger( int* num ) { return *num > 0; };
    static bool IsEven( int* num ) { return *num % 2 == 0; };
    static bool ValidateRange( int* val, int min, int max )
    {
        if ( *val > max || *val < min )
        {
            return false;
        }
        else
        {
            return true;
        }
    };

}  // namespace Helper

#endif  // !HELPER_H;
