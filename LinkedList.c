#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste simplu inlantuite, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e adaugat pe pozitia n a listei
 * rep;rezentata de pointerul list. Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla
 * pe pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca n < 0, eroare.
 */

void add_nth_node(struct LinkedList *list, int n, void *new_data) {
    if (list == NULL || n < 0) {
        return;
    }

    struct Node* new = malloc(sizeof(struct Node));
    struct Node *it = list->head;

    new->data = new_data; // Nu ne nevoie de castare dubioasa, ambii sunt pointeri, si daca arata amandoi la aceeasi chestie e ca si cum *p = 5
    list->size++; // Valabil la toate operatiile de adaugare

    // ADD_FIRST
    if(n == 0) {
        list->head = new;
        // Daca lista e goala
        if (list->size == 0) {
            new->next = NULL;
            return;
        }
        new->next = it;
        return;
    }

    // ADD_MIDDLE (sau LAST): Avansam cu iteratorul pana la pozitia unde trebuie sa inseram (finalul listei sau pozitia ceruta)   
    for (int i = 0; i < n - 1 && it->next != NULL; i++) {
        it = it->next;
    }
        
    new->next = it->next;
    it->next = new;
    return;
    
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1,
 * se elimina nodul de la finalul listei. Daca n < 0, eroare.
 * Functia intoarce un pointer spre acest nod proaspat eliminat din lista.
 * Este responsabilitatea apelantului sa elibereze memoria acestui nod.
 */

struct Node* remove_nth_node(struct LinkedList *list, int n) {
    if (list == NULL || n < 0 || list->size == 0) {
        return NULL;
    }

    struct Node *rmvd_node;

    // Daca avem un singur element
    if (list->size == 1) {
        rmvd_node = list->head;
        list->head = NULL;
        
        list->size --;
        return rmvd_node;
    }

    // Daca n == 0
    if (n == 0) {
        rmvd_node = list->head;
        list->head = list->head->next;
        
        list->size --;
        return rmvd_node;
    }
    
    struct Node *it = list->head;

    // Daca n >= list->size => remove_last
    if (n >= list->size) {
        while (it->next->next != NULL) {
            it = it->next;
        }
        rmvd_node = it->next;
        it->next = NULL;

        list->size --;
        return rmvd_node;
    }

    // Default: parcurgere si remove
    for (int i = 0; i < n - 1; i++) {
        it = it->next;
    }
    rmvd_node = it->next;
    it->next = it->next->next;
    return rmvd_node;
}

struct Node* reverse_list() {
    
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca parametru.
 */

int get_size(struct LinkedList *list) {
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit, elibereaza memoria folosita
 * de structura lista si actualizeaza la NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void free_list(struct LinkedList **pp_list) {
    if(pp_list == NULL) {
        return;
    }

    struct Node *it;
    it = (*pp_list)->head; // From pointer to list to list.

    // Solution: Mananci din lista ca la Pacman

    // Eliberez fix ce nu e NULL
    while((*pp_list)->head != NULL) {
        it = (*pp_list)->head;
        (*pp_list)->head = ((*pp_list)->head)->next;
        free(it);
    }

    free((*pp_list)->head);
    free(*pp_list);
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza int-uri.
 * Functia afiseaza toate valorile int stocate in nodurile din lista inlantuita separate printr-un spatiu.
 */
void print_int_linkedlist(struct LinkedList *list) {
    if (list == NULL || list->size == 0) {
        return;
    }

    // Puteam sa le pun pe amandoua in acelasi if? Daca list era null, list->head dadea seg

    struct Node *it = list->head;

    while (it != NULL) {
        printf("%d ", *((int *)it->data));
        it = it->next;
    } 

    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM ca stocheaza string-uri.
 * Functia afiseaza toate string-urile stocate in nodurile din lista inlantuita, separate printr-un spatiu.
 */
void print_string_linkedlist(struct LinkedList *list) {
    if (list == NULL || list->size == 0) {
        return;
    }

    struct Node *it = list->head;    

    while (it != NULL) {
        printf("%s ", (char *)it->data);
        it = it->next;
    }
    printf("\n");
}