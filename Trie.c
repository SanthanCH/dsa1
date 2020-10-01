#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Trienode{
    struct Trienode* Children[26];
    bool endofword;
    int counter;
}Trie;

Trie* newnode(){
    Trie* newNode = (Trie*)malloc(sizeof(Trie));
    newNode->endofword = false;
    newNode->counter=0;
    for(int i=0;i<26;i++) newNode->Children[i] = NULL;
    return newNode;
}

void insert(Trie* root,char *str){
    Trie* temp = root;
    for(int i=0;i<strlen(str);i++){
        int index = str[i] - 'a';

        if(!temp->Children[i]) temp->Children[i] = newnode();
        temp = temp->Children[i];
    }
    temp->endofword = true;
    temp->counter++;
}

bool search(Trie* root,char *str){
    Trie* temp = root;
    for(int i=0;i<strlen(str);i++){
        int indec = str[i] - 'a';

        if(!temp->Children[i]) return false;
        temp = temp->Children[i];
    }
    if(temp!=NULL && temp->endofword) return true;
    else return false;
}

bool isempty(Trie *parent){
    for(int i=0;i<26;i++) if(parent->Children[i]) return false;
    return true;
}

Trie* delete(Trie* root,char *str,int n){
    if(n==strlen(str)){
        if(root->counter>1) root->counter--;
        else{
            root->endofword=false;
            root->counter=0;
            if(isempty(root)){
                free(root);
                root=NULL;
            }
        }
        return root;
    }
    int index=str[n++]-'a';
    root->Children[index]=delete(root->Children[index],str,n);
    if(isempty(root) && !root->endofword){
        free(root);
        root=NULL;
    }
    return root;
}

int main(){
    Trie *root = newnode();
    int flag,temp;
    char str[10000];
    while(1){
        printf("\n\nKindly chose your choice\n1-insert\t2-search\t3-delete\t4-exit\n\n");
        scanf("%d",&flag);
        switch(flag){
            case 1:
                printf("Enter 1 to insert from a file. 0 to insert from stdin\n");
                scanf("%d",&temp);
                if(temp==1)
                {
                    printf("Enter the name of the file\n");
                    char name[10000];
                    scanf("%s",name);
                    FILE *f;
                    f= fopen(name,"r");
                    if(f==NULL) printf("Sorry buddy! We couldn't find a file with that name\n");
                    else{
                        while(fscanf(f,"%s",str)!=EOF) insert(root,str);
                        fclose(f);
                    }
                }
                else
                {
                    printf("Enter the string to insert\n");
                    scanf("%s",str);
                    insert(root,str);
                }
                break;
            case 2:
                printf("Enter the string to search\n");
                scanf("%s",str);
                if(search(root,str)) printf("Given string found!\n");
                else printf("Sorry user! We couldn't find the given string!\n");
                   break;
            case 3:
                printf("Enter the string to delete\n");
                scanf("%s",str);
                if(search(root,str)) root = delete(root,str,0);
                   else printf("Sorry user! We couldn't find the given string!\n");
                if(root==NULL) root = newnode();
                break;
            case 4:
                return 0;
            default:
                printf("Sorry! I guess you didn't read the operations. Please try again!\n");
                break;
        }
    }
    return 0;
}
