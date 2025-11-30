#ifndef TREE234_H
#define TREE234_H

#include <stdbool.h>

// Knotenstruktur für 2-3-4-Baum
typedef struct Node {
    int keys[3];              // bis zu 3 sortierte Schlüssel
    int keyCount;             // 1..3
    struct Node* children[4]; // 2..4 Kinder oder NULL
    bool isLeaf;
} Node;

// Funktionsprototypen

/**
 * Erstellt einen neuen leeren Knoten
 */
Node* createNode();

/**
 * Initialisiert den Baum
 */
void initTree(Node** root);

/**
 * Sucht nach einem Wert und zählt Vergleiche
 * @param node Wurzelknoten
 * @param value Zu suchender Wert
 * @param comparisons Zeiger auf Vergleichszähler
 * @return true wenn gefunden, false sonst
 */
bool search(Node* node, int value, int* comparisons);

/**
 * Fügt einen Wert in den Baum ein (Top-Down mit automatischem Split)
 * Duplikate werden automatisch ignoriert
 * @param root Zeiger auf Wurzelknoten
 * @param value Einzufügender Wert
 */
void insert(Node** root, int value);

/**
 * Inorder-Traversierung (sortierte Ausgabe)
 * @param node Wurzelknoten
 */
void printInOrder(Node* node);

/**
 * Berechnet die Baumhöhe
 * @param node Wurzelknoten
 * @return Höhe des Baums
 */
int getHeight(Node* node);

/**
 * Zählt alle Knoten im Baum
 * @param node Wurzelknoten
 * @return Anzahl der Knoten
 */
int countNodes(Node* node);

/**
 * Gibt den Speicher des Baums frei
 * @param node Wurzelknoten
 */
void freeTree(Node* node);

#endif // TREE234_H

