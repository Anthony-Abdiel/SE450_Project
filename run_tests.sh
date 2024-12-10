#!/bin/bash

# Step 1: Compile the program (assumes AVL_Tree_Utility.c is replaced with a mutant)
g++ -o avl_test_suite AVL_Tree_Utility.c GeneralUtility.c test_avl_tree.cpp -lm -ldeepstate
if [ $? -ne 0 ]; then
    # Compilation failed; skip this mutant
    echo "Compilation failed for mutant"
    exit 0  # Return 0 to indicate the mutant is not killed
fi

# Step 2: Run the test suite
./avl_test_suite > /dev/null 2>&1
if [ $? -ne 0 ]; then
    # Test suite failed, indicating the mutant was killed
    echo "Test failed for mutant"
    exit 1  # Return 1 to signal the mutant is killed
fi

# Step 3: If the test suite passes, the mutant is not killed
echo "Test passed for mutant"
exit 0
