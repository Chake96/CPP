#include <iostream>


struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL){}
};

ListNode* swapPairs(ListNode* head){
	if(head== NULL) return NULL;
	if(head && head->next == NULL) return head;
	ListNode* temp = head;
	head = head->next;
	temp->next = head->next;
	head->next = temp;
	head->next->next = swapPairs(head->next->next); 
	return head;
}




int main(){

	ListNode* list = new ListNode(1);
	list->next = new ListNode(2);
	list->next->next = new ListNode(3);
	list->next->next->next = new ListNode(4);
	std::cout << "Before: [";
	ListNode* prnt_node = list;
	while(prnt_node != NULL){
		std::cout << prnt_node->val << ", ";
		prnt_node = prnt_node->next;
	}
	list = swapPairs(list);
	prnt_node = list;
	std::cout << "]\nAfter: [";
	while(prnt_node != NULL){
		std::cout << prnt_node->val << ", ";
		prnt_node = prnt_node->next;
	}
	std::cout << std::endl;
	std::exit(0);
}
