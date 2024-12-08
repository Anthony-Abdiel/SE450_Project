// header files
#include <stdio.h>
#include "File_Input_Utility.h"
#include "AVL_Tree_Utility.h"

// constant definitions
   // none

// function prototypes

AvlTreeNodeType *addItem( AvlTreeNodeType *rootPtr );
void copyTreeExample( AvlTreeNodeType *rootPtr );
void displaySelectedData( AvlTreeNodeType *rootPtr );
void findItem( AvlTreeNodeType *rootPtr );
AvlTreeNodeType *uploadData();

// main function
int main( int argc, char *argv[] )
   {
    AvlTreeNodeType *rootPtr;
    char fileName[ STD_STR_LEN ] = "Universities_49.csv";
    char userResponse;
    int dispNum;
    bool runProgram = true;

    // set title
    printf( "\nAVL Testing Program\n" ); 
    printf( "===================\n" ); 

    // initialize iterator
    rootPtr = initializeTree();

    // upload data
       // function: getDataFromFile
    rootPtr = getDataFromFile( fileName );

    if( rootPtr != NULL )
       {
        do
           {
            printf( "\nBinary Search Tree Test Program\n" );
            printf(   "===============================\n" );
   
            printf( "1) (A)dd or Replace Item\n" );
            printf( "2) (F)ind Item\n" );
            printf( "3) (C)opy Tree\n" );
            printf( "4) Display Data (I)n Order\n" );
            printf( "5) Display Data Pos(t) Order\n" );
            printf( "6) Display Data Pr(e) Order\n" );
            printf( "7) Display (S)elected Data\n" );
            printf( "8) Display (G)raphic Tree Structure\n" );
            printf( "9) End (P)rogram\n" );
   
            printf( "\nEnter selection: " );
            scanf( "%c", &userResponse );
            fflush( stdin );
   
            switch( userResponse )
               {
                case '1': case 'a': case 'A':
                   rootPtr = addItem( rootPtr );
                   break;
   
                case '2': case 'f': case 'F':
                   findItem( rootPtr );
                   break;
   
                case '3': case 'c': case 'C':
                   copyTreeExample( rootPtr );
                   break;
   
                case '4': case 'i': case 'I':
                   printf( "\nDisplay in order:\n" );
                   dispNum = 1;
                   displayInOrder( rootPtr, &dispNum );
                   break;
   
                case '5': case 't': case 'T':
                   printf( "\nDisplay post order:\n" );
                   dispNum = 1;
                   displayPostOrder( rootPtr, &dispNum );
                   break;
   
                case '6': case 'e': case 'E':
                   printf( "\nDisplay pre order:\n" );
                   dispNum = 1;
                   displayPreOrder( rootPtr, &dispNum );
                   break;
   
                case '7': case 's': case 'S':
                   dispNum = 1;
                   displaySelectedData( rootPtr );
                   break;
   
                case '8': case 'g': case 'G':
                   dispNum = 1;
                   displayTreeStructure( rootPtr );
                   break;
   
                case '9': case 'p': case 'P':
                   runProgram = false;
                   break;
   
                default:
                   printf( "Incorrect entry, Try again\n" );
                   break;               
               }
           }
        while( runProgram );    
        // end program
       }
    // end correct upload test

    else
       {
        printf( "Data not found - Program aborted\n" );
       }

       // clear BST
          // function: clearTree
       rootPtr = clearTree( rootPtr );

       // show program end
          // function: printf
       printf( "\nEnd Program\n" );

       // return success
       return 0;
   }

/*
Name: addItem
Process: prompts user for individual input, then loads to tree
Function input/parameters: pointer to root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: root/link to recursive pointer (AvlTreeNodeType *)
Device input/keyboard: prompts user as needed
Device output/monitor: displays data as specified
Dependencies: printf, scanf, gets, insertRawData, fflush
*/
AvlTreeNodeType *addItem( AvlTreeNodeType *rootPtr )
   {
    char univName[ STD_STR_LEN ];
    char univCity[ TINY_STR_LEN ];
    int univRank;

    printf( "\nAdd Item Module\n" );

    printf( "Enter university name: " );
    gets( univName );

    printf( "Enter university city: " );
    gets( univCity );

    printf( "Enter rank: " );
    scanf( "%d", &univRank );
    fflush( stdin );

    rootPtr = insertRawData( rootPtr, univName, univCity, univRank );

    printf( "\nUniversity %s added to BST\n", univName );

    return rootPtr;
   }

/*
Name: copyTreeExample
Process: shows original tree, copies tree, then shows copied display
Function input/parameters: pointer to root node (AvlTreeNodeType *) 
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displays as specified
Dependencies: printf, displayInOrder, copyTree, clearTree, fflush
*/
void copyTreeExample( AvlTreeNodeType *rootPtr )
   {
    AvlTreeNodeType *cpdTreePtr;
    int dispNum = 1;

    printf( "\nCopy Tree Module\n" );

    printf( "\nOriginal Tree Displayed:\n" );
    displayInOrder( rootPtr, &dispNum );

    cpdTreePtr = copyTree( rootPtr );

    printf( "\n\nCopied Tree Displayed:\n" );
    dispNum = 1;
    displayInOrder( cpdTreePtr, &dispNum );

    clearTree( cpdTreePtr );

    fflush( stdin );
   }

/*
Name: displaySelectedData
Process: prompts user for university name, then displays all items
         beginning with the provided string segment
Function input/parameters: pointer to root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: prompts user as needed
Device output/monitor: displays data as specified
Dependencies: printf, scanf, fflush, displaySelectionInOrder
*/
void displaySelectedData( AvlTreeNodeType *rootPtr )
   {
    char univNameSgmnt[ STD_STR_LEN ];
    int dispNum = 1;

    printf( "\nDisplay University Selection Module\n" );

    printf( "Enter segment of university name: " );
    scanf( "%s", univNameSgmnt );

    fflush( stdin );

    printf( "\nSelected Data Displayed:\n" );
    displaySelectionInOrder( rootPtr, univNameSgmnt, &dispNum );
   }

/*
Name: findItem
Process: prompts user for university name, finds and displays if available,
         otherwise displays "University not found"
Function input/parameters: pointer to root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: prompts user as needed
Device output/monitor: displays data as specified
Dependencies: printf, scanf, universityDataToString, search, fflush
*/
void findItem( AvlTreeNodeType *rootPtr )
   {
    AvlTreeNodeType *resultPtr;
    char resultStr[ MAX_STR_LEN ];
    char univNameSgmnt[ STD_STR_LEN ];

    printf( "\nFind Item Module\n" );

    printf( "Enter segment of university name: " );
    scanf( "%s", univNameSgmnt );
    
    resultPtr = search( rootPtr, univNameSgmnt );

    if( resultPtr != NULL )
       {
        universityDataToString( resultStr, *resultPtr );

        printf( "University found: %s\n", resultStr );
       }

    else
       {
        printf( "University not found\n" );
       }

    fflush( stdin );
   }

