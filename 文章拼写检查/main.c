//
//  main.c
//  拼写检查
//
//  Created by Phantom on 2019/5/21.
//  Copyright © 2019 辛巴达. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 50
#define NEWWORD (Dtree *)malloc(sizeof(Dtree))
#define NEWMIS (Mlist *)malloc(sizeof(Mlist))
#define NEWPP (Position *)malloc(sizeof(Position))

typedef struct DictionaryTree{      //单词查找树
    char word[MAXWORD];
    struct DictionaryTree *left, *right, *parent;
} Dtree;
typedef struct hashnode{            //单词首字母哈希表
    Dtree *root;
} hash;
typedef struct MistakewordList{     //错误的单词
    char word[MAXWORD];
    int count;
    struct position *pp;
    struct MistakewordList *next, *last;
} Mlist;
typedef struct position{
    int posi;
    struct position *next;
} Position;
hash hashdic[26];
Mlist list[25000];
int top = 0;
int getword(char *str, FILE *in, int *count);
void insert(Dtree *bstnow, char *str);
int search(Dtree *root, char *word);
void order(char *word, int pp);
void sort(Mlist *now);

int main(int argc, const char * argv[]) {
    FILE *dic = fopen("dictionary.txt", "r"), *art = fopen("article.txt", "r");
    if (dic == NULL) {printf("Dictionary open failed!\n"); return -1;}
    if (dic == NULL) {printf("Article open failed!\n");return -1;}
    char word[MAXWORD];
    Mlist *p = NULL;
    Position *pp =NULL;
    int i, count = 0;
    for (i = 0; i < 26; ++ i)
        hashdic[i].root = NULL;
    while (getword(word, dic, &count)) {
        insert(hashdic[word[0] - 'a'].root, word);
    }
    count = 0;
    i = -1;
    while (getword(word, art, &count)) {
        ++ i;
        if (search(hashdic[word[0] - 'a'].root, word)){
            
        }
    }
    FILE *out = fopen("misspelling.txt", "w");
    
    fclose(dic);
    fclose(art);
    fclose(out);
    return 0;
}

int getword(char *str, FILE *in, int *count){
    int i = 0;
    char ch;
    while ((ch = fgetc(in)) != EOF){
        ++ *count;
        if (!isalpha(ch))
            continue;
        while (isalpha(ch)){
            -- *count;
            str[i ++] = tolower(ch);
            ch = fgetc(in);
        }
        str[i] = '\0';
        return 1;
    }
    return 0;
}

void insert(Dtree *bstnow, char *str){
    if (bstnow == NULL) {
        Dtree *p = NEWWORD;
        p->left = NULL;
        p->right = NULL;
        strcpy(p->word, str);
        hashdic[str[0] - 'a'].root = p;
        return;
    }
    if (bstnow->right == NULL){
        Dtree *p = NEWWORD;
        p->left = NULL;
        p->right = NULL;
        strcpy(p->word, str);
        bstnow->right = p;
        return;
    }
    else insert(bstnow->right, str);
}

int search(Dtree *root, char *word){
    if (root == NULL) {
        return 1;
    }
    Dtree *p;
    for (p = root; p != NULL; p = p->right) {
        if (strcmp(p->word, word)>0)
            return 1;
        else if(!strcmp(p->word, word))
            return 0;
    }
    return 1;
}

void order(char *word, int pp){
    Mlist *p, *q;
    Position *o = NULL, *r;
    if (head->next == NULL) {
        q = NEWMIS;
        r = NEWPP;
        q->pp = r;
        r->posi = pp;
        strcpy(q->word, word);
        q->count = 1;
        q->last = head;
        head->next = q;
        q->next = NULL;
        return;
    }
    for (p = head; p != NULL; p = p->next) {
        if (!strcmp(p->word,word)) {
            ++ p->count;
            if(p->count>=p->last->count){
                for (o = p->pp; o->next != NULL; o = o->next)
                    ;
                r = NEWPP;
                r->posi = pp;
                o->next = r;
                p->last->next = p->next;
                if (p->next != NULL) {
                    p->next->last = p->last;
                }
                sort(p);
            }
            return;
        }
        q = p;
    }
    p = q;
    for (; strcmp(p->word,word) < 0 && p->last != NULL; p = p->last)
        ;
    q = NEWMIS;
    r = NEWPP;
    q->pp = r;
    r->posi = pp;
    strcpy(q->word, word);
    q->count = 1;
    if (p->last == NULL) {
        q->next = head->next;
        q->last = q;
        q->last = head;
        head->next = q;
        return;
    }
    p->last->next = q;
    q->last = p->last;
    q->next = p;
    p->last = q;
}

void sort(Mlist *now){
    Mlist *p;
    for (p = head; p != NULL; p = p->next) {
        if (now->count > p->count || (now->count == p->count && !strcmp(now->word,p->word))) {
            now->next = p;
            now->last = p->last;
            if (p->last == NULL) {
                head->next = now;
                now->last = head;
                return;
            }
            p->last->next = now;
            p->last = now;
            return;
        }
    }
}
