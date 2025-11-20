/*
 * Program Name: LLL
 * Brief Description: Linked list library with multi-OS debug functions
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * For more details, see the GNU General Public License:
 * <https://www.gnu.org/licenses/>.
 */




#ifndef __LINKED_LIST_LIBRARY_H
#define __LINKED_LIST_LIBRARY_H


/*Definizione versione LLL*/
#define LLL_VERSION_MAJOR 0
#define LLL_VERSION_MINOR 1

/*Definizione modalità Debug per LLL*/
#define LLL_DEBUG   

#include <stdlib.h>
#include <stdio.h>



/*
 * Struct: Node
 * ----------------------------
 * Rappresenta un nodo di una lista collegata semplice (singly linked list).
 *
 * Campi:
 *  - int id
 *      Un identificatore numerico o un valore associato a questo nodo.
 *      Può essere usato per distinguere i nodi tra loro o memorizzare dati.
 *
 *  - struct Node *next
 *      Puntatore al nodo successivo nella lista. Se il nodo è l'ultimo elemento,
 *      questo puntatore sarà NULL. Serve a creare la catena di nodi che forma
 *      la lista collegata.
 *
 * Utilizzo tipico:
 *  - Creazione di liste dinamiche in cui il numero di elementi non è noto a priori.
 *  - Iterazione su tutti i nodi partendo dal primo nodo della lista.
 *  - Inserimento, rimozione o ricerca di nodi in modo efficiente senza spostare blocchi
 *    di memoria contigui.
 *
 * Nota:
 *  - Questa è una lista collegata semplice: ogni nodo punta solo al successivo.
 *  - Non contiene informazioni sul nodo precedente (per quello servirebbe una doubly linked list).
 */

struct Node
{
    int id;
    struct Node *next;
};








/*
 * Macro/Funzione: DEBUG_PRINT
 * ----------------------------
 * Funzione/macros generica per stampare messaggi di debug.
 * Compatibile su più sistemi operativi.
 *
 * Scopo:
 *  - Centralizzare tutti i messaggi di debug in un unico punto.
 *  - Permette di abilitare/disabilitare facilmente il logging di debug
 *    senza modificare tutte le funzioni della libreria.
 *
 * Utilizzo tipico:
 *   DEBUG_PRINT("Messaggio di debug: id = %d\n", node->id);
 *
 * Nota:
 *  - Su Windows utilizza printf standard.
 *  - Su Linux/macOS utilizza printf standard (può essere rediretto su syslog se necessario).
 *  - Può essere facilmente ridefinita per inviare messaggi su file, console o log esterni.
 */
#ifdef _WIN32
    #define LLL_DEBUG_PRINT(fmt, ...) \
        do { fprintf(stdout, "[DEBUG] " fmt, __VA_ARGS__); } while (0)
#else
    #define LLL_DEBUG_PRINT(fmt, ...) \
        do { fprintf(stdout, "[DEBUG] " fmt, ##__VA_ARGS__); } while (0)
#endif

/*
 * Macro/Funzione: DEBUG_NODE(node_ptr n)
 * ----------------------------
 * Stampa rapidamente lo stato di un nodo.
 *
 * Scopo:
 *  - Visualizzare i dati principali di un nodo (id, next pointer)
 *    durante il debugging della lista.
 *  - Unifica la rappresentazione dei nodi nella libreria.
 *
 * Utilizzo tipico:
 *   DEBUG_NODE(current);
 *
 * Nota:
 *  - Usa DEBUG_PRINT per garantire output coerente su tutte le piattaforme.
 */
#define LLL_DEBUG_NODE(n) \
    do \
    { \
        if (n) \
        { \
            LLL_DEBUG_PRINT("Node at %p -> id: %d, next: %p\n", (void*)(n), (n)->id, (void*)((n)->next)); \
        } \
        else \
        { \
            LLL_DEBUG_PRINT("Node is NULL\n"); \
        } \
    } while(0)

/*
 * Macro/Funzione: DEBUG_LIST(head)
 * ----------------------------
 * Stampa rapidamente l'intera lista collegata.
 *
 * Scopo:
 *  - Verifica lo stato completo della lista durante il debugging.
 *  - Controlla struttura, ordine e integrità dei nodi.
 *
 * Utilizzo tipico:
 *   DEBUG_LIST(head);
 *
 * Nota:
 *  - Itera sulla lista partendo dalla testa fino a NULL.
 *  - Usa DEBUG_NODE per stampare ogni nodo.
 */
#define LLL_DEBUG_LIST(head) \
    do \
    { \
        node_ptr tmp=(head); \
        int idx=0; \
        while(tmp) \
        { \
            LLL_DEBUG_PRINT("Node[%d]: ", idx); \
            LLL_DEBUG_NODE(tmp); \
            tmp=tmp->next; \
            idx++; \
        } \
        if (idx==0) \
        { \
            LLL_DEBUG_PRINT("Empty list\n"); \
        } \
    } while(0)









/*
 * Typedef: node
 * ----------------------------
 * Alias per `struct Node`. Permette di scrivere semplicemente `node` invece di
 * `struct Node` quando si dichiara una variabile nodo.
 *
 * Esempio:
 *   node myNode;   // equivalente a 'struct Node myNode;'
 */

/*
 * Typedef: node_ptr
 * ----------------------------
 * Alias per `struct Node *`. Rappresenta un puntatore a un nodo della lista collegata.
 * Permette di dichiarare puntatori ai nodi in modo più leggibile.
 *
 * Esempio:
 *   node_ptr head = NULL;   // equivalente a 'struct Node *head = NULL;'
 *   head->id = 5;
 *
 * Nota:
 *  - `node_ptr` viene comunemente usato per manipolare liste dinamiche, come inserimenti,
 *    cancellazioni o iterazioni sui nodi.
 */

typedef struct Node node;
typedef struct Node *node_ptr;






/*
 * Funzioni per manipolare liste collegate semplici.
 *
 * Tutte le funzioni ricevono come parametro `head` il puntatore al primo nodo della lista
 * e un `number_id` da inserire in un nuovo nodo. Ritornano il nuovo head della lista
 * (utile in caso di inserimento in testa).
 *
 * Tipi usati:
 *  - node      : alias per struct Node
 *  - node_ptr  : alias per struct Node *, cioè puntatore a nodo
 *
 * Funzioni disponibili:
 *
 * 1) addNodeTail(node_ptr head, int number_id)
 *    - Inserisce un nuovo nodo alla fine della lista.
 *    - Se la lista è vuota (head == NULL), il nuovo nodo diventa la testa.
 *    - Restituisce la testa aggiornata della lista.
 *
 * 2) addNodeHead(node_ptr head, int number_id)
 *    - Inserisce un nuovo nodo all’inizio della lista.
 *    - Il nuovo nodo diventa la nuova testa della lista.
 *    - Restituisce la nuova testa.
 *
 * 3) addNodeMiddle(node_ptr head, int number_id)
 *    - Inserisce un nuovo nodo nella "posizione di mezzo" della lista.
 *    - Se la lista è vuota, il nuovo nodo diventa la testa.
 *    - La posizione di mezzo è calcolata come floor(length/2), cioè metà dei nodi esistenti.
 *    - Restituisce la testa aggiornata della lista.
 *
 * 4) addNodoInPosition(node_ptr head, int number_id, int position)
 *    - Inserisce un nuovo nodo in una posizione specifica della lista (indice 0-based).
 *    - Se la lista è vuota o position == 0, il nuovo nodo diventa la testa.
 *    - Se position >= lunghezza della lista, il nodo viene inserito in coda.
 *    - Altrimenti, il nodo viene inserito esattamente alla posizione indicata.
 *    - Restituisce la testa aggiornata della lista.
 *
 * Nota generale:
 *  - Tutte le funzioni allocano dinamicamente il nuovo nodo usando malloc.
 *  - Se malloc fallisce, le funzioni restituiscono NULL (non gestito in questo esempio).
 *  - La lista collegata è semplice (singly linked list), quindi ogni nodo punta solo al successivo.
 */


node_ptr addNodeTail(node_ptr head, int number_id)
{
    node_ptr new_node=(node_ptr) malloc(sizeof(node));

    if (!new_node) return NULL; // malloc fallita
    new_node->id=number_id;
    new_node->next=NULL;

    if (!head) return new_node; // lista vuota

    node_ptr current=head;
    while (current->next) 
    {
        current=current->next;
    }
    current->next=new_node;
    return head;
}

node_ptr addNodeHead(node_ptr head, int number_id)
{
    node_ptr new_node=(node_ptr) malloc(sizeof(node));
    if (!new_node) return NULL; // malloc fallita
    new_node->id=number_id;
    new_node->next=head; // il nodo punta alla vecchia testa
    return new_node;       // nuovo nodo diventa testa
}

node_ptr addNodeMiddle(node_ptr head, int number_id)
{
    node_ptr new_node=(node_ptr) malloc(sizeof(node));
    if (!new_node) return NULL; // malloc fallita
    new_node->id=number_id;

    if (!head) 
    {
        new_node->next=NULL;
        return new_node; // lista vuota
    }

    // calcolo posizione di mezzo
    node_ptr slow=head;
    node_ptr fast=head;
    while (fast->next && fast->next->next) 
    {
        slow=slow->next;
        fast=fast->next->next;
    }

    // inserimento dopo il nodo slow
    new_node->next=slow->next;
    slow->next=new_node;

    return head;
}


node_ptr addNodoInPosition(node_ptr head, int number_id, int position)
{
    node_ptr new_node=(node_ptr) malloc(sizeof(node));
    
    if (!new_node) return NULL; // malloc fallita
    new_node->id=number_id;
    new_node->next = NULL;

    // inserimento in testa o lista vuota
    if (!head || position <= 0)
    {
        new_node->next=head;
        return new_node;
    }

    node_ptr current=head;
    int index=0;

    // scorriamo la lista fino alla posizione precedente o fine lista
    while (current->next && index < position - 1)
    {
        current=current->next;
        index++;
    }

    // inserimento del nuovo nodo
    new_node->next=current->next;
    current->next=new_node;

    return head;
}






#endif // __LINKED_LIST_LIBRARY_H
