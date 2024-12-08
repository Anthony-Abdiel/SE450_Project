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

