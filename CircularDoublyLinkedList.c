#include <stdio.h>
#include <stdlib.h>

#include "CircularDoublyLinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct CircularDoublyLinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Daca n >= nr_noduri, atunci se intoarce nodul de pe pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe
 * lista si am trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem afla pozitia dorita fara sa
 * simulam intreaga parcurgere?
 * Daca n < 0, eroare.
 */
struct Node* get_nth_node(struct CircularDoublyLinkedList *list, int n) {
    n = n % list->size;
    if (list->head == NULL || n < 0 || list == NULL) {
    	return NULL;
    }
	
	struct Node *curr;
	curr = list->head;
	for (int i = 0; i < n; i++) {
		curr = curr->next;
	}
	return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * reprezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0).
 * Cand indexam pozitiile nu "ciclam" pe lista circulara ca la get, ci consideram nodurile in ordinea de la head la
 * ultimul (adica acel nod care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci adaugam nodul
 * nou la finalul listei. Daca n < 0, eroare.
 */
void add_nth_node(struct CircularDoublyLinkedList *list, int n, void *new_data) {
    struct Node *new = malloc(sizeof(struct Node));
    new->data = new_data;
    struct Node *curr;
    
    if (n < 0 || list == NULL) {
    	return;
    }
    
    
    if (list->head == NULL) {
    	list->head = new;
    	new->next = new;
    	new->prev = new;
   		list->size++;
    	return;
    }
    
    if (n == 0) {
    	new->prev = list->head->prev;
    	new->next = list->head;
    	list->head->prev->next = new;
    	list->head->prev = new;
    	list->head = new;
    	list->size++;
    	return;
    }

    if (n > list->size) {
    	new->next = list->head;
    	new->prev = list->head->prev;
    	list->head->prev->next = new;
    	list->head->prev = new;
    	list->size++;
    	return;
    }

    curr = list->head;
    for (int i = 0; i < n - 1; i++) {
    	curr = curr->next;
    }
    new->prev = curr;
    new->next = curr->next;
    curr->next->prev = new;
    curr->next = new;
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0).
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */
struct Node* remove_nth_node(struct CircularDoublyLinkedList *list, int n) {
    if (list->head == NULL || n < 0 || list == NULL) {
    	return NULL;
    }
    struct Node *nod, *curr;
    
    if (list->size == 1) {
    	nod = list->head;
    	list->head = NULL;
    	list->size--;
    	return nod;
    }
	
	if (n == 0) {
    	nod = list->head;
    	list->head->prev->next = nod->next;
    	nod->next->prev = list->head->prev;
    	list->head = nod->next;
    	list->size--;
    	return nod;
    }

    if (n > list->size - 1) {
    	nod = list->head->prev;
    	list->head->prev = nod->prev;
    	nod->prev->next = list->head;
    	list->size--;
    	return nod;
    }

    curr = list->head;
    for (int i = 0; i < n-1; i++) {
    	curr = curr->next;
    }
    nod = curr->next;
    curr->next = nod->next;
    nod->next->prev = curr;
    list->size--;
    return nod;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */
int get_size(struct CircularDoublyLinkedList *list) {
    if (list != NULL) {
    	return list->size;
}
	return -1;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista.
 */
void free_list(struct CircularDoublyLinkedList **pp_list) {
    if(pp_list == NULL) {
    	return;
    }
    struct Node *prev;
   	while ((*pp_list)->size) {
   		prev = (*pp_list)->head;
   		(*pp_list)->head = (*pp_list)->head->next;
   		free(prev);
   		(*pp_list)->size--;
   	}
   	free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_int_list(struct CircularDoublyLinkedList *list) {
    struct Node *curr;

    if (list == NULL) {
    	return;
    }

    curr = list->head;
   for (int i = 0; i < list->size; i++) {
    	printf("%d ", *((int *)curr->data));
        curr = curr->next;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista separate printr-un spatiu, incepand de la primul
 * nod din lista.
 */
void print_string_list(struct CircularDoublyLinkedList *list) {
    struct Node *curr;

    if (list == NULL) {
    	return;
    }

    curr = list->head;
    for (int i = 0; i < list->size; i++) {
    	printf("%s ", (char *)curr->data);
        curr = curr->next;
    }

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la stanga in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_left_circular(struct Node *start) {
    struct Node *ultim = start->next;
    while (start != ultim) {
    	printf("%d ", *(int *)start->data);
    	start = start->prev;
    }
    printf("%d ", *(int *)ultim->data);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza o singura data toate valorile int stocate in nodurile din lista, separate printr-un spatiu, incepand
 * de la nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita circulara, pana cand sunt afisate
 * valorile tuturor nodurilor.
 */
void print_ints_right_circular(struct Node *start) {
    struct Node *ultim = start->prev;
    while (start != ultim) {
    	printf("%d ", *(int *)start->data);
    	start = start->next;
    }
    printf("%d ", *(int *)ultim->data);
    printf("\n");
}