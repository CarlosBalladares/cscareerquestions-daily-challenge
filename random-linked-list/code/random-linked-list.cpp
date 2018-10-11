#include <bits/stdc++.h>
#define ASSERT(expected, res)  cout << (expected == res? "\033[1;32mpass\033[0m":"\033[1;31mfail\033[0m" ) << endl;
using namespace std;


/*
  CSCareerQuestions problem Oct 10 2018

  This question was asked by Snapchat.

  Given the head to a singly linked list, where each node also has 
  a “random” pointer that points to anywhere in the linked list, 
  deep clone the list.

  node {
    int value;
    ptr next;
    ptr rand;
  }

*/


/* List node struct */
struct ListNode
{
  int val;
  ListNode* next;
  ListNode* rand;
  ListNode(int val):val(val){
    next = NULL;
    rand = NULL;
  };

};

/*
  deepclone
    Makes a deep clone of a Linked List of ListNode
    returns the head of the clone.
*/
ListNode* deepclone(ListNode* head){
  // Clone without rand
  ListNode* clone_head = new ListNode(head->val);
  ListNode* this_node  = clone_head;
  ListNode* original   = head;
  
  while( original->next != NULL){
    this_node->next = new ListNode (original->next->val);
    original = original->next;
    this_node = this_node->next;
  }

  // handle rand
  map<ListNode*, ListNode*> mapping;
  ListNode* clone_head_temp    = clone_head;
  ListNode* original_head_temp = head;

  while(original_head_temp!= NULL){
    mapping.insert({original_head_temp, clone_head_temp});
    original_head_temp = original_head_temp->next;    
    clone_head_temp = clone_head_temp->next;
  }

  for(auto it = mapping.begin();it!=mapping.end();++it ){
    pair<ListNode*, ListNode*> ocp=*it;
    ocp.second->rand = mapping[ocp.first->rand];
  }
  
  return clone_head;
}


/*
  shallowverify_helper
    Helper for verify.
    
    returns true if both are not null, have the same value
    and point to a different address or if both are NULL
    
    returns false otherwise

*/
bool shallowverify_helper(ListNode* original, ListNode* clone){

  if(original == NULL ^ clone == NULL){
    return false;
  }

  if(original== NULL && clone == NULL){
    return true;
  }

  if(original->val != clone->val){
    return false;
  }

  if(original == clone){
    return false;
  }
  
  return true;
  
}
/*
  verify
    verifies that the nodes in the clone
    and the nodes in the original are
    deep clones of each other. 
    
*/
bool verify(ListNode* original, ListNode* clone){
  while(shallowverify_helper(original,clone) && original!=NULL &&clone!=NULL){
    if(!shallowverify_helper(original->rand,clone->rand))return false;
    original = original->next;
    clone    = clone->next;
  }
  return original ==NULL && clone==NULL;
}




void printList(ListNode* head){
  if(head == NULL){
    cout << "NULL"<< endl;
    return;
  }
  cout << "this_val: "  << head->val << endl;
  cout << "this_rand: " << (head->rand==NULL?0:head->rand->val)<< endl;
  cout << "-----" << endl;
  printList(head->next);
}

int main(){

  int n, val;
  cin >> n;

  ListNode* nodes[n];
  
  for(int i =0;i<n;i++){
    cin >> val;
    nodes[i] = new ListNode(val);
  }

  for(int i =1;i<n;i++)
    nodes[i-1]->next = nodes[i];
  
  for(int i =0;i<n;i++){
    int rand_ptr = (rand() %( n+1));
    nodes[i]->rand = nodes[rand_ptr==n?NULL:rand_ptr];
  }

  ListNode* clone = deepclone(nodes[0]);
 
  // Verify funciton tests
  // 
  // ASSERT(verify(nodes[0], NULL), false);
  // ASSERT(verify(NULL, NULL), true);
  // ASSERT(verify(nodes[2], nodes[0]), false);
  // ASSERT(verify(nodes[0], nodes[0]), false);
  // ASSERT(verify(clone->next, nodes[0]), false);
  
  // Test clone result
  ASSERT(verify(nodes[0], clone), true);



  // clean the mess
  for(int i =0;i<n;i++)
    delete nodes[i];
  
  stack<ListNode*> clone_nodes;
  while(clone!=NULL){
    clone_nodes.push(clone);
    clone = clone->next;
  }

  while(!clone_nodes.empty()){
    delete clone_nodes.top();
    clone_nodes.pop();
  }
  
  return 0;
}
