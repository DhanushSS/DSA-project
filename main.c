#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "browser.h"

void menu() {
    printf("\n============================\n");
    printf("      MINI BROWSER MENU\n");
    printf("============================\n");
    printf("1. Add Page\n");
    printf("2. Visit Page\n");
    printf("3. Go Back\n");
    printf("4. Go Forward\n");
    printf("5. Search Keyword in BST\n");
    printf("6. Query Ranking (Priority Queue)\n");
    printf("7. Display Cache\n");
    printf("8. Add Link\n");
    printf("9. Print Graph\n");
    printf("10. PageRank\n");
    printf("11. Exit\n");
    printf("============================\n");
    printf("Enter choice: ");
}

int main() {
    Browser b;
    initBrowser(&b);

    int choice;
    char url1[200], url2[200], title[200], word[200];

    while (1) {
        menu();
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf(" %[^\n]", url1);
                printf("Enter Title: ");
                scanf(" %[^\n]", title);
                addPage(&b, url1, title);
                break;

            case 2:
                printf("Enter URL: ");
                scanf(" %[^\n]", url1);
                visitPage(&b, url1);
                break;

            case 3:
                goBack(&b);
                break;

            case 4:
                goForward(&b);
                break;

            case 5:
                printf("Enter word: ");
                scanf(" %[^\n]", word);
                searchKeyword(&b, word);
                break;

            case 6:
                printf("Enter search query: ");
                scanf(" %[^\n]", word);
                rankQuery(&b, word);
                break;

            case 7:
                showCache(&b.cache);
                break;

            case 8:
                printf("From URL: ");
                scanf(" %[^\n]", url1);
                printf("To URL: ");
                scanf(" %[^\n]", url2);
                addLink(&b, url1, url2);
                break;

            case 9:
                printGraph(&b);
                break;

            case 10:
                calculatePageRank(&b);
                break;

            case 11:
                printf("Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
