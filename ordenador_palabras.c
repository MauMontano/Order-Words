#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>
#include <ctype.h>

typedef struct Queue{
    char word[50];
    struct Queue *ant;
    struct Queue *next;
}Palabra;

void push_word(char *, int);
int compare_begin(Palabra *);
int compare_end(Palabra *);
void push_front(Palabra *);
void push_back(Palabra *);
void push_sw(Palabra *);
void pop_word(void);
void display(void);

Palabra *front = NULL;//First element
Palabra *back = NULL;//Last element

int main(){
    int ioption;
    char pal[50];
    char *ptr_pal = pal;
    do{
        Sleep(7000);
        system("cls");
        printf("Menu\n");
        printf ("------------------------------------------\n");
        printf ("1) INSERTAR PALABRA\n");
        printf ("2) ELIMINAR PALABRA\n");
        printf ("3) VER LISTA DE PALABRAS\n");
        printf ("4) SALIR\n");
        printf ("------------------------------------------\n");
        printf("Elige la opcion que deseas: \n");
        fflush(stdin);
        scanf("%d",&ioption);
        switch(ioption){
            case 1:
                printf("Palabra a insertar: ");
                scanf("%s",pal);
                push_word(ptr_pal, strlen(pal));
            break;
            case 2:
                pop_word();
            break;
            case 3:
                display();
            break;
            case 4:
                printf("\nGracias por participar");
            break;
            default:
                printf("\nChoose a valid option");
        }
    }while(ioption != 4);
    return 0;
}
void push_word(char *pal, int word_length){
    //In all our cases we have to implement a while to compare word given with the word on the list
    Palabra *new_element;
    new_element = (Palabra*)malloc(sizeof(Palabra));//Each time that we call the function a new struct is created and added to the stack;
    int i = 0,caso;
    while(i <= word_length){
        new_element->word[i] = tolower(*pal);
        i++;
        pal++;
    }
    if(front == NULL && back == NULL){//If the queue is void
        front = new_element;
        back = new_element;
        new_element->ant = NULL;
        new_element->next = NULL;
    }
    else{//If the queue has at least one element
        if(front == back){// Case 1: we have just one element
            /*Here they can happen two things, Suppose the first word is 'Alberto':
                1.- Word will be pushed at the begin
                    Alacran Alberto
                2.- Word will be pushed at the end
                    Alberto Ana
            */
            caso = compare_begin(new_element);
            if(caso == 1){//word will be pushed at the begin
                push_front(new_element);
            }
            else if(caso == 2){//word will be pushed at the end
                push_back(new_element);
            }
        }
        else {//Case 2: We have at least two elements
            /*Here they can happen three things, Suppose we have Alberto and Ana
                1.- Word will be pushed at the begin
                    alacran alberto ana
                2.- Word will be pushed at the end
                    Alberto Ana Andres
                3.- Word will be pushed between the elements
                    alberto amaranto ana
                If I get 3 make all the things here
                */
            caso = compare_begin(new_element);
            if(caso == 1){//word will be pushed at the begin
                push_front(new_element);
            }
            else{//Word is higher than the firstone
                caso = compare_end(new_element);
                if(caso == 1){//word will be pushed at the end
                    push_back(new_element);
                }
                else{
                    push_sw(new_element);
                }
            }
        }
    }
    printf("\nLa palabra ha sido insertada");
}
int compare_begin(Palabra *new_element){
    int i = 0;
    while(new_element->word[i] == front->word[i]){
        i++;
    }
    if(new_element->word[i] > front->word[i]){// alacran alberto. Here we can have front or back it's equal
        return 1;
    }
    else{//alberto ana
        return 2;
    }
}
int compare_end(Palabra *new_element){
    int i = 0;
    while(new_element->word[i] == back->word[i]){
        i++;
    }
    if(new_element->word[i] < back->word[i]){// alacran alberto. Here we can have front or back it's equal
        return 1;
    }
    else{//alberto ana
        return 2;
    }
}
void push_front(Palabra *new_element){
    Palabra *temp;
    temp = front;
    front = new_element;
    front->ant = NULL;
    front->next = temp;
    temp->ant = front;
}
void push_back(Palabra *new_element){
    Palabra *temp;
    temp = back;
    back = new_element;
    temp->next = back;
    back->ant = temp;
    back->next = NULL;
}
void push_sw(Palabra *new_element){
    int flag = 0,i;
    Palabra *buscador;
    buscador = front;
    while(flag == 0 && buscador != NULL){//while space don´t be found and buscador don´t get the end
        i = 0;
        while(new_element->word[i] == buscador->word[i]){
            i++;
        }
        //alberto amaranto ana
        if(new_element->word[i] < buscador->word[i]){//There are posibilities to the word stay in the middle of alberto y ana
            i = 0;
            while(new_element->word[i] == buscador->next->word[i]){
                i++;
            }
            if(new_element->word[i] > buscador->next->word[i]){
                flag = 1;
            }
            else{
                buscador = buscador->next;
            }
        }
    }
    //When while ends we have the space where we have to insert the word given
    new_element->ant = buscador;
    new_element->next = buscador->next;
    buscador->next = new_element;
    new_element->next->ant = new_element;
}
void pop_word(){
    Palabra *temp = front;
    if(front == NULL && back == NULL){
        printf("\nLa cola esta vacia");
    }
    else{
        if(front == back){
            front = temp->next;//NULL
            back = NULL;
            //free(temp);
        }
        else{
            front = temp->next;//NEXT_ELEMENT
            front->ant = NULL;

        }
        printf("\nSe ha eliminado la palabra de mayor prioridad: '%s' ",temp->word);
        free(temp);
    }
}
void display(){
    Palabra *iterator = back;
    if(back == NULL && front == NULL){
        printf("\nAl momento no hay ninguna palabra en la lista");
    }
    else{
        printf("\nLista de palabras de forma Ascendente (a-z)\n");
        while(iterator != NULL){
            printf("%s\n",iterator->word);
            iterator = iterator->ant;
        }
        iterator = front;
        printf("\nLista de palabras de forma Descendente (z-a)\n");
        while(iterator != NULL){
            printf("%s\n",iterator->word);
            iterator = iterator->next;
        }
    }
}
