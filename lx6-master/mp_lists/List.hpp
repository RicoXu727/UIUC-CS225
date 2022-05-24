
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/*
the first node’s prev pointer
the last node’s next pointer, are both NULL.
we keep a pointer head to the first node, 
and a pointer tail to the last node in the List. 
(In an empty list, both head and tail are NULL.)
The List class also has an integer member variable, length, 
which represents the number of nodes in the List; you will need to maintain this variable.
*/
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    length_ = 0;   // add just one line here;
    head_ = NULL;  // delete type name;
    tail_ = NULL;  //// delete type name;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); // change here from NULL;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL); // tail_ 
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL)
  {
    ListNode * tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  head_ = NULL;
  tail_ = NULL;
  
}
// void List<T>::_destroy() {
//   /// @todo Graded in MP3.1
//   ListNode* curr;
//   ListNode* temp;
//   curr = head_;
//   while(curr != NULL){
//     temp = curr;
//     curr = curr->next;
//     delete temp;
//   }
//   head_ = NULL;
//   tail_ = NULL;
//   temp = NULL;
//   length_= 0;

// }

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  //newNode -> prev = NULL;
  if (size() != 0) {                            //
    newNode -> next = head_;
    head_->prev = newNode;
    //newNode -> prev = NULL;
    head_ = newNode;
  } else {
    head_ = newNode;
    tail_ = newNode;
  }
  length_++;
  
}
// void List<T>::insertFront(T const & ndata) {
//   /// @todo Graded in MP3.1
//   ListNode* temp = new ListNode(ndata);
//   if(length_ == 0){
//     head_ = temp;
//     tail_ = temp;
//     length_++;
//   }
//   else{
//     temp->next = head_;
//     head_->prev = temp;
//     head_ = head_->prev;
//     length_++;
//   }
// }

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (size() != 0) {                            //
    newNode->prev = tail_;                   
    tail_ -> next = newNode;                   //
    tail_ = newNode;
    //newNode->next = NULL;
  } else {
    // newNode->next = NULL;
    // newNode->prev = NULL;
    tail_ = newNode;
    head_ = newNode;
    
  }
  length_++;
}
// void List<T>::insertBack(const T & ndata) {
//   /// @todo Graded in MP3.1
//   ListNode* temp = new ListNode(ndata);
//   if(length_ == 0){
//     head_ = temp;
//     tail_ = temp;
//     length_++;
//   }
//   else{
//     tail_->next = temp; 
//     temp->prev = tail_;
//     tail_ = tail_->next;
//     length_++;
//   }
// }


/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  if (splitPoint == 0) {
    return curr;
  }

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      ListNode * temp;
      temp = curr -> prev;
      curr->prev->next = NULL;
      tail_ = temp;
      curr -> prev = NULL;
  }

  return curr; // NULL
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int groupNumber = floor(size() / 3); // the number of groups need to rotate;
  for (int i = 0; i < groupNumber; i++) {
    if(head_->prev != NULL){
      head_->prev->next = head_->next;
    }
    head_->next->prev = head_->prev;
    head_->prev = head_->next->next;
    head_->next = head_->prev->next;
    if (head_->next != NULL) {
      head_->next->prev = head_;
    }
    head_->prev->next = head_;
    if (head_->next != NULL){
      head_ = head_->next;
    }
  }
  while (head_->prev != NULL)
  {
    head_ = head_->prev;
  }
  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  //edge case;
  if (startPoint == endPoint) {
    return;
  }
  
  ListNode * starttmp, *current, *endtmp;
  starttmp = startPoint->prev;
  current = startPoint->next;
  endtmp = endPoint->next;

  startPoint->next = endtmp;
  startPoint->prev = current;
  

  while (current != endPoint)
  {
    ListNode * temp = current->next;
    current->next = current->prev;
    current->prev = temp;
    current = temp;
  }

  endPoint->next = endPoint->prev;
  endPoint ->prev = starttmp;

  if (startPoint != head_)
  {
    starttmp->next = current;
  } else {
    head_ = endPoint;
  }
  if (endPoint != tail_) {
    endtmp->prev = startPoint;
  } else {
    tail_ = startPoint;
  }
  /////////////////////////////////////////////////////
  // current->next = current->prev;
  // current->prev = startPoint->prev;
  // startPoint->next = endPoint->next;

  // startPoint->next = endPoint->next;
  // startPoint->prev = startPoint->next;
  // endPoint->next = endPoint->prev;
  // endPoint->prev = startPoint->prev;
  /// @todo Graded in MP3.2
  //////////////////////////////////////////////////////
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  ListNode * starttmp = head_;
  ListNode * endtmp = head_;

  while (starttmp != NULL)
  {
    for (int i = 1; i < n; i++)
    {
      if (endtmp != tail_) {
        endtmp = endtmp->next;
      }
    }
    reverse(starttmp, endtmp);
    starttmp = starttmp->next;
    endtmp = starttmp;
  }
  
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  if (first == NULL && second == NULL) {
    return NULL;
  } else if (first == NULL && second != NULL) {
    return second;
  } else if (first != NULL && second == NULL) {
    return first;
  } else {
    while (second != NULL)
    {
      //ListNode * firsttmp = first;
      ListNode * secondtmp = second;
      ListNode * secondhelp = second->next;
      while (first != NULL)
      {
        if (secondtmp->data < first->data) {
          secondtmp->next = first;
          ListNode * firsthelp = first->prev;
          first->prev = secondtmp;
          if (firsthelp == NULL) {  
            secondtmp->prev = NULL;
          } else {
            secondtmp->prev = firsthelp;
            firsthelp->next = secondtmp;
          }
          first->prev = secondtmp;
          break;
        } 
        /*
        while (secondtmp != NULL) 
        {
        if (secondtmp < firsttmp) {
          if (firsttmp != first) {
            second = second->next;
            second->prev = NULL;
            firsttmp->prev = secondtmp;
            secondtmp = secondtmp->next;
            firsttmp->prev->next = firsttmp;
            firsttmp->prev->prev = NULL;
            first = first->prev;
          } else {
            ListNode * firsthelp = firsttmp->prev;
            second = second->next;
            second->prev = NULL;
            firsthelp->next = secondtmp;
            secondtmp = secondtmp->next;
            firsthelp->next->next = firsttmp;
            firsttmp->prev = firsthelp->next;
            firsthelp->next->prev = firsthelp;
            firsthelp = firsthelp->next;
          }
        }
        */
        if (first->next == NULL && second != NULL) {
          first->next = secondtmp;
          secondtmp->prev = first;
          secondtmp->next = NULL;
          break;
        }
        first = first->next;
      }
      second = secondhelp;
    }
    while (first->prev != NULL)
    {
      first = first->prev;
    }
    
  }
  return first;
}

  


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  // @todo Graded in MP3.2
  /////////////////////////////////////////////////////////////////////////////
  // the base case;
  if(chainLength == 1){
    start->prev = NULL;
    start->next = NULL;
    return start;
  }

  int mid = (chainLength / 2);  // mid = floor(chainLength / 2) ;
  ListNode* tmp = start;
  ///move the tmp pointer to the mid position ;
  for(int i = 0; i < mid; i++){    //// (int i = 1; i <= mid; i++)
    tmp = tmp->next;
  }

  //break list;
  if (tmp != NULL){  
    tmp->prev->next = NULL;
    tmp->prev = NULL;
  }
  //recursive step;
  start = mergesort(start, mid);
  tmp = mergesort(tmp, chainLength - mid);
  //merge two lists;
  start = merge(start, tmp);
  
  return start;
  ////////////////////////////////////////////////////////////////////////////////
}

