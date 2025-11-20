#ifndef BROWSER_H
#define BROWSER_H

#define MAX_PAGES 100
#define MAX_TITLE 200
#define MAX_URL 200
#define MAX_WORD 50
#define CACHE_SIZE 101

typedef struct Page {
    char url[MAX_URL];
    char title[MAX_TITLE];
} Page;

typedef struct Stack {
    Page data[MAX_PAGES];
    int top;
} Stack;

typedef struct Graph {
    int adj[MAX_PAGES][MAX_PAGES];
    int count;
    char urls[MAX_PAGES][MAX_URL];
} Graph;

typedef struct BSTNode {
    char word[MAX_WORD];
    int frequency;
    struct BSTNode *left, *right;
} BSTNode;

typedef struct PQNode {
    char word[MAX_WORD];
    int relevance;
} PQNode;

typedef struct PriorityQueue {
    PQNode arr[200];
    int size;
} PriorityQueue;

typedef struct CacheEntry {
    char url[MAX_URL];
    int used;
} CacheEntry;

typedef struct HashTable {
    CacheEntry table[CACHE_SIZE];
} HashTable;

typedef struct Browser {
    Page pages[MAX_PAGES];
    int pageCount;

    Page currentPage;
    int hasCurrent;

    Stack backStack;
    Stack forwardStack;

    Graph graph;

    BSTNode *wordRoot;
    HashTable cache;
} Browser;


void initBrowser(Browser *b);

void push(Stack *s, Page p);
Page pop(Stack *s);
int isEmpty(Stack *s);

void addPage(Browser *b, const char *url, const char *title);
void visitPage(Browser *b, const char *url);

void goBack(Browser *b);
void goForward(Browser *b);

BSTNode* insertBST(BSTNode *root, const char *word);
BSTNode* searchBST(BSTNode *root, const char *word);
void indexWords(Browser *b, const char *title);
void searchKeyword(Browser *b, const char *word);

void collectWords(BSTNode *root, PQNode arr[], int *idx);
void pqPush(PriorityQueue *pq, char *word, int relevance);
PQNode pqPop(PriorityQueue *pq);
void rankQuery(Browser *b, const char *query);

void initCache(HashTable *ht);
int hash(const char *str);
void insertCache(HashTable *ht, const char *url);
int findInCache(HashTable *ht, const char *url);
void showCache(HashTable *ht);

void addLink(Browser *b, const char *from, const char *to);
void printGraph(Browser *b);
void calculatePageRank(Browser *b);

#endif
