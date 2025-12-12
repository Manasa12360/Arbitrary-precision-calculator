#ifndef APC_H
#define APC_H
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

int dl_insert_last(Dlist **head, Dlist **tail, int data);
int convert(char str[],Dlist **head1,Dlist **tail1);
void print_list(Dlist *head);
int validate_args(char *argv[]);
int dl_insert_first(Dlist **head, Dlist **tail, int data);
int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail);
int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail);
int compare(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2);
int dl_delete_first(Dlist **head, Dlist **tail);
int dl_delete_list(Dlist **head, Dlist **tail);
int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res2_head,Dlist **res2_tail);
int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail);
void remove_zeroes(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2);

#endif