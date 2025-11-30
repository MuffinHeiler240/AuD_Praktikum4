#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree234.h"

// Hauptprogramm
int main(void) {
    Node* root = NULL;
    initTree(&root);

    // Zufallszahlengenerator initialisieren
    srand((unsigned int)time(NULL));

    printf("=== 2-3-4-Baum Implementierung ===\n\n");
    printf("Fuege 500 zufaellige Zahlen ein...\n");

    int insertedCount = 0;
    while (insertedCount < 500) {
        int randomValue = rand() % 10000; // Zufallszahl zwischen 0 und 9999

        int comparisons = 0;
        if (!search(root, randomValue, &comparisons)) {
            insert(&root, randomValue);
            insertedCount++;
        }
    }

    printf("Erfolgreich %d Zahlen eingefuegt.\n\n", insertedCount);

    // Inorder-Ausgabe
    printf("Inorder-Ausgabe (sortiert):\n");
    printInOrder(root);
    printf("\n\n");

    // Baumstatistiken
    printf("Baumhoehe: %d\n", getHeight(root));
    printf("Knotenanzahl: %d\n\n", countNodes(root));

    // Interaktives Menü
    int choice;
    do {
        printf("\n=== Menue ===\n");
        printf("1 - Zahl suchen\n");
        printf("2 - Neue Zahl einfuegen\n");
        printf("3 - Baum anzeigen\n");
        printf("4 - Baumstatistik\n");
        printf("0 - Programm beenden\n");
        printf("Ihre Wahl: ");

        if (scanf("%d", &choice) != 1) {
            // Eingabepuffer leeren bei ungültiger Eingabe
            while (getchar() != '\n');
            choice = -1;
            printf("Ungueltige Eingabe!\n");
            continue;
        }

        switch (choice) {
            case 1: {
                int searchValue;
                printf("Zu suchende Zahl eingeben: ");
                scanf("%d", &searchValue);

                int comparisons = 0;
                bool found = search(root, searchValue, &comparisons);

                if (found) {
                    printf("-> Zahl %d GEFUNDEN\n", searchValue);
                } else {
                    printf("-> Zahl %d NICHT GEFUNDEN\n", searchValue);
                }
                printf("Vergleiche: %d\n", comparisons);
                break;
            }
            case 2: {
                int newValue;
                printf("Neue Zahl eingeben: ");
                scanf("%d", &newValue);

                int comparisons = 0;
                if (search(root, newValue, &comparisons)) {
                    printf("-> Zahl %d existiert bereits (Duplikat)\n", newValue);
                } else {
                    insert(&root, newValue);
                    printf("-> Zahl %d erfolgreich eingefuegt\n", newValue);
                }
                break;
            }
            case 3: {
                printf("Baum (Inorder):\n");
                printInOrder(root);
                printf("\n");
                break;
            }
            case 4: {
                printf("=== Baumstatistik ===\n");
                printf("Baumhoehe: %d\n", getHeight(root));
                printf("Knotenanzahl: %d\n", countNodes(root));
                break;
            }
            case 0:
                printf("Programm wird beendet...\n");
                break;
            default:
                printf("Ungueltige Wahl!\n");
        }
    } while (choice != 0);

    // Speicher freigeben
    freeTree(root);

    return 0;
}