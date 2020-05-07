#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *f;
typedef struct
{
    char words[30];
    struct Node *right;
    struct Node *left;
} Node;

typedef struct
{
    Node *Root;
} tree;
int MAX(int x,int y)
{
    return x > y ? x : y;
}
void init(tree*T)
{
    T->Root=NULL;
}
int size(Node *Root)
{
    return (Root == NULL) ? 0 :1 + size(Root->left) + size(Root->right);
}
int height(Node *Root)
{
    return (Root == NULL) ? -1 :1 + MAX(height(Root->left), height(Root->right));
}
void AddNode(Node**node,char*input)
{
    if(*node==NULL)
    {
        Node *nodenew=malloc(sizeof(Node));
        strcpy(nodenew->words,input);
        nodenew->left=NULL;
        nodenew->right=NULL;
        *node=nodenew;
    }
    else if(strcmp((*node)->words,input)>0)
    {
        AddNode(&((*node)->left),input);
    }
    else AddNode(&((*node)->right),input);
}
Node* newBSTNode(char*input )
{
    Node *node = malloc(sizeof(Node));
    node->words[30]=malloc(30*sizeof(char));
    strcpy(node->words,input);
    node->left = node->right = NULL;
    return node;
}
Node* searchInBST(Node*Root,char*word)
{
    if(strcmp(Root->words,word)>0)
    {
        if(Root->left==NULL)
            return Root;
            else return searchInBST(Root->left,word);
    }
    if(strcmp(Root->words,word)<0)
    {
        if(Root->right==NULL)
            return Root;
            else return searchInBST(Root->right,word);

    }
}

void ReadFile(Node** Root)
{
    char input[30];
    f=fopen("abc.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%s\n",&input);
        AddNode(Root,input);
    }
    fclose(f);
}
char* GetPrev(Node *Root,Node* nodenew)
{
    if(nodenew->left!=NULL)
    {
        nodenew=nodenew->left;
        while(nodenew->right!=NULL)
            nodenew= nodenew->right;
        return nodenew->words;
    }
    else
    {
        Node *nextNode=NULL;
        Node *prevNode=Root;
        while(prevNode!=nodenew)
        {
            if(strcmp(nodenew->words,prevNode->words)>0)
            {
                nextNode=prevNode;
                prevNode=prevNode->right;
            }
            else
                prevNode=prevNode->left;
        }
        return nextNode->words;
    }
}
char* GetNext(Node *Root,Node* nodenew)
{
    if(nodenew->right!=NULL)
    {
        nodenew=nodenew->right;
        while(nodenew->left!=NULL)
            nodenew= nodenew->left;
        return nodenew->words;
    }
    else
    {
        Node *nextNode=NULL;
        Node *prevNode=Root;
        while(prevNode!=nodenew)
        {
            if(strcmp(nodenew->words,prevNode->words)<0)
            {
                nextNode=prevNode;
                prevNode=prevNode->left;
            }
            else
                prevNode=prevNode->right;
        }
        return nextNode->words;
    }
}

int main()
{
    char sentence[100];
    tree r;
    init(&r);
    ReadFile(&r.Root);
    printf("height of tree= %d\n",height(r.Root));
    printf("the size of the tree is= %d\n",size(r.Root));
    printf("enter the sentence that you want to spell-check\n");
    scanf("%[^\n]s",sentence);
    Node *searcher;
    char* token=strtok(sentence," ");
    while(token!=NULL){
        searcher=searchInBST(r.Root,token);
        if(searcher==NULL)
            printf("%s     CORRECT\n",token);
        else
            printf("your word is %s     first suggestion is %s    second suggestion is %s       third suggestion is %s\n",token,searcher->words,GetNext(r.Root,searcher),GetPrev(r.Root,searcher));
        token=strtok(NULL," ");
    }
    return 0;
}
