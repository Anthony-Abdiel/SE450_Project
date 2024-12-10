#include <deepstate/DeepState.hpp>
#include "AVL_Tree_Utility.h"

using namespace deepstate;

// Helper to populate the tree with random data
AvlTreeNodeType* populateTreeRandom(int numNodes) {
    AvlTreeNodeType* root = initializeTree();
    for (int i = 0; i < numNodes; i++) {
        int rank = DeepState_IntInRange(1, 100);  // Random rank
        char name[STD_STR_LEN];
        char city[MIN_STR_LEN];

        // Generate random strings for name and city
        snprintf(name, STD_STR_LEN, "University_%d", rank);
        snprintf(city, MIN_STR_LEN, "City_%d", rank);

        root = insertRawData(root, name, city, rank);
    }
    return root;
}

// Test case: Verify tree balance after random insertions
TEST(AVLTree, InsertAndBalance) {
    int numNodes = DeepState_IntInRange(1, 50);  // Number of nodes to insert
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    ASSERT(isBalanced(root)) << "Tree is not balanced after insertions!";
    clearTree(root);
}

// Test case: Verify BST property using in-order traversal
TEST(AVLTree, BSTProperty) {
    int numNodes = DeepState_IntInRange(1, 50);
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    // Traverse tree in-order and check for sorted order
    char lastName[STD_STR_LEN] = "";
    int displayCount = 1;
    displayInOrder(root, &displayCount);

    // Ensure balance and free memory
    ASSERT(isBalanced(root)) << "Tree is not balanced!";
    clearTree(root);
}

// Test case: Search for all inserted nodes
TEST(AVLTree, SearchInsertedNodes) {
    int numNodes = DeepState_IntInRange(1, 50);
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    for (int i = 0; i < numNodes; i++) {
        int rank = DeepState_IntInRange(1, 100);  // Generate random rank
        char name[STD_STR_LEN];
        snprintf(name, STD_STR_LEN, "University_%d", rank);

        AvlTreeNodeType* result = search(root, name);
        ASSERT(result != NULL) << "Inserted node " << name << " not found!";
    }

    // Test non-existent key
    char nonExistent[STD_STR_LEN] = "University_999";
    ASSERT(search(root, nonExistent) == NULL)
        << "Non-existent key was incorrectly found!";

    clearTree(root);
}

// Test case: Validate tree rotations
TEST(AVLTree, RotationValidation) {
    AvlTreeNodeType* root = initializeTree();

    // Insert values that cause specific rotations
    root = insertRawData(root, "University_30", "City_A", 30);
    root = insertRawData(root, "University_20", "City_B", 20);
    root = insertRawData(root, "University_10", "City_C", 10);  // Triggers rotation

    ASSERT(isBalanced(root)) << "Tree is not balanced after left rotation!";

    root = insertRawData(root, "University_40", "City_D", 40);
    root = insertRawData(root, "University_50", "City_E", 50);  // Triggers rotation

    ASSERT(isBalanced(root)) << "Tree is not balanced after right rotation!";

    clearTree(root);
}


TEST(AVLTree, DisplayInOrderValidation) {
    int numNodes = DeepState_IntInRange(1, 50);
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    char buffer[1000];  // Buffer to capture display output
    int displayCount = 1;

    // Redirect stdout to capture display output
    freopen("/dev/null", "a", stdout);
    setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));

    // Call displayInOrder
    displayInOrder(root, &displayCount);

    // Restore stdout and validate
    freopen("/dev/tty", "a", stdout);
    ASSERT_EQ(displayCount - 1, numNodes) << "Node count does not match!";
    ASSERT(isBalanced(root)) << "Tree is not balanced!";

    clearTree(root);
}


TEST(AVLTree, HeightValidation) {
    int numNodes = DeepState_IntInRange(1, 50);
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    int nodeCount = countNodes(root);
    bool heightValid = isHeightValid(root, nodeCount);

    ASSERT(heightValid) << "Tree height is not valid for " << nodeCount << " nodes!";
    clearTree(root);
}


TEST(AVLTree, EmptyTree) {
    AvlTreeNodeType* root = initializeTree();

    ASSERT(isBalanced(root)) << "Empty tree is not balanced!";
    ASSERT_EQ(countNodes(root), 0) << "Empty tree has non-zero node count!";
    ASSERT(isHeightValid(root, 0)) << "Height check failed for empty tree!";
    clearTree(root);
}


TEST(AVLTree, SingleNode) {
    AvlTreeNodeType* root = insertRawData(NULL, "University_1", "City_1", 1);

    ASSERT(isBalanced(root)) << "Single node tree is not balanced!";
    ASSERT_EQ(countNodes(root), 1) << "Single node tree has incorrect count!";
    ASSERT(isHeightValid(root, 1)) << "Height check failed for single node tree!";
    clearTree(root);
}


TEST(AVLTree, DuplicateInsertions) {
    AvlTreeNodeType* root = initializeTree();

    root = insertRawData(root, "University_1", "City_1", 1);
    root = insertRawData(root, "University_1", "City_1", 1);  // Duplicate

    ASSERT(isBalanced(root)) << "Tree is not balanced after duplicate insert!";
    ASSERT_EQ(countNodes(root), 1) << "Duplicate insertion increased node count!";
    clearTree(root);
}


TEST(AVLTree, DisplayPreOrderRandom) {
    int numNodes = DeepState_IntInRange(10, 100);
    AvlTreeNodeType* root = populateTreeRandom(numNodes);

    int displayCount = 1;
    displayPreOrder(root, &displayCount);

    ASSERT_EQ(displayCount - 1, numNodes) << "Pre-order display missed nodes!";
    clearTree(root);
}


