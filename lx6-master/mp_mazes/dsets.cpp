/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        setElements.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (setElements[elem] < 0) {
        return elem;
    } else {
        int findOutput = find(setElements[elem]);
        setElements[elem] = findOutput;
        return setElements[elem];
    }
}
void DisjointSets::setunion(int a, int b) {
    int asize = setElements[find(a)] * -1;
    int bsize = setElements[find(b)] * -1;
    int newsize = asize + bsize;
    int aroot = find(a);
    int broot = find(b);
    if (asize < bsize) {
        setElements[aroot] = broot;
        setElements[broot] = newsize * -1;
    } else {
        setElements[broot] = find(a);
        setElements[aroot] = newsize * -1;
    }
}

int DisjointSets::size(int elem) {
    int setSize = -1 * setElements[find(elem)];
    return setSize;
}
