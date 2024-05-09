/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while(length_ > 0) {
    ListNode* temp = head_->next;
    delete head_;
    head_ = temp;
    length_--;
  }
  tail_ = NULL;
}

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
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;

  length_++;

}

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
  newNode -> next = NULL;
  newNode -> prev = tail_;

  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }

  tail_ = newNode;
  length_++;
}

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

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
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
  ListNode *n1, *n2, *n3 = head_;
  bool first = true;
  int i = 0;

  while (i+2 < size() && n3 != nullptr && n3->next != nullptr && n3->next->next != nullptr) {
    // Assign nodes for the current triplet
    n1 = n3;
    n2 = n1->next;
    n3 = n2->next;
    // Update pointers for rotation
    n1->next = n3->next;
    n3->next = n1;
    n2->prev = n1->prev;
    n1->prev = n3;
    // Move n3 to the next triplet
    if (n1->next != nullptr) {
      n3 = n1->next;
      n1->next->prev = n1;
    }
    // Update head if necessary
    if (first) {
      head_ = n2;
      first = false;
    } else {
      n2->prev->next = n2;
    }
    i += 3;
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
  /// @todo Graded in MP3.2
  ListNode* curr = startPoint;
  ListNode* next = startPoint->next;
  ListNode* prev = curr->prev;

  curr->next = endPoint->next;
  curr->prev = next;
  curr = next;
  while (curr != endPoint && curr != nullptr) {
    next = next->next;
    curr->next = curr->prev;
    curr->prev = next;
    curr = next;
  }
  endPoint->next = endPoint->prev;
  endPoint->prev = prev;

  if (startPoint != head_) {
    prev->next = curr;
  }
  if (endPoint != tail_) {
    startPoint->next->prev = startPoint;
  }
  endPoint = startPoint;
  startPoint = curr;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* temp = head_;
  ListNode* temp2 = head_;
  for (int i=0; i<size(); i++) {
    if (i % n == 0 && i != 0) {
      temp = temp2;
    }
    if (i % n == n-1 || i == size()-1) {
      reverse(temp2 == head_ ? head_ : temp2, temp == tail_ ? tail_ : temp);
      temp2 = temp->next;
      temp = temp2;
    }
    else {
      temp = temp->next;
    }
  }
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
  /// @todo Graded in MP3.2
  ListNode* smallest = first->data < second->data ? first : second;
  ListNode* temp1 = first->data < second->data ? first->next : first;
  ListNode* temp2 = first->data < second->data ? second : second->next;
  ListNode* smaller = smallest;
  ListNode* temp = smaller;

  while (temp1 != nullptr || temp2 != nullptr) {
    if (temp2 == nullptr || (temp1 != nullptr && temp1->data < temp2->data)) {
      temp = temp1;
      temp1 = temp1->next;
    }
    else {
      temp = temp2;
      temp2 = temp2->next;
    }
    smaller->next = temp;
    temp->prev = smaller;
    smaller = temp;
  }
  return smallest;
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
  /// @todo Graded in MP3.2
  if (start->next == nullptr) {
    return start;
  }
  ListNode* other = split(start, chainLength/2);
  start = mergesort(start, chainLength/2);
  other = mergesort(other, chainLength - chainLength/2);
  return merge(start, other);
}
