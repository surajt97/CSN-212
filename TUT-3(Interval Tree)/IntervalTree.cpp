#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
int max(int a, int b, int c){
    return max(a, max(b, c));
}
struct node{
    int low, high, maxh;
    node *left, *right;
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
            root->left = root->right = NULL;
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
        }
    }
    node* minValueNode(node* root){
        node *p = root;
        while (p->left != NULL)
            p = p->left; 
        return p;
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
    void remove(node* p, node* root, node* parent, bool head){
        int child = 0;
        bool left = false, right = false;
        if(p->low <= parent->low) 
            left = true;
        else 
            right = true;
        if(p->left) 
            child++;
        if(p->right)
            child++;

        if(child==0){
            if(head){
                parent = NULL;
                return;
            }
            if(left)
                parent->left = NULL;
            else 
                parent->right = NULL;
        }
        else if(child==1){
            if(head){
                if(p->left) 
                    root = root->left;
                else 
                    root = root->right;
                return;
            }
            if(left){
                if(p->right) 
                    parent->left = p->right;
                else 
                    parent->left = p->left;
            }
            else{
                if(p->right) 
                    parent->right = p->right;
                else 
                    parent->right = p->left;
            }
        }
        else{
            node* temp = p;
            temp = temp->left;
            if(temp->right){
                while(temp->right){
                    parent = temp;
                    temp = temp->right;
                }
                p->low = temp->low;
                p->high = temp->high;
                parent->right = NULL;
            }
            else{
                p->low = temp->low;
                p->high = temp->high;
                remove(temp, root, p, false);
            }
        }
    }
    node* deletenode(node* root, node* temp){
        node* p = new node();
        p = root;
        node *parent= new node();
        parent = root;
        while(true){
            if(temp->low < p->low){
                parent = p; 
                p = p->left;
            }
            else if(temp->low > p->low){
                parent = p; 
                p = p->right;
            }
            else{
                remove(p, root, parent, false);
                break;
            }
        }
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
    //deletion
    node *d = new node();
    cin>>l>>h;
    d->low = l;
    d->high = h;
    d->left = d->right = NULL;
    d->maxh = h;
    t.deletenode(t.root, d);
    cout<<"Node deleted"<<endl;
    return 0;
}