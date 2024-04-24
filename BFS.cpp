#include<iostream>
#include<queue>
#include<stdlib.h>
#include<omp.h>
using namespace std;

class node{
    public:
    node * left;
    node * right;
    int data;
};

class Breadth{
    public:
    node * insert(node * , int);
    void bfs(node *);
};

node * Breadth::insert(node * root, int data){
    if(!root){
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data=data;
        return root;
    }
    queue<node *>q;
    q.push(root);

    while(!q.empty()){

        node* temp = q.front();
        q.pop();

        if(temp->left==NULL){
            temp->left = new node;
            temp->left->left=NULL;
            temp->left->right=NULL;
            temp->left->data=data;
            return root;
        }
        else{
            q.push(temp->left);
        }

        if(temp->right==NULL){
            temp->right=new node;
            temp->right->right=NULL;
            temp->right->left=NULL;
            temp->right->data=data;
            return root;
        }
        else{
            q.push(temp->right);
        }

    }
    
    return root; // Add this line to handle the case where neither left nor right child is NULL
}

void Breadth::bfs(node * head){
    queue<node * >q;
    q.push(head);

    int qsize;
    
    while(!q.empty()){

        qsize=q.size();

        for(int i=0;i<qsize;i++){

            node * curr;
            {
                curr = q.front();
                q.pop();
                cout<<curr->data<<" ";
            }

            {
                if(curr->left){
                    q.push(curr->left);
                }
                if(curr->right){
                    q.push(curr->right);
                }
            }

        }
    }
}


int main(){

    node * root=NULL;
    int data;
    char ans;

    Breadth b;

    do{
        cout<<"Enter the data ";
        cin>>data;

        root=b.insert(root,data);

        cout<<"Continue??";
        cin>>ans;
    }while(ans=='Y' || ans=='y');

    b.bfs(root);

    return 0;
}