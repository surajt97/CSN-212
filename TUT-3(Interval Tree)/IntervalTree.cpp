#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
int max(int a, int b, int c){
    return max(a, max(b, c));
}
struct node{
    int low, high, maxh;
    node *left, *right, *parent;
};
class IntervalTree{
public:
    node *root;
    int count;
    IntervalTree(){
        root = NULL;
    }
    void insert(int l, int h){
        if(!root){
            root = new node();
            root->low = l;
            root->high = h;
            root->maxh = h;
            root->left = root->right = root->parent = NULL;
        }
        else{
            node *p = root;
            while(p){
                if(p->high<h){ //update of max found in subtree rooted at this node
                    p->high = h;
                }
                if(p->low < l && p->right){ // to be inserted in right subtree
                    p = p->right;
                }
                else if(p->low >= l && p->left){ // to be inserted in left subtree
                    p = p->left;
                }
                else 
                    break;
            }
            node *q = new node();
            q->low = l;
            q->high = h;
            q->maxh = h;
            if(p->high<h)
                p->high = h;
            if(p->low < l){
                p->right = q;
            }
            else{
                p->left = q;
            }
            q->left = q->right = NULL;
            q->parent = p;
        }
    }
    node* minValueNode(node* root){
        node *p = root;
        while (p->left != NULL)
            p = p->left; 
        return p;
    }
    node* deleteNode(node* root, int key){
    if (root == NULL) 
        return root;
    if (key < root->low)
        root->left = deleteNode(root->left, key);
    else if (key > root->low)
        root->right = deleteNode(root->right, key);
    else{
        node *p = root->parent;
        int maxleft = (root->left)->maxh, maxrt = (root->right)->maxh;
        if (root->left == NULL){
            node *temp = root->right;
            p->maxh = max(p->maxh, temp->maxh);
            return temp;
        }
        else if (root->right == NULL){
            node *temp = root->left;
            p->maxh = max(p->maxh, temp->maxh);        
            return temp;
        }
        p->maxh = max(p->maxh, (root->left)->maxh, (root->right)->maxh);
        node* temp = minValueNode(root->right);
        root->low = temp->low;
        root->high = temp->high;
        root->maxh =  max(maxleft, maxrt);
        root->right = deleteNode(root->right, temp->low);
    }
    return root;
}
    node *search(node *root, int l, int h){
        if (root == NULL)
            return NULL;
        if (root->low<=h && root->high>=l)
            return root;
        if (root->left != NULL && (root->left)->maxh >= l)
            return search(root->left, l, h);
        return search(root->right, l, h);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector <pair<int, int> > v;
    int n, l, h;
    cin>>n;
    for(int i = 0; i<n; i++){
        cin>>l>>h;//input of all intervals
        v.push_back(make_pair(l, h));
    }
    IntervalTree t;
    for(int i = 0; i<n; i++){
        t.insert(v[i].first, v[i].second);//building of tree
    }
    cin>>l>>h;    //search query input
    node *ans = t.search(t.root, l, h);
    if(ans){ // ans is not NULL
        cout<<"Overlap interval: "<<ans->low<<" "<<ans->high<<endl;
    }
    else{
        cout<<"No overlap interval found"<<endl;
    }
    return 0;
}