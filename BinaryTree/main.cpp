#include "Tree.h"
int main() {
    Tree<int> myTree;
    int a[10] = {2,5,12,1,4,0,6,7,8,10};

    for (int key: a)
        myTree.insertNode(key);

    myTree.inorderWalk(myTree.getRoot());

    return 0;

}
