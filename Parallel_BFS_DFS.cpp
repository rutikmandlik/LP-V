#include <iostream>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

class node
{
public:
    node *left, *right;
    int data;
};

class TreeTraversal
{
public:
    node *insert(node *, int);
    void parallel_bfs(node *);
    void parallel_dfs(node *);
};

node *TreeTraversal::insert(node *root, int data)
{
    if (root == NULL)
    {
        root = new node;
        root->left = root->right = NULL;
        root->data = data;
    }
    else if (data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }
    return root;
}

void TreeTraversal::parallel_bfs(node *root)
{
    if (root == NULL)
        return;

    queue<node *> q;
    q.push(root);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        cout << "\nBFS running on thread: " << thread_id << endl;
        while (!q.empty())
        {
            node *node = NULL;

            #pragma omp critical
            {
                int thread_id = omp_get_thread_num();
                cout << "\nBFS running on thread: " << thread_id << endl;
                if (!q.empty())
                {
                    node = q.front();
                    q.pop();
                }
            }

            if (node != NULL)
            {
                cout << node->data << " ";

                if (node->left != NULL)
                    q.push(node->left);
                if (node->right != NULL)
                    q.push(node->right);
            }
        }
    }
}

void TreeTraversal::parallel_dfs(node *root)
{
    if (root == NULL)
        return;

    stack<node *> s;
    s.push(root);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        cout << "\nDFS running on thread: " << thread_id << endl;
        while (!s.empty())
        {
            node *node = NULL;

            #pragma omp critical
            {
                int thread_id = omp_get_thread_num();
                cout << "\nDFS running on thread: " << thread_id << endl;
                if (!s.empty())
                {
                    node = s.top();
                    s.pop();
                }
            }

            if (node != NULL)
            {
                cout << node->data << " ";

                if (node->right != NULL)
                    s.push(node->right);
                if (node->left != NULL)
                    s.push(node->left);
            }
        }
    }
}

int main()
{
    TreeTraversal tt;
    node *root = NULL;
    int data;
    char ans;

    do
    {
        cout << "\n enter data=>";
        cin >> data;

        root = tt.insert(root, data);

        cout << "do you want insert one more node?";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

	cout << "\nBFS Traversal: ";
    tt.parallel_bfs(root);//for bfs traversal

	cout << "\nDFS Traversal: ";
	tt.parallel_dfs(root);//for dfs traversal

    return 0;
}
/*
commanfd to compile and run the code:
g++ -fopenmp Parallel_BFS_DFS.cpp -o Parallel_BFS_DFS
./Parallel_BFS_DFS
*/