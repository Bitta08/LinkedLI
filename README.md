

# LLL - Linked List Library

**Version:** 0.1  
**License:** [GNU GPLv3](https://www.gnu.org/licenses/)  

`LLL` è una libreria in C per la gestione di liste collegate semplici (*singly linked list*), con funzioni di debug multipiattaforma (Windows, Linux, macOS).  
Questo README fornisce una panoramica completa, esempi pratici e consigli sul debug.

---

## Sommario

- [Cos'è una linked list](#cosè-una-linked-list)
- [Struttura Node](#struttura-node)
- [Diagramma della lista](#diagramma-della-lista)
- [Debug e stampa](#debug-e-stampa)
- [Funzioni principali](#funzioni-principali)
- [Esempi d'uso](#esempi-duso)
- [Consigli di performance](#consigli-di-performance)
- [Licenza](#licenza)

---

## Cos'è una linked list

Una *linked list* è una struttura dati composta da nodi, in cui ogni nodo contiene:

1. Un valore o identificatore (`id`)
2. Un puntatore al nodo successivo (`next`)

**Vantaggi:**

- Dimensione dinamica: non serve conoscere il numero di elementi a priori.
- Inserimenti e rimozioni efficienti senza spostare blocchi di memoria.

**Svantaggi:**

- Accesso sequenziale: non è possibile accedere direttamente a un nodo intermedio.
- Overhead di memoria maggiore rispetto ad array statici (necessario spazio per i puntatori).

---

## Struttura Node

```c
struct Node {
    int id;           // Identificatore del nodo
    struct Node *next; // Puntatore al nodo successivo
};

typedef struct Node node;
typedef struct Node* node_ptr;
````

* `node` è un alias per `struct Node`
* `node_ptr` è un alias per `struct Node*`

**Creazione manuale di un nodo:**

```c
node_ptr n = malloc(sizeof(node));
n->id = 10;
n->next = NULL;
```

---

## Diagramma della lista

Una lista collegata con 3 nodi può essere rappresentata così:

```
head
 |
 v
+----+      +----+      +----+
| id | ---> | id | ---> | id | ---> NULL
+----+      +----+      +----+
```

Esempio con valori reali:

```
head
 |
 v
+----+      +----+      +----+
| 1  | ---> | 4  | ---> | 2  | ---> NULL
+----+      +----+      +----+
```

---

## Debug e stampa

LLL include macro per il debug multipiattaforma:

### Stampare un singolo nodo

```c
LLL_DEBUG_NODE(n);
```

Output tipico:

```
Node at 0x7ffee2c -> id: 10, next: NULL
```

### Stampare l'intera lista

```c
LLL_DEBUG_LIST(head);
```

Output tipico:

```
Node[0]: Node at 0x7ffee2c -> id: 1, next: 0x7ffee3c
Node[1]: Node at 0x7ffee3c -> id: 4, next: 0x7ffee4c
Node[2]: Node at 0x7ffee4c -> id: 2, next: NULL
```

---

## Funzioni principali

### 1. Inserimento in testa

```c
head = addNodeHead(head, 5);
```

* Il nuovo nodo diventa la testa
* `next` punta alla vecchia testa

### 2. Inserimento in coda

```c
head = addNodeTail(head, 10);
```

* Aggiunge un nodo alla fine della lista
* Se la lista è vuota, diventa la testa

### 3. Inserimento a metà lista

```c
head = addNodeMiddle(head, 7);
```

* Inserisce un nodo nella posizione centrale (`floor(length/2)`)

### 4. Inserimento in posizione specifica

```c
head = addNodoInPosition(head, 8, 2);
```

* Inserisce un nodo alla posizione indicata (indice 0-based)
* Se `position` > lunghezza lista → inserimento in coda
* Se `position` <= 0 → inserimento in testa

---

## Esempio completo

```c
#include "lll.h"
#include <stdio.h>

int main() {
    node_ptr head = NULL;

    head = addNodeHead(head, 1);
    head = addNodeTail(head, 2);
    head = addNodeMiddle(head, 3);
    head = addNodoInPosition(head, 4, 1);

    LLL_DEBUG_LIST(head);

    return 0;
}
```

**Output previsto:**

```
Node[0]: Node at 0x7ffee2c -> id: 1, next: 0x7ffee3c
Node[1]: Node at 0x7ffee3c -> id: 4, next: 0x7ffee4c
Node[2]: Node at 0x7ffee4c -> id: 3, next: 0x7ffee5c
Node[3]: Node at 0x7ffee5c -> id: 2, next: NULL
```

**Diagramma ASCII della lista finale:**

```
head
 |
 v
+----+      +----+      +----+      +----+
| 1  | ---> | 4  | ---> | 3  | ---> | 2  | ---> NULL
+----+      +----+      +----+      +----+
```


---

## Licenza

Questo programma è distribuito sotto la **GNU General Public License v3**:

* Puoi usarlo, modificarlo e ridistribuirlo
* Non è fornita alcuna garanzia

Per i dettagli completi: [GPL v3](https://www.gnu.org/licenses/).


