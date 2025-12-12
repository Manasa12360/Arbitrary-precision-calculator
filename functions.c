#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"apc.h"



int addition(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail)
{
    remove_zeroes(head1,tail1,head2,tail2);
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    Dlist *res_temp1  = NULL;
    Dlist *res_temp2 = NULL;

    int carry = 0;
    while((temp1 != NULL) && (temp2 != NULL))
    {
        int num = (temp1->data)+(temp2->data)+carry;
        if(num>9)
        {
            carry = 1;
            num = num%10;
        }
        else
            carry = 0;

        dl_insert_first(&res_temp1,&res_temp2,num);
        temp1=temp1->prev;
        temp2=temp2->prev;

    }
    if((temp1 == NULL) && (temp2 == NULL) && carry ==1)
    {
        dl_insert_first(&res_temp1,&res_temp2,carry);
        *res_head = res_temp1;
        *res_tail = res_temp2;
        return SUCCESS;
    }

    
    while(temp1 != NULL)
    {
        int  num = (temp1->data)+carry;
        if(num>9)
        {
            carry = 1;
            num = num%10;
        }
        else
            carry = 0;
        dl_insert_first(&res_temp1,&res_temp2,num);
        temp1 = temp1->prev;
            
    }
    if((temp1 == NULL) && carry ==1)
    {
        dl_insert_first(&res_temp1,&res_temp2,carry);
        *res_head = res_temp1;
        *res_tail = res_temp2;
        return SUCCESS;
    }
    while(temp2 != NULL)
    {
        int  num = (temp2->data)+carry;
        if(num>9)
        {
            carry = 1;
            num = num%10;
        }
        else
            carry = 0;
        dl_insert_first(&res_temp1,&res_temp2,num);
        temp2=temp2->prev;
        
    }
    if((temp2 == NULL) && carry ==1)
    {
        dl_insert_first(&res_temp1,&res_temp2,carry);
        *res_head = res_temp1;
        *res_tail = res_temp2;
        return SUCCESS;
    }
    *res_head = res_temp1;
    *res_tail = res_temp2;
    return SUCCESS;
}
int compare(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2)
{

    
    int count1=0,count2=0;
    remove_zeroes(head1,tail1,head2,tail2);
    Dlist * temp1 = *head1;
    Dlist * temp2 = *head2;
    /*while((temp1 != NULL) && (temp1->data == 0))
    {
        if(temp1->data == 0)
            dl_delete_first(head1,tail1);
        temp1 = temp1->next;
    }
    while((temp2 != NULL) && (temp2->data == 0))
    {
        if(temp2->data == 0)
            dl_delete_first(head2,tail2);
        temp2 = temp2->next;
    }
    //print_list(*head1);
    //print_list(*head2);
    temp1 = *head1;
    temp2 = *head2;*/

    while(temp1 != NULL)
    {
        count1++;
        temp1= temp1->next;
    }
    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }
    if(count1>count2)
        return 1;
    else if(count2>count1)

        return 2;
    else
    {
        temp1 = *head1;
        temp2 = *head2;

        while(temp1 != NULL && temp1 != NULL)
        {
            if(temp1->data>temp2->data)
                return 1;
            else if(temp2->data>temp1->data)
                return 2;
            else
            {
                temp1= temp1->next;
                temp2 = temp2->next;
            }
        }
        return 0;
    }
}

int subtraction(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail)
{
    int i = compare(head1,tail1,head2,tail2);
    Dlist *temp1;
    Dlist *temp2;
    Dlist *res_temp1  = NULL;
    Dlist *res_temp2 = NULL;
    if(i == 0)
    {
        dl_insert_first(res_head,res_tail,0);
        return 0;
    }
    if(i == 2 )
    {
        temp1 = *head1;
        *head1 =*head2;
        *head2 = temp1;

        temp2 = *tail1;
        *tail1 =*tail2;
        *tail2 = temp2;
    }
    int borrow = 0;
    temp1 = *tail1;
    temp2 = *tail2;
    int res;
    while(temp1 != NULL && temp2 != NULL)
    {
        if((temp1->data) < (temp2->data))
        {
            res = (temp1->data)-(temp2->data)+10-borrow;
            dl_insert_first(&res_temp1,&res_temp2,res);
            borrow =1;
        }
        else
        {
            res = (temp1->data)-(temp2->data)-borrow;
            dl_insert_first(&res_temp1,&res_temp2,res);
            borrow =0;
        }

        temp1 = temp1->prev;
        temp2 = temp2->prev;
    }
    if(temp1 == NULL && temp2 == NULL)
    {
        if(i == 2)
        {
            printf("-");
            *res_head = res_temp1;
            *res_tail = res_temp2;
            return SUCCESS;
        }
        else
        {
            *res_head = res_temp1;
            *res_tail = res_temp2;
            return SUCCESS;
        }
    }

    while(temp1 != NULL)
    {
         int res = (temp1->data) - borrow;
         if(res<0)
         {
            res = res+10;
            borrow = 1;

         }
         else
            borrow = 0;
         dl_insert_first(&res_temp1,&res_temp2,res);
         temp1 = temp1->prev;
    }
    if(i==2)
    {
        printf("-");
        *res_head = res_temp1;
        *res_tail = res_temp2;
        return SUCCESS;
    }
    else
    {
        *res_head = res_temp1;
        *res_tail = res_temp2;
        return SUCCESS;
    }
}
int dl_delete_first(Dlist **head, Dlist **tail)
{
    if((*head) == NULL || (*tail) == NULL)
        return FAILURE;
        
    if((*head) == (*tail))
    {
        *head = NULL;
        *tail = NULL;
        free(*head);
        return SUCCESS;
    }
    else
    {
        Dlist *temp = *head;
        *head = temp->next;
        free(temp);
        (*head)->prev = NULL;
        return SUCCESS;
    }
    return FAILURE;
}

int multiplication(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res2_head,Dlist **res2_tail)
{
    remove_zeroes(head1,tail1,head2,tail2);
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    Dlist *res1_head = NULL;
    Dlist *res1_tail = NULL;
    dl_insert_first(res2_head,res2_tail,0);

    int count = 0,carry = 0,num;
    while(temp2 != NULL)
    {
        while(temp1 != NULL)
        {
            num = (temp1->data) * (temp2->data) +carry;
            if(num>9)
            {
                carry = num/10;
                num = num%10;
            }
            else
                carry = 0;

            dl_insert_first(&res1_head,&res1_tail,num);
            temp1 = temp1->prev;
        }
        if(carry != 0)
        {
            dl_insert_first(&res1_head,&res1_tail,carry);

        }
        int i = count;
        while(i != 0)
        {
            dl_insert_last(&res1_head,&res1_tail,0);
            i--;
        }
        addition(&res1_head,&res1_tail,res2_head,res2_tail,res2_head,res2_tail);
        dl_delete_list(&res1_head,&res1_tail);
        temp1 = *tail1;
        temp2 = temp2->prev;
        count++;
    }

}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    if((*head) == NULL || (*tail) == NULL)
        return FAILURE;
        
    Dlist *temp = *head;
    if((*head) == (*tail))
    {
         
        *head = NULL;
        *tail = NULL;
        free(temp);
        return SUCCESS;
    }
    while((*head) != NULL)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
    }
    *tail = NULL;
    return SUCCESS;
}

int division(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2,Dlist **res_head,Dlist **res_tail)
{
    int i = compare(head1,tail1,head2,tail2);
    
    
    //Dlist *count = malloc(sizeof(Dlist));
    //count->data = 0;
    Dlist *Count_head = NULL;
    Dlist *Count_tail = NULL;
    dl_insert_first(&Count_head,&Count_tail,0);

    Dlist *one_head = NULL;
    Dlist *one_tail = NULL;
    dl_insert_first(&one_head,&one_tail,1);

    if(i == 1)
    {
        while(compare(head1,tail1,head2,tail2) != 2)
        {
            subtraction(head1,tail1,head2,tail2,head1,tail1);
            //print_list(*head1);
            addition(&Count_head,&Count_tail,&one_head,&one_tail,&Count_head,&Count_tail);
           // print_list(Count_head);
        }
        *res_head = Count_head;
        *res_tail = Count_tail;
        return SUCCESS;
    }
    else if(i == 0)
    {
        dl_insert_first(res_head,res_tail,1);
        return SUCCESS;
    }
    else
        return FAILURE;

}

void remove_zeroes(Dlist **head1,Dlist **tail1,Dlist **head2,Dlist **tail2)
{
    Dlist * temp1 = *head1;
    Dlist * temp2 = *head2;
    while((temp1 != NULL) && (temp1->data == 0))
    {
        if(temp1->data == 0)
            dl_delete_first(head1,tail1);
        temp1 = temp1->next;
    }
    while((temp2 != NULL) && (temp2->data == 0))
    {
        if(temp2->data == 0)
            dl_delete_first(head2,tail2);
        temp2 = temp2->next;
    }
}