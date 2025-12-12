/*
    Name: Manasa S
    Date: 12/12/2025
    Description:Arbitrary Precision Calculator
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"apc.h"

int main(int argc,char *argv[])
{
    Dlist *head1 = NULL; //initialize the header to NULL
	Dlist *tail1 = NULL; //initialize the tail to NULL

    Dlist *head2 = NULL; //initialize the header to NULL
	Dlist *tail2 = NULL; //initialize the tail to NULL

    Dlist *res_head = NULL; //initialize the header to NULL
	Dlist *res_tail = NULL; //initialize the tail to NULL
    printf(GREEN"┌─────────────────────────────────────────────┐\n"
                 "│        ARBITRARY PRECISION CALCULATOR📱     │\n"
                 "└─────────────────────────────────────────────┘\n"RESET);

    
    if(argc != 4)
    {
        printf("Invalid no of arguments\n");
        return 0;
    }
    if(validate_args(argv) == FAILURE) // validation failed
    {
        printf("Invalid Arguments\n");
        return 0;
    }
    convert(argv[1],&head1,&tail1);//converting string to linked list
    convert(argv[3],&head2,&tail2);//converting string to linked list
    int sign1 = 0,sign2 = 0;
    if((argv[1][0] == '-'))
        sign1 = -1;
    else
        sign1 = 1;
    if((argv[3][0] == '-'))
        sign2 = -1;
    else
        sign2 = 1;

    
    if(strcmp(argv[2],"+") == 0)
    {
        printf("Operation : Addition\n");
        printf("Result : ");
        if((sign1 > 0) && (sign2 > 0) )
        {
            addition(&head1,&tail1,&head2,&tail2,&res_head,&res_tail); 
            print_list(res_head);   
        }
        else if((sign1 < 0 ) && (sign2 < 0))
        {
            printf("-");
            addition(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);    
            print_list(res_head);
        }
        else if((sign1 > 0) && (sign2 < 0))
        {
            int i = compare(&head1,&tail1,&head2,&tail2);
            if(i == 0)
                printf("0");
            else if(i == 1)
            {
                subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
                print_list(res_head);
            }
            else if(i==2)
            {
                printf("-");
                subtraction(&head2,&tail2,&head1,&tail1,&res_head,&res_tail);
                print_list(res_head);
            }
        }
        else if((sign1 < 0) && (sign2 > 0))
        {
            int i = compare(&head1,&tail1,&head2,&tail2);
            if(i == 0)
                printf("0");
            else if(i == 1)
            {
                printf("-");
                subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
                print_list(res_head);
            }
            else if(i==2)
            {
                subtraction(&head2,&tail2,&head1,&tail1,&res_head,&res_tail);               
                print_list(res_head);
            }
        }   
            res_head = NULL;
            res_tail = NULL;
    }
    else if(strcmp(argv[2],"-") == 0)
    {
        printf("Operation : Subtraction\n");
        printf("Result : ");
        if((sign1 > 0 ) && (sign2 > 0))
        {
            subtraction(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
            print_list(res_head);
        }
        else if((sign1 < 0 ) && (sign2 < 0))
        {
            subtraction(&head2,&tail2,&head1,&tail1,&res_head,&res_tail);               
            print_list(res_head);
        }
        else if((sign1 > 0) && (sign2 < 0))
        {
            addition(&head2,&tail2,&head1,&tail1,&res_head,&res_tail);
            print_list(res_head);
        }
        else if((sign1 < 0) && (sign2 > 0))
        {
            printf("-");
            addition(&head2,&tail2,&head1,&tail1,&res_head,&res_tail);
            print_list(res_head);
        }

        
        res_head = NULL;
        res_tail = NULL;

    }
    else if(strcmp(argv[2],"x") == 0)
    {
        printf("Operation : Multiplication\n");
        printf("Result : ");
        multiplication(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
        //printf("%d\n",sign1*sign2);
        if((sign1*sign2) < 0)
            printf("-");
        print_list(res_head);
        res_head = NULL;
        res_tail = NULL;
    }
    else if(strcmp(argv[2],"/") == 0)
    {
        printf("Operation : Division\n");
        printf("Result : ");
        division(&head1,&tail1,&head2,&tail2,&res_head,&res_tail);
        if((sign1*sign2) < 0)
            printf("-");
        print_list(res_head);
        res_head = NULL;
        res_tail = NULL;
    }
   
}

int validate_args(char *argv[])
{
    int i = 0;
    if (argv[1][0] == '-')   // allow negative
        i = 1;
    else if(argv[1][0] == '+')
        i = 1;

    while(argv[1][i])
    {
        if(isdigit(argv[1][i]) == 0) //validating operand 1 
        {
           /// printf("Invalid Arguments\n");
            return FAILURE;
        }

        i++;
    }
    i = 0;
    if (argv[3][0] == '-')   // allow negative
        i = 1;
    else if(argv[3][0] == '+')
    {
        i = 1;
    }

    while(argv[3][i])
    {
        if(isdigit(argv[3][i]) == 0) //validating operand 2
        {
           // printf("Invalid Arguments\n");    
            return FAILURE;
        }

        i++;
    }
    //validating operator
    if((strcmp(argv[2],"+") != 0) && (strcmp(argv[2],"-") != 0) && (strcmp(argv[2],"x") != 0) && (strcmp(argv[2],"/") != 0))
    {
        
        return FAILURE;
    }
    printf("✅ Arguments validated successfully\n\n");
    return SUCCESS;


}
int convert(char *str,Dlist **head1,Dlist **tail1)
{
    int i = 0;
    int is_negative = 0;

    if (str[0] == '-')   // mark negative
    {
        is_negative = 1;
        i = 1;
    }
    else if(str[0] == '+')
    {
        i = 1;
    }
    while(str[i] != '\0')
    {
        int num = str[i] - '0';
        dl_insert_last(head1,tail1,num);
        i++;
    }
    return SUCCESS;
}
int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    {
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if((*head) == NULL  || (*tail) == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        new->prev = *tail;
        (*tail)->next = new;
        *tail = new;
        return SUCCESS;
    }
    return FAILURE;
}
}

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if((*head) == NULL  || (*tail) == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
        return SUCCESS;
    }
    return FAILURE;
}

void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("0\n");
	}
	else
	{
	   // printf("Head -> ");
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    //if (head)
		      //  printf("> ");
	    }
    	//printf(" Tail\n");
        printf("\n");
    }
}

