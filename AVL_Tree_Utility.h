#ifndef AVL_TREE_UTILITY_H
#define AVL_TREE_UTILITY_H

// Header files
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//#include "File_Input_Utility.h"
#include "GeneralUtility.h"
#include "StandardConstants.h"
#include <math.h>

// Constants
   // none
typedef enum { THIN_DIVIDER = '-', THICK_DIVIDER = '=' } DividerCodes;

// Data Structures

typedef struct AvlTreeNodeStruct
   {
    char name[ STD_STR_LEN ];

    char city[ MIN_STR_LEN ];

    int rank;

    struct AvlTreeNodeStruct *leftChildPtr, *rightChildPtr;
   } AvlTreeNodeType;

// Prototypes

/*
Name: clearTree
Process: recursively removes all nodes from tree and returns memory to OS,
         uses post order traversal strategy
Function input/parameters: pointer to root/ working pointer (AvlTreeNodType *)
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: free, clearTree (recursively)
*/
AvlTreeNodeType *clearTree( AvlTreeNodeType *wkgPtr );

/*
Name: copyTree
Process: creates duplicate copy of given tree, allocates all new nodes,
         returns pointer to root of new tree or NULL if original tree was empty,
         uses pre order traversal strategy
Function input/parameters: tree root/working pointer (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: tree root of copied tree
                          or NULL as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createNodeFromNode, copyTree (recursively)
*/
AvlTreeNodeType *copyTree( AvlTreeNodeType *wkgPtr );

/*
Name: createNodeFromData
Process: captures data from individual data items, 
         dynamically creates new node,
         copies data, and returns pointer to new node         
Function input/parameters: university and city (const char *), rank (int)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, privateCopyString
*/
AvlTreeNodeType *createNodeFromData( const char *univName, 
                                           const char *univCity, int univRank );

/*
Name: createNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, and returns pointer to new node         
Function input/parameters: node to be copied (const AvlTreeNodeType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createNodeFromData
*/
AvlTreeNodeType *createNodeFromNode( const AvlTreeNodeType source );

/*
Name: displayInOrder
Process: recursively displays numbered tree items using in order traversal
Function input/parameters: working pointer for recursion 
                                                       (const AvlTreeNodeType *),
                           pointer to display number (int *)
Function output/parameters: pointer to display number (int *)
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: universityDataToString, printf, displayInOrder (recursively)
Note: Uses printf control to align numbering
*/
void displayInOrder( const AvlTreeNodeType *univPtr, int *number );

/*
Name: displayPostOrder
Process: recursively displays numbered tree items using post order traversal
Function input/parameters: working pointer for recursion 
                                                       (const AvlTreeNodeType *),
                           pointer to display number (int *)
Function output/parameters: pointer to display number (int *)
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: universityDataToString, printf, displayPostOrder (recursively)
Note: Uses printf control to align numbering
*/
void displayPostOrder( const AvlTreeNodeType *univPtr, int *number );

/*
Name: displayPreOrder
Process: recursively displays numbered tree items using pre order traversal
Function input/parameters: working pointer for recursion 
                                                       (const AvlTreeNodeType *),
                           pointer to display number (int *)
Function output/parameters: pointer to display number (int *)
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: universityDataToString, printf, displayPreOrder (recursively)
Note: Uses printf control to align numbering
*/
void displayPreOrder( const AvlTreeNodeType *univPtr, int *number );

/*
Name: displaySelectionInOrder
Process: recursively displays numbered selected items in tree using 
         in order traversal, items are specified by provided starting segment 
         of university name string
Function input/parameters: working pointer for recursion 
                                                       (const AvlTreeNodeType *),
                           name segment for searching (const char *)
                           pointer to display number (int *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: privateCompareStringSegments, universityDataToString, printf,
              displaySelectionInOrder (recursively)
*/
void displaySelectionInOrder( AvlTreeNodeType *univPtr, 
                                         const char *nameSegment, int *number );

/*
Name: findBalanceFactor
Process: finds balance factor by subtracting
         height differences between left and right subtrees,
         returns if found, returns zero if pointer is NULL
Function input/parameters: pointer to current tree location (TreeNodeType *)
Function output/parameters: none
Function output/returned: difference between two subtree heights (int)
Device input/---: none
Device output/---: none
Dependencies: findTreeHeight
*/
int findBalanceFactor( AvlTreeNodeType *wkgPtr );

/*
Name: findTreeHeight
Process: recursively finds maximum tree height from current node 
         to bottom of tree
Function input/parameters: pointer to current tree location (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: -1 if empty tree, 0 if no subtrees,
                          max height of subtrees otherwise
Device input/---: none
Device output/---: none
Dependencies: privateFindMax, findTreeHeight (recursively)
*/
int findTreeHeight( AvlTreeNodeType *wkgPtr );

/*
Name: getDataFromFile
Process: uploads data from file with unknown number of data sets,
         has internal Boolean to display data input success
Function input/parameters: file name (const char *)
Function output/parameters: none
Function output/returned: pointer to BST holding data (AvlTreeNodeType *)
Device input/---: data from HD
Device output/monitor: if internal Boolean set, displays uploaded values
Dependencies: openInputFile, readStringToLineEndFromFile, 
              checkForEndOfInputFile, readIntegerFromFile,
              readStringToDelimiterFromFile, readCharacterFromFile, 
              insertRawData, printf, closeInputFile
*/
AvlTreeNodeType *getDataFromFile( const char *fileName );

/*
Name: initializeTree
Process: returns NULL to set tree to empty
Function input/parameters: none
Function output/parameters: none
Function output/returned: NULL
Device input/---: none
Device output/---: none
Dependencies: none
*/
AvlTreeNodeType *initializeTree();

/*
Name: insertNodeData
Process: recursively finds location to insert node, inserts node,
         then follows recursion back up tree to implement balancing,
         does not allow duplicate entries,
         uses "look up" strategy for linking nodes
Function input/parameters: pointer to current tree location (AvlTreeNodeType *),
                           university node (const AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: actions displayed as function progresses
                       ("Identified: <direction> <direction> Case")
Dependencies: insertNodeData
*/
AvlTreeNodeType *insertNodeData( AvlTreeNodeType *wkgPtr, 
                                                const AvlTreeNodeType nodePtr );

/*
Name: insertRawData
Process: recursively finds location to insert node, inserts node,
         then follows recursion back up tree to implement balancing,
         does not allow duplicate entries,
         uses "look up" strategy for linking nodes
Function input/parameters: pointer to current tree location (AvlTreeNodeType *),
                           university and city names (const char *),
                           university ranking (int)
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: actions displayed as function progresses
                       ("Identified: <direction> <direction> Case")
Dependencies: createNodeFromData, privateCompareStrings, findBalanceFactor,
              insertRawData (recursively), printf, rotateLeft, rotateRight,
              privateDisplayChars
*/
AvlTreeNodeType *insertRawData( AvlTreeNodeType *wkgPtr, 
                         const char *univName, const char *univCity, int rank );

/*
Name: isEmpty
Process: reports if tree is empty
Function input/parameters: pointer to current root node (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( AvlTreeNodeType *rootPtr );

/*
Name: rotateLeft
Process: conducts left rotation by manipulation of given pointer,
         displays "- Rotating Left" with an endline
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed ("- Rotating Left")
                       indented by current height of tree + 2
Dependencies: printf, findTreeHeight, and privateDisplayChars for display
*/
AvlTreeNodeType *rotateLeft( AvlTreeNodeType *oldParentPtr );

/*
Name: rotateRight
Process: conducts right rotation by manipulation of given pointer,
         displays "- Rotating Right" with an endline
Function input/parameters: pointer to given subtree to rotate
Function output/parameters: none
Function output/returned: pointer to calling function/tree node above
                          where function is called
Device input/---: none
Device output/monitor: rotation action displayed  ("- Rotating Right")
                       indented by current height of tree + 2
Dependencies: printf, findTreeHeight, and privateDisplayChars for display
*/
AvlTreeNodeType *rotateRight( AvlTreeNodeType *oldParentPtr );

/*
Name: search
Process: recursively searches tree for specified data using university name key
Function input/parameters: pointer to working subtree (AvlTreeNodeType *),
                           university name (const char *)
Function output/parameters: none
Function output/returned: pointer to found node (AvlTreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: privateCompareStrings, search (recursively)
*/
AvlTreeNodeType *search( AvlTreeNodeType *wkgPtr, const char *univName );

/*
Name: universityDataToString
Process: sets data from node to formatted string
Function input/parameters: node with data to be set (const AvlTreeNodeType)
Function output/parameters: string array with result (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: sprintf
*/
void universityDataToString( char *destStr, 
                                         const AvlTreeNodeType universityData );


////////////////////////////////////////////////////////////////////////////////
// No student coding below this point
////////////////////////////////////////////////////////////////////////////////      

/*
Name: displayAtTreeLevel
Process: displays one horizontal "level" of a tree using text graphics
         with appropriate spacing and appropriate number of nodes
Function input/parameters: recursive working node (AvlTreeNodeType *),
                           node height, display level, working level (int),
                           row start flag (bool)
Function output/parameters: none
Function output/returned: updated row start flag (bool *)
Device input/---: none
Device output/---: none
Dependencies: displayValue, displayEmptyNodeSpaces
*/
//void displayAtTreeLevel( AvlTreeNodeType *workingNode, int nodeHeight, 
//                                  int displayLevel, int workingLevel, 
//                                                           bool *rowStartFlag );

/*
Name: displayDivider
Process: displays divider of correct length for tree
         using either THICK_DIVIDER or THIN_DIVIDER 
         depending on the control code,
         adds one endline to thick divider, two to thin for spacing
Function input/parameters: number of characters (int), 
                           character to be displayed (char)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: printf
*/
//void displayDivider( AvlTreeNodeType *rootPtr, char dividerChar );

/*
Name: displayEmptyNodeSpaces
Process: displays the appropriate number of dashes for a given level
         for null nodes, can display either dashes or 'B's
Function input/parameters: node height, display level, working level (int)
                           pointer to row start flag (bool *)
Function output/parameters: none
Function output/returned: updated row start flag (bool *)
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: privateToPower, displayValue
*/
//void displayEmptyNodeSpaces( int nodeHeight, 
//                       int displayLevel, int workingLevel, bool *rowStartFlag );

/*
Name: displayTreeStructure
Process: repeatedly calls other function to display 
         the structure of an RB tree, can display either dashes or 'B's,
         displays error message if empty tree
Function input/parameters: tree root pointer (AvlTreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: characters displayed as specified
Dependencies: findTreeHeight, displayAtTreeLevel, printf
*/
//void displayTreeStructure( AvlTreeNodeType *avlTreeRoot );

/*
Name: displayValue
Process: displays a tree character value or color letter (R/B)
         after a calculated set of leading spaces
Function input/parameters: character data (char), 
                           node height, working level (int),
                           pointer to row start flag (bool *)
Function output/parameters: updated row start flag (bool *)
Function output/returned: none
Device input/---: none
Device output/---: character displayed as specified
Dependencies: privateToPower, displayChars, printf
*/
//void displayValue( char data, int nodeHeight, 
//                                          int workingLevel, bool *rowStartFlag );




//TESTING FUNCTIONS 


bool isBalanced(AvlTreeNodeType* node);

bool containsKey(AvlTreeNodeType* node, const char *name);

bool isHeightValid(AvlTreeNodeType* root, int nodeCount);

int countNodes(AvlTreeNodeType* node);



#endif   // AVL_TREE_UTILITY_H



