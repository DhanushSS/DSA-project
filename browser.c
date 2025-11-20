#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "browser.h"

void initBrowser(Browser *b) {
    b->pageCount = 0;
    b->hasCurrent = 0;
    b->backStack.top = -1;
    b->forwardStack.top = -1;
    b->graph.count = 0;
    b->wordRoot = NULL;
    initCache(&b->cache);
}

void push(Stack *s, Page p) {
    if (s->top < MAX_PAGES - 1)
        s->data[++s->top] = p;
}

Page pop(Stack *s) {
    return s->data[s->top--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void addPage(Browser *b, const char *url, const char *title) {
    for (int i = 0; i < b->pageCount; i++)
        if (strcmp(b->pages[i].url, url) == 0) {
            strncpy(b->pages[i].title, title, MAX_TITLE - 1);
            return;
        }

    if (b->pageCount >= MAX_PAGES) return;

    strncpy(b->pages[b->pageCount].url, url, MAX_URL - 1);
    strncpy(b->pages[b->pageCount].title, title, MAX_TITLE - 1);

    strncpy(b->graph.urls[b->graph.count], url, MAX_URL - 1);

    b->graph.count++;
    b->pageCount++;

    indexWords(b, title);
}

void visitPage(Browser *b, const char *url) {
    Page *p = NULL;

    for (int i = 0; i < b->pageCount; i++)
        if (strcmp(b->pages[i].url, url) == 0) {
            p = &b->pages[i];
            break;
        }

    if (!p) {
        printf("Page not found. Add it first.\n");
        return;
    }

    if (b->hasCurrent)
        push(&b->backStack, b->currentPage);

    b->currentPage = *p;
    b->hasCurrent = 1;
    b->forwardStack.top = -1;

    printf("Visiting %s (%s)\n", p->url, p->title);

    if (findInCache(&b->cache, url))
        printf("(Cache Hit)\n");
    else {
        printf("(Cache Miss -> Adding)\n");
        insertCache(&b->cache, url);
    }
}

void goBack(Browser *b) {
    if (!b->hasCurrent || isEmpty(&b->backStack)) {
        printf("Back stack empty.\n");
        return;
    }

    push(&b->forwardStack, b->currentPage);
    b->currentPage = pop(&b->backStack);

    printf("Back to %s\n", b->currentPage.url);
}

void goForward(Browser *b) {
    if (!b->hasCurrent || isEmpty(&b->forwardStack)) {
        printf("Forward stack empty.\n");
        return;
    }

    push(&b->backStack, b->currentPage);
    b->currentPage = pop(&b->forwardStack);

    printf("Forward to %s\n", b->currentPage.url);
}

BSTNode* insertBST(BSTNode *root, const char *word) {
    if (!root) {
        BSTNode *n = malloc(sizeof(BSTNode));
        strncpy(n->word, word, MAX_WORD - 1);
        n->frequency = 1;
        n->left = n->right = NULL;
        return n;
    }
    int c = strcmp(word, root->word);
    if (c == 0) root->frequency++;
    else if (c < 0) root->left = insertBST(root->left, word);
    else root->right = insertBST(root->right, word);
    return root;
}

BSTNode* searchBST(BSTNode *root, const char *word) {
    if (!root) return NULL;
    int c = strcmp(word, root->word);
    if (c == 0) return root;
    if (c < 0) return searchBST(root->left, word);
    return searchBST(root->right, word);
}

void indexWords(Browser *b, const char *title) {
    char temp[500];
    strncpy(temp, title, 499);
    char *w = strtok(temp, " ");
    while (w) {
        b->wordRoot = insertBST(b->wordRoot, w);
        w = strtok(NULL, " ");
    }
}

void searchKeyword(Browser *b, const char *word) {
    BSTNode *res = searchBST(b->wordRoot, word);
    if (res) printf("Found \"%s\" freq = %d\n", word, res->frequency);
    else printf("Word not found.\n");
}

void collectWords(BSTNode *root, PQNode arr[], int *idx) {
    if (!root) return;
    collectWords(root->left, arr, idx);
    strncpy(arr[*idx].word, root->word, MAX_WORD - 1);
    arr[*idx].relevance = root->frequency;
    (*idx)++;
    collectWords(root->right, arr, idx);
}

void pqPush(PriorityQueue *pq, char *word, int relevance) {
    if (pq->size >= 200) return;
    strncpy(pq->arr[pq->size].word, word, MAX_WORD - 1);
    pq->arr[pq->size].relevance = relevance;
    pq->size++;

    int i = pq->size - 1;
    while (i > 0 && pq->arr[i].relevance > pq->arr[(i - 1) / 2].relevance) {
        PQNode t = pq->arr[i];
        pq->arr[i] = pq->arr[(i - 1) / 2];
        pq->arr[(i - 1) / 2] = t;
        i = (i - 1) / 2;
    }
}

PQNode pqPop(PriorityQueue *pq) {
    PQNode out = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;

    int i = 0;
    while (1) {
        int m = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < pq->size && pq->arr[l].relevance > pq->arr[m].relevance) m = l;
        if (r < pq->size && pq->arr[r].relevance > pq->arr[m].relevance) m = r;
        if (m == i) break;
        PQNode t = pq->arr[i];
        pq->arr[i] = pq->arr[m];
        pq->arr[m] = t;
        i = m;
    }
    return out;
}

void rankQuery(Browser *b, const char *query) {
    PriorityQueue pq;
    pq.size = 0;

    char temp[300];
    strncpy(temp, query, 299);
    char *w = strtok(temp, " ");
    while (w) {
        BSTNode *res = searchBST(b->wordRoot, w);
        if (res) pqPush(&pq, w, res->frequency);
        w = strtok(NULL, " ");
    }

    printf("\n--- Relevance Ranking ---\n");
    while (pq.size > 0) {
        PQNode n = pqPop(&pq);
        printf("%s (score = %d)\n", n.word, n.relevance);
    }
}

void initCache(HashTable *ht) {
    for (int i = 0; i < CACHE_SIZE; i++)
        ht->table[i].used = 0;
}

int hash(const char *str) {
    int h = 0;
    for (int i = 0; str[i]; i++)
        h = (h * 31 + str[i]) % CACHE_SIZE;
    return h;
}

void insertCache(HashTable *ht, const char *url) {
    int idx = hash(url);
    for (int i = 0; i < CACHE_SIZE; i++) {
        int p = (idx + i) % CACHE_SIZE;
        if (!ht->table[p].used) {
            strncpy(ht->table[p].url, url, MAX_URL - 1);
            ht->table[p].used = 1;
            return;
        }
    }
}

int findInCache(HashTable *ht, const char *url) {
    int idx = hash(url);
    for (int i = 0; i < CACHE_SIZE; i++) {
        int p = (idx + i) % CACHE_SIZE;
        if (!ht->table[p].used) return 0;
        if (strcmp(ht->table[p].url, url) == 0) return 1;
    }
    return 0;
}

void showCache(HashTable *ht) {
    printf("\n--- Cached URLs ---\n");
    for (int i = 0; i < CACHE_SIZE; i++)
        if (ht->table[i].used)
            printf("%s\n", ht->table[i].url);
}

void addLink(Browser *b, const char *from, const char *to) {
    int f = -1, t = -1;

    for (int i = 0; i < b->graph.count; i++) {
        if (strcmp(b->graph.urls[i], from) == 0) f = i;
        if (strcmp(b->graph.urls[i], to) == 0) t = i;
    }

    if (f != -1 && t != -1)
        b->graph.adj[f][t] = 1;
}

void printGraph(Browser *b) {
    printf("\n--- Graph ---\n");
    for (int i = 0; i < b->graph.count; i++) {
        printf("%s -> ", b->graph.urls[i]);
        for (int j = 0; j < b->graph.count; j++)
            if (b->graph.adj[i][j])
                printf("%s ", b->graph.urls[j]);
        printf("\n");
    }
}

void calculatePageRank(Browser *b) {
    printf("\n--- PageRank (Out-degree) ---\n");
    for (int i = 0; i < b->graph.count; i++) {
        int out = 0;
        for (int j = 0; j < b->graph.count; j++)
            if (b->graph.adj[i][j]) out++;
        printf("%s : %d\n", b->graph.urls[i], out);
    }
}
