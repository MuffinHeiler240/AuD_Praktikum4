#include "tree234.h"
#include <stdio.h>
#include <stdlib.h>

// Erstellt einen neuen leeren Knoten
Node* createNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Speicherzuweisung fehlgeschlagen!\n");
        exit(1);
    }
    node->keyCount = 0;
    node->isLeaf = true;
    for (int i = 0; i < 4; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Initialisiert den Baum
void initTree(Node** root) {
    *root = NULL;
}

// Hilfsfunktion: Fügt einen Schlüssel sortiert in einen Knoten ein
static void insertKeyIntoNode(Node* node, int key, Node* rightChild) {
    int i = node->keyCount - 1;

    // Verschiebe größere Schlüssel nach rechts
    while (i >= 0 && node->keys[i] > key) {
        node->keys[i + 1] = node->keys[i];
        node->children[i + 2] = node->children[i + 1];
        i--;
    }

    node->keys[i + 1] = key;
    node->children[i + 2] = rightChild;
    node->keyCount++;
}

// Split eines vollen 4-Knotens
static void splitChild(Node* parent, int index) {
    Node* fullChild = parent->children[index];
    Node* newChild = createNode();

    newChild->isLeaf = fullChild->isLeaf;
    newChild->keyCount = 1;

    // Rechter Knoten bekommt den dritten Schlüssel
    newChild->keys[0] = fullChild->keys[2];

    // Wenn nicht Blatt, verschiebe Kinder
    if (!fullChild->isLeaf) {
        newChild->children[0] = fullChild->children[2];
        newChild->children[1] = fullChild->children[3];
    }

    // Mittlerer Schlüssel wandert nach oben
    int middleKey = fullChild->keys[1];

    // Linker Knoten behält ersten Schlüssel
    fullChild->keyCount = 1;
    fullChild->children[2] = NULL;
    fullChild->children[3] = NULL;

    // Füge mittleren Schlüssel in Parent ein
    insertKeyIntoNode(parent, middleKey, newChild);
}

// Sucht nach einem Wert und zählt Vergleiche
bool search(Node* node, int value, int* comparisons) {
    if (node == NULL) {
        return false;
    }

    int i = 0;
    // Durchsuche Schlüssel im aktuellen Knoten

    (*comparisons)++;
    while (i < node->keyCount) {
        (*comparisons)++;
        if (value == node->keys[i]) {
            return true;
        } else if (value < node->keys[i]) {
            break;
        }
        i++;
    }

    // Wenn Blatt, wurde Wert nicht gefunden
    if (node->isLeaf) {
        return false;
    }

    // Rekursiv im passenden Kind suchen
    return search(node->children[i], value, comparisons);
}

// Fügt einen Wert in den Baum ein (Top-Down)
void insert(Node** root, int value) {
    // Duplikatsprüfung
    int comparisons = 0;
    if (search(*root, value, &comparisons)) {
        return; // Duplikat, nicht einfügen
    }

    // Leerer Baum
    if (*root == NULL) {
        *root = createNode();
        (*root)->keys[0] = value;
        (*root)->keyCount = 1;
        return;
    }

    // Wurzel ist 4-Knoten: Split erforderlich
    if ((*root)->keyCount == 3) {
        Node* newRoot = createNode();
        newRoot->isLeaf = false;
        newRoot->children[0] = *root;
        splitChild(newRoot, 0);
        *root = newRoot;
    }

    // Abstieg zum Blatt
    Node* current = *root;

    while (!current->isLeaf) {
        int i = 0;
        // Finde korrektes Kind
        while (i < current->keyCount && value > current->keys[i]) {
            i++;
        }

        // Prüfe, ob Zielkind ein 4-Knoten ist
        if (current->children[i]->keyCount == 3) {
            splitChild(current, i);

            // Nach Split: Bestimme neues Zielkind
            if (value > current->keys[i]) {
                i++;
            }
        }

        current = current->children[i];
    }

    // Einfügen im Blatt
    insertKeyIntoNode(current, value, NULL);
}

// Inorder-Traversierung (sortierte Ausgabe)
void printInOrder(Node* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->keyCount; i++) {
        printInOrder(node->children[i]);
        printf("%d ", node->keys[i]);
    }
    printInOrder(node->children[node->keyCount]);
}

// Berechnet die Baumhöhe
int getHeight(Node* node) {
    if (node == NULL) {
        return 0;
    }

    if (node->isLeaf) {
        return 1;
    }

    // Folge dem linkesten Kind
    return 1 + getHeight(node->children[0]);
}

// Zählt alle Knoten im Baum
int countNodes(Node* node) {
    if (node == NULL) {
        return 0;
    }

    int count = 1; // Aktueller Knoten

    // Zähle alle Kinder
    for (int i = 0; i <= node->keyCount; i++) {
        count += countNodes(node->children[i]);
    }

    return count;
}

// Gibt den Speicher des Baums frei
void freeTree(Node* node) {
    if (node == NULL) {
        return;
    }

    // Rekursiv alle Kinder freigeben
    for (int i = 0; i <= node->keyCount; i++) {
        freeTree(node->children[i]);
    }

    free(node);
}

