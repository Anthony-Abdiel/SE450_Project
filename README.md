Welcome to the mess that is the directory I'm using for testing my old AVL implementation
=========================================================================================

The main files you are probably worried about are as follows:

AVL Source Code:                AVL_Tree_Utility.c

AVL Tree Dependencies:          GeneralUtility.c

Deepstate Testing Harness:      test_avl_tree.cpp

Mutation Analysis Script:       run_tests.sh

AFL Seed Files:                 /aflIn

AFL Output Directory:           /aflOut


The rest of the files are all mostly old dependencies from the original implementation of this AVL tree
as well as data files used, again, in the original implementation. I should probably clean that all up...
