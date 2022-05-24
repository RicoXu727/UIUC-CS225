using namespace std;
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->right;
    t->right = tmp->left;
    tmp->left = t;
    
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    tmp->height = 1 + max(heightOrNeg1(tmp->left), heightOrNeg1(tmp->right));
    t = tmp; 
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * tmp = t->left;
    t->left = tmp->right;
    tmp->right = t;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    tmp->height = 1 + max(heightOrNeg1(tmp->left), heightOrNeg1(tmp->right));
    t = tmp; 
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
    
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }

    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == 2) {  //heavy right
        int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (rightbalance > 0) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    } else if (balance == -2) { // heavy left
        int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (leftbalance < 0) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node * node = new Node(key, value);
        subtree = node;
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
        rebalance(subtree);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
        rebalance(subtree);
    } else if (key == subtree->key) {
        subtree->value = value;
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * tmp = subtree->left;
            while (tmp->right != NULL) 
            {
                tmp = tmp->right;
            }
            swap(tmp, subtree);
            remove(subtree->left, tmp->key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left) {
                Node * tmp = subtree->left;
                delete subtree;
                subtree = tmp;
            } else {
                Node * tmp = subtree->right;
                delete subtree;
                subtree = tmp;
            }
        }
        // your code here
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
