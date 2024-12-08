#include "AVL_Tree_Utility.h"


//Anthony A. Narvaez


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
AvlTreeNodeType *clearTree( AvlTreeNodeType *wkgPtr )
   {
    //make sure working pointer isn't NULL
    if( wkgPtr != NULL )
       {
         //call left recursion
         clearTree( wkgPtr->leftChildPtr );

         //call right recursion
         clearTree( wkgPtr->rightChildPtr );

         //free parent
         free( wkgPtr );
       }
    return NULL;
   }

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
AvlTreeNodeType *copyTree( AvlTreeNodeType *wkgPtr )
   {
    //declare the new local node
    AvlTreeNodeType *newNode = NULL;
    
    //check to make sure the pointer is not NULL 
    if( wkgPtr != NULL )
       {
        newNode = createNodeFromNode( *wkgPtr );

        //call recursion on left child
        newNode->leftChildPtr = copyTree( wkgPtr->leftChildPtr );
        
        //call recursion on right child
        newNode->rightChildPtr = copyTree( wkgPtr->rightChildPtr );
       }

    return newNode;
   }

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
                                           const char *univCity, int univRank )
   {
    //declare the new node, allocate memory for it
    AvlTreeNodeType *newNode = malloc( sizeof( AvlTreeNodeType ) );

    //copy data over to new node
    privateCopyString( newNode->name, univName );
    privateCopyString( newNode->city, univCity );
    newNode->rank = univRank;

    //set children to node 
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;

    return newNode;
   }

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
AvlTreeNodeType *createNodeFromNode( const AvlTreeNodeType source )
   {
    //return created node
    return createNodeFromData( source.name, source.city, source.rank );
   }

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
void displayInOrder( const AvlTreeNodeType *univPtr, int *number )
   {
    //check that the wkgPtr is not NULL
    if( univPtr != NULL )
       {
        //declare the string buffer used for data display
        char buffer[ MAX_STR_LEN ];
        
        //call recursion on left child
        displayInOrder( univPtr->leftChildPtr, number );

        //print parent
            //build the string
        universityDataToString( buffer, *univPtr );

            //display the data
        printf( "%5d) %s\n", *number, buffer);

            //increment the number for next printing operation
        *number = *number + 1;

        //call recursion on right child
        displayInOrder( univPtr->rightChildPtr, number );
       }
   }

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
void displayPostOrder( const AvlTreeNodeType *univPtr, int *number )
   {
    //check to make sure pointer is not NULL
    if( univPtr != NULL )
       {
        //declare string buffer used for data display 
        char strBuffer[ MAX_STR_LEN ];

        //call recursion on left child with incremented number
        displayPostOrder( univPtr->leftChildPtr, number );

        //call recursion on right child with incremented number
        displayPostOrder( univPtr->rightChildPtr, number );

        //leaf node, print parent
            //build string to display
        universityDataToString( strBuffer, *univPtr );

            //display the data
        printf( "%5d) %s\n", *number, strBuffer );

        //incrememnt number 
        *number = *number + 1;
       }
   }

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
void displayPreOrder( const AvlTreeNodeType *univPtr, int *number )
   {
    //check to make sure the pointer is not NULL  
    if( univPtr != NULL )
       {
        //declare string buffer used for data display
        char strBuffer[ MAX_STR_LEN ];

        //display parent
            //build string to display
        universityDataToString( strBuffer, *univPtr );

            //display the data
        printf( "%5d) %s\n", *number, strBuffer );

            //increment number for next printing operation
        *number = *number + 1;

        //call recursion on left child
        displayPreOrder( univPtr->leftChildPtr, number );
        
        //call recursion on right child
        displayPreOrder( univPtr->rightChildPtr, number );
       }
   }

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
                                         const char *nameSegment, int *number )
   {
    //make sure the node isn't NULL
    if( univPtr != NULL )
       {
        //declare the string buffer for data display
        char strBuffer[MAX_STR_LEN];   

        //call recursion on left child
        displaySelectionInOrder( univPtr->leftChildPtr, nameSegment, number );

        //display parent if it contains the given segment
        if( privateCompareStringSegments( nameSegment, univPtr->name ) == 0 )
           {
            //build the string to display 
            universityDataToString( strBuffer, *univPtr );

            //print the name with the number 
            printf( "%5d) %s\n", *number, strBuffer );

            //increment number for next printing operation
            *number = *number+1;
           }
        
        //call recursion on right child
        displaySelectionInOrder( univPtr->rightChildPtr, nameSegment, number );
       }
   }

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
int findBalanceFactor( AvlTreeNodeType *wkgPtr )
   {
    //check if pointer is not NULL
    if( wkgPtr != NULL )
       {
        //declare the left and right height variables
        int leftHeight, rightHeight;

        //find left and right heights
        leftHeight = findTreeHeight( wkgPtr->leftChildPtr );
        rightHeight = findTreeHeight( wkgPtr->rightChildPtr );
        
        //calculate and return balance factor (Left height - Right height)
        return leftHeight - rightHeight;
       }
    return 0;
   }

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
int findTreeHeight( AvlTreeNodeType *wkgPtr )
   {
    //check if working pointer is not NULL
    if( wkgPtr != NULL )
       {
        //declare left and right height variables
        int leftHeight, rightHeight;

        //call left recursion, assigning height
        leftHeight = findTreeHeight( wkgPtr->leftChildPtr);
        rightHeight = findTreeHeight( wkgPtr->rightChildPtr);

        //return the greter of the two heights plus 1 
            //note: 1 is added to account for current node's height
        return privateFindMax( leftHeight, rightHeight ) + 1;
       }
    
    //if the wkg pointer is NULL, height is -1, return that
    return -1;
   }

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
AvlTreeNodeType *getDataFromFile( const char *fileName )
   {
    //declare the first (root) node pointer
    AvlTreeNodeType *rootNode = NULL;

    //declare the boolean flag and counter for it
    bool dispFlag = true;
    int counter = 1;
    
    if( openInputFile( fileName ) )
       {
        //declare a string buffer for first line
        char buffer[ MAX_STR_LEN ];

        //declare variables to hold data from the file
        char inName[ STD_STR_LEN ];
        char inCity[ STD_STR_LEN ];
        int inRank;

        //read first line to skip csv description
        readStringToLineEndFromFile( buffer );

        //print first title and debug message (boolean flag)
        if( dispFlag )
           {
            printf( "\nBegin Loading Data From File . . .\n" );
           }

        //get first integer to prime the loop (read priming)
        inRank = readIntegerFromFile();

        while( !checkForEndOfInputFile() )
           {
            //read the comma
            readCharacterFromFile();

            //read in the name
            readStringToDelimiterFromFile( COMMA, inName );

            //read in the city
            readStringToLineEndFromFile( inCity );

            

            //insert the data into the BST
            rootNode = insertRawData(rootNode, inName, inCity, inRank);

            //test for flag and print if true
            if( dispFlag )
               {
                printf( "%5d) Name: %s, City: %s, Rank: %d\n", counter, inName, 
                                                               inCity, inRank );
                counter = counter + 1;
               }

            //reprime the loop
            inRank = readIntegerFromFile();
           }
       }
    //print last loading debug message
    if( dispFlag )
       {
        printf( 
    "                                  . . . End Loading Data From File\n\n" );
       }

    //print debug message
    closeInputFile();

    return rootNode;
   }
   

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
AvlTreeNodeType *initializeTree()
   {
    return NULL;
   }

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
                                                const AvlTreeNodeType nodePtr )
   {
    return insertRawData( wkgPtr, nodePtr.name, nodePtr.city, nodePtr.rank);
   }

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
                         const char *univName, const char *univCity, int rank )
   {
    //declare integer for balance factor and tree height
    int balanceFactor, treeHeight;

    //check to make sure current node isn't NULL
    if( wkgPtr != NULL )
       {
        //check if given name is less than current node's name
        if( privateCompareStrings( univName, wkgPtr->name ) < 0 )
           {
            //recurse left, setting the left child equal to the result
            wkgPtr->leftChildPtr = insertRawData( wkgPtr->leftChildPtr, 
                                                 univName, univCity, rank );
           }

        //check if given name is greater than current node's name
        else if( privateCompareStrings( univName, wkgPtr->name ) > 0 )
           {
            //recurse right, setting the right child equal to the result
            wkgPtr->rightChildPtr = insertRawData( wkgPtr->rightChildPtr, 
                                                 univName, univCity, rank );
           }
       }
    else
       {
        //found the spot to insert new node, create node
        AvlTreeNodeType *newNode = 
                             createNodeFromData( univName, univCity, rank );
        
        //set the working pointer to the new node
        wkgPtr = newNode;
       }
    

    //Balancing Code  V V V 

    //find balance factor for current node 
    balanceFactor = findBalanceFactor( wkgPtr );
    treeHeight = findTreeHeight( wkgPtr );

    
    //identify right-left case
    if( balanceFactor < -1 && privateCompareStrings( 
                                    univName, wkgPtr->rightChildPtr->name) < 0 )
       {
        //display the action
            //display leading spaces
        privateDisplayChars( treeHeight, SPACE );
            
            //display case
        printf( "Identified: Right Left Case\n" );

        //apply first rotation on the right child of wkgPtr
        wkgPtr->rightChildPtr = rotateRight( wkgPtr->rightChildPtr );

        //apply second roation on the wkgPtr and its right child
        wkgPtr = rotateLeft( wkgPtr );

       }
    //identify right-right case
    else if( balanceFactor < -1 && privateCompareStrings( 
                                   univName, wkgPtr->rightChildPtr->name ) > 0 )
       {
        //display the action
            //display leading spaces
        privateDisplayChars( treeHeight, SPACE );
            
            //display case
        printf( "Identified: Right Right Case\n" );

        //just rotate right on the wkg ptr
        wkgPtr = rotateLeft( wkgPtr );

       }
    //identify left-left case
    else if( balanceFactor > 1 && privateCompareStrings( 
                                    univName, wkgPtr->leftChildPtr->name ) < 0 )
       {
        //display the action
            //display leading spaces
        privateDisplayChars( treeHeight, SPACE );
            
            //display case
        printf( "Identified: Left Left Case\n" );
        
        //just rotate left on the wkgPtr
        wkgPtr = rotateRight( wkgPtr );
       }
    //identify left-right case
    else if( balanceFactor > 1 && privateCompareStrings( 
                                    univName, wkgPtr->leftChildPtr->name ) > 0 )
       {
        //display the action
            //display leading spaces
        privateDisplayChars( treeHeight, SPACE );
            
            //display case
        printf( "Identified: Left Right Case\n" );
        
        //apply first rotation on the left child of wkgPtr
        wkgPtr->leftChildPtr = rotateLeft( wkgPtr->leftChildPtr );

        //apply second rotation on the wkgPtr
        wkgPtr = rotateRight( wkgPtr );
       }

    
    
    //return the current local node
    return wkgPtr;
   }

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
bool isEmpty( AvlTreeNodeType *rootPtr )
   {
    return rootPtr == NULL;
   }

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
AvlTreeNodeType *rotateLeft( AvlTreeNodeType *oldParentPtr )
   {
    //declare int for space alignment
    int numSpaces = 2;

    //declare tree height, find value
    int height = findTreeHeight( oldParentPtr );

    //display rotation

        //print leading spaces
    privateDisplayChars( numSpaces + height, SPACE );

        //display action
    printf( "- Rotating Left\n" );

    //declare a temporary pointer, set it equal to right child (new root/parent)
    AvlTreeNodeType *tempChild = oldParentPtr->rightChildPtr;

    //declare temp pointer for child's left child
    AvlTreeNodeType *tempChildLeft = oldParentPtr->rightChildPtr->leftChildPtr;

    //set the left child of the right child of the root as the 
    //old parent (rotating) ((this makes the right child the new root))
    tempChild->leftChildPtr = oldParentPtr;

    //restore branches 
    tempChild->leftChildPtr->rightChildPtr = tempChildLeft;

    //return the new root pointer
    return tempChild;
   }

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
AvlTreeNodeType *rotateRight( AvlTreeNodeType *oldParentPtr )
   {
    //declare int for space alignment
    int numSpaces = 2;

    //declare and calculate tree height
    int height = findTreeHeight( oldParentPtr );

    //display rotation

        //print leading spaces
    privateDisplayChars( numSpaces + height, SPACE );

        //print action
    printf( "- Rotating Right\n" );

    //declare temp pointer, set equal to left child ( new root )
    AvlTreeNodeType *tempChild = oldParentPtr->leftChildPtr;

    //declare temp pointer for child's right pointer
    AvlTreeNodeType *tempChildRight = oldParentPtr->leftChildPtr->rightChildPtr;

    //set the right child of the left child of the root as the 
    //old parent (rotating)  ((this makes the right child the new root))
    tempChild->rightChildPtr = oldParentPtr;

    //restore branches
    tempChild->rightChildPtr->leftChildPtr = tempChildRight;

    return tempChild;
   }

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
AvlTreeNodeType *search( AvlTreeNodeType *wkgPtr, const char *univName )
   {
    //make sure the working pointer is not NULL
    if( wkgPtr != NULL )
       {
        //check for test less than node
        if( privateCompareStringSegments( univName, wkgPtr->name ) < 0 )
           {
            //recurse left 
            wkgPtr = search( wkgPtr->leftChildPtr, univName );
           }
        //check for test greater than node
        else if( privateCompareStringSegments( univName, wkgPtr->name ) > 0 )
           {
            //recurse right 
            wkgPtr = search( wkgPtr->rightChildPtr, univName );
           }
        //test must be the same as name, node found, return it 
        return wkgPtr;
       }
    return NULL;
   }

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
                                         const AvlTreeNodeType universityData )
   {
    sprintf( destStr, "Name: %s, City: %s, Rank: %d", universityData.name, 
                                      universityData.city, universityData.rank);
   }


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
void displayAtTreeLevel( AvlTreeNodeType *workingNode, int nodeHeight, 
                                  int displayLevel, int workingLevel, 
                                                            bool *rowStartFlag )
   {
    char charOut = workingNode->name[ 0 ];
  
    if( workingLevel == displayLevel )
       {
        displayValue( charOut, nodeHeight, workingLevel, rowStartFlag );
       }
  
    else
       {
        if( workingNode->leftChildPtr != NULL )
           {
            displayAtTreeLevel( workingNode->leftChildPtr, nodeHeight,
                                 displayLevel, workingLevel + 1, rowStartFlag );
           }
  
        else
           {
            displayEmptyNodeSpaces( nodeHeight, displayLevel, 
                                               workingLevel + 1, rowStartFlag );
           }
      
        if( workingNode->rightChildPtr != NULL )
           {
            displayAtTreeLevel( workingNode->rightChildPtr, nodeHeight,
                                 displayLevel, workingLevel + 1, rowStartFlag );
           }

        else
           {
            displayEmptyNodeSpaces( nodeHeight, displayLevel, 
                                               workingLevel + 1, rowStartFlag );
           }              
       }
   }

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
void displayDivider( AvlTreeNodeType *rootPtr, char dividerChar )
   {
    int treeHeight = findTreeHeight( rootPtr );
    int numChars = privateToPower( 2, treeHeight + 2 );

    privateDisplayChars( numChars, dividerChar );

    if( dividerChar == THIN_DIVIDER )
       {
        printf( "\n" );
       }

    printf( "\n" );
   }

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
void displayEmptyNodeSpaces( int nodeHeight, 
                        int displayLevel, int workingLevel, bool *rowStartFlag )
   {
    int nodesToDisplay = privateToPower( 2, displayLevel - workingLevel ); 
    char charOut = SPACE;
  
    if( displayLevel == workingLevel )
       {
        charOut = DASH;
       }
  
    while( nodesToDisplay > 0 )
       {
        displayValue( charOut, nodeHeight, displayLevel, rowStartFlag );
      
        nodesToDisplay--;
       }
   }

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
void displayTreeStructure( AvlTreeNodeType *avlTreeRoot )
   {
    int displayLevel, nodeHeight = findTreeHeight( avlTreeRoot ) + 2;
    int workingLevel = 1;
    bool rowStartFlag;

    if( avlTreeRoot != NULL )
       {
        for( displayLevel = 1; displayLevel <= nodeHeight; displayLevel++ )
           {
            rowStartFlag = true;
          
            displayAtTreeLevel( avlTreeRoot, nodeHeight, 
                                    displayLevel, workingLevel, &rowStartFlag );
          
            printf( "\n" );
           }
       }
  
    else
       {
        printf( "\nEmpty Tree - No Display" );
       }
   }

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
void displayValue( char data, int nodeHeight, 
                                          int workingLevel, bool *rowStartFlag )
   {
    int leadingSpaces;
  
    if( *rowStartFlag )
       {
        leadingSpaces = privateToPower( 2, nodeHeight - workingLevel );

        *rowStartFlag = false;
       }
  
    else
       {
        leadingSpaces = privateToPower( 2, nodeHeight - workingLevel + 1 ) - 1;
       }

    privateDisplayChars( leadingSpaces, SPACE );
  
    printf( "%c", data );         
   }

