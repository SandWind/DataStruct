#include<iostream>
#include<stack>
#include<queue>
using namespace std;

template<typename T>
class Node{
public:
    Node(const T& t=T()):data(t),left(NULL),right(NULL)
    {}
    ~Node()
    {}
public:
    T data;
    Node<T>* left;
    Node<T>* right;
};

template<typename T>
class BinaryTree{
public:
    BinaryTree():root(NULL)
    {}
    ~BinaryTree()
    {}
    void PreOrder()
    {
        cout<<"PrevOrder_R:  ";
        _PreOrder(root);
       cout<<endl;
    }
    void InOrder()
    {
        cout<<"InOrder_R:    ";
        _InOrder(root);
       cout<<endl;
    }
    void PostOrder()
    {
        cout<<"PostOrder_R:  ";
        _PostOrder(root);
       cout<<endl;
    }
    void CreateWithPre(const T* PreOrder,const T* InOrder,int length)
    {
       root= _CreateWithPre(PreOrder,InOrder,length);
    }
    void CreateWithPost(const T* PostOrder,const T* InOrder,int length)
    {
        root=_CreateWithPost(PostOrder,InOrder,length);
    }
    void PreOrder_NR()
    {
        cout<<"PrevOrder_NR: ";
        stack<Node<T>*> s;
        if(root!=NULL)
        {
            s.push(root);
        }
        while(!s.empty())
        {
            cout<<s.top()->data<<" ";
            Node<T>* cur=s.top();
            s.pop();
            if(cur->right!=NULL)
                s.push(cur->right);
            if(cur->left!=NULL)
                s.push(cur->left);
        }
        cout<<endl;
    }
    void InOrder_NR()
    {
        cout<<"InOrder_NR:   ";
        stack<Node<T>*> s;
        Node<T>* cur=root;
        while(!s.empty() || cur!=NULL)
        {
            while(cur!=NULL)
            {
                s.push(cur);
                cur=cur->left;
            }
            cur=s.top();
            cout<<cur->data<<" ";
            s.pop();
            cur=cur->right;
        }
        cout<<endl;
    }
    void PostOrder_NR()
    {
        cout<<"PostOrder_NR: ";
        if(root==NULL)
            return;
        stack<Node<T>*> s1;
        stack<Node<T>*> s2;
        Node<T>* cur=root;
        s1.push(cur);
        while(!s1.empty())
        {
            cur=s1.top();
            s1.pop();
            s2.push(cur);
            if(cur->left!=NULL)
                s1.push(cur->left);
            if(cur->right!=NULL)
                s1.push(cur->right);
        }
        while(!s2.empty())
        {
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
        cout<<endl;
    }
    //void PostOrder_NR()
    //{
    //    cout<<"PostOrder_NR: ";
    //    stack<Node<T>*> s;
    //    Node<T>* cur=root;
    //    Node<T>* visited=NULL;
    //    while(!s.empty() || cur!=NULL)
    //    {
    //        while(cur!=NULL)
    //        {
    //            s.push(cur);
    //            cur=cur->left;
    //        }
    //        cur=s.top();
    //        if(cur->right==NULL || cur->right==visited)
    //        {
    //            s.pop();
    //            cout<<cur->data<<" ";
    //            visited=cur;
    //            cur=NULL;
    //        }
    //        else
    //        {
    //            cur=cur->right;
    //        }
    //    }
    //    cout<<endl;
    //}
    void LevelOrder()
    {
        cout<<"LevelOrder_R: ";
        if(root==NULL)
            return;
        queue<Node<T>*> q;
        Node<T>* cur=root;
        q.push(cur);
        while(!q.empty())
        {
            cur=q.front();
            q.pop();
            cout<<cur->data<<" ";
            if(cur->left!=NULL)
                q.push(cur->left);
            if(cur->right!=NULL)
                q.push(cur->right);
        }
        cout<<endl;
    }
    int Depth()
    {
        cout<<"Depth: ";
        return _Depth(root);
    }
    void PrintEdge1()
    {
        if(root==NULL)
            return ;
        vector<vector<Node<T>*> > edge;
        edge.resize(_Depth(root));
        _setEdge(root,0,edge);
        int i;
        for(i=0;i<edge.size();++i)
        {
            cout<<edge[i][0]->data<<" ";
        }
        _printLeafNotInEdge(root,0,edge);
        for(i=edge.size()-1;i>=0;--i)
        {
            if(edge[i][0]!=edge[i][1])
                cout<<edge[i][1]->data<<" ";
        }
        cout<<endl;
    }
    void PrintEdge2()
    {
        _PrintEdge2(root);
    }
    int size()
    {
        return _size(root);
    }
    void PrintTree()
    {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //error
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int widthspace=3;
        int widthword=5;
        if(root==NULL)
            return;
        queue<Node<T>*> q1;
        queue<Node<T>*> q2;
        Node<T>* cur=root;
        q1.push(cur);
        int level=0;
        bool flag=true;//栈中是否还有不为空的节点
        while(flag && (!q1.empty() || !q2.empty()))
        {
            flag==false;
            if(!q1.empty())
            {
                level++;
                printf("%*s",(_Depth(root)-level)*widthspace," ");
                while(!q1.empty())
                {
                    cur=q1.front();
                    q1.pop();
                    //cout<<cur->data<<" ";
                    if(cur!=NULL)
                        printf("%*d",widthword,cur->data);
                    else
                        printf("%*s",widthword," ");
                    printf("%*s",widthspace," ");
                    if(cur!=NULL)
                    {
                        if(cur->left!=NULL)
                        {
                            flag=true;
                            q2.push(cur->left);
                        }
                        if(cur->right!=NULL)
                        {
                            flag=true;
                            q2.push(cur->right);
                        }
                    }
                    else
                    {
                        q2.push(NULL);
                        q2.push(NULL);
                    }
                }
                cout<<endl;
            }
            if(!q2.empty())
            {
                level++;
                printf("%*s",(_Depth(root)-level)*widthspace," ");
                while(!q2.empty())
                {
                    cur=q2.front();
                    q2.pop();
                    //cout<<cur->data<<" ";
                    if(cur!=NULL)
                        printf("%*d",widthword,cur->data);
                    else
                        printf("%*s",widthword," ");
                    printf("%*s",widthspace," ");
                    if(cur!=NULL)
                    {
                        if(cur->left!=NULL)
                        {
                            flag=true;
                            q1.push(cur->left);
                        }
                        if(cur->right!=NULL)
                        {
                            flag=true;
                            q1.push(cur->right);
                        }
                    }
                    else
                    {
                        q1.push(NULL);
                        q1.push(NULL);
                    }
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }
    //Morris先序遍历，时间复杂度为O(n),空间复杂度为O(1)
    void MorrisPre()
    {
        if(root==NULL)
            return;
        Node<T>* cur=root;
        Node<T>* LeftTreeRightNode=NULL;
loop:
        while(cur->left!=NULL)
        {
            cout<<cur->data<<" ";
            LeftTreeRightNode=cur->left;
            while(LeftTreeRightNode->right!=NULL)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            LeftTreeRightNode->right=cur;
            cur=cur->left;
        }
        cout<<cur->data<<" ";
        cur=cur->right;
        while(cur!=NULL)
        {
            LeftTreeRightNode=cur->left;
            if(LeftTreeRightNode==NULL)
                goto loop;
            while(LeftTreeRightNode->right!=NULL && LeftTreeRightNode->right!=cur)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            if(LeftTreeRightNode->right==NULL)
            {
                goto loop;
            }
            else
            {
                LeftTreeRightNode->right=NULL;
                cur=cur->right;
            }
        }
        cout<<endl;
    }
    //Morris中序遍历，时间复杂度为O(n),空间复杂度为O(1)
    void MorrisIn()
    {
        if(root==NULL)
            return;
        Node<T>* cur=root;
        Node<T>* LeftTreeRightNode=NULL;
loop:
        while(cur->left!=NULL)
        {
            LeftTreeRightNode=cur->left;
            while(LeftTreeRightNode->right!=NULL)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            LeftTreeRightNode->right=cur;
            cur=cur->left;
        }
        cout<<cur->data<<" ";
        cur=cur->right;
        while(cur!=NULL)
        {
            LeftTreeRightNode=cur->left;
            if(LeftTreeRightNode==NULL)
                goto loop;
            while(LeftTreeRightNode->right!=NULL && LeftTreeRightNode->right!=cur)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            if(LeftTreeRightNode->right==NULL)
            {
                goto loop;
            }
            else
            {
                LeftTreeRightNode->right=NULL;
                cout<<cur->data<<" ";
                cur=cur->right;
            }
        }
        cout<<endl;
    }
    //Morris后序遍历，时间复杂度为O(n),空间复杂度为O(1)
    void MorrisPost()
    {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //error
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(root==NULL)
            return;
        Node<T>* cur=root;
        Node<T>* LeftTreeRightNode=NULL;
loop:
        while(cur->left!=NULL)
        {
            LeftTreeRightNode=cur->left;
            while(LeftTreeRightNode->right!=NULL)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            LeftTreeRightNode->right=cur;
            cur=cur->left;
        }
        cur=cur->right;
        while(cur!=NULL)
        {
            LeftTreeRightNode=cur->left;
            if(LeftTreeRightNode==NULL)
                goto loop;
            while(LeftTreeRightNode->right!=NULL && LeftTreeRightNode->right!=cur)
            {
                LeftTreeRightNode=LeftTreeRightNode->right;
            }
            if(LeftTreeRightNode->right==NULL)
                goto loop;
            else
            {
                //cout<<cur->left->data<<" ";
                Node<T>* head=_ReverseRightEdge(cur->left);
                _PrintList(head);
                cur->left=_ReverseRightEdge(head);
                LeftTreeRightNode->right=NULL;
                cur=cur->right;
            }
        }
        //逆置树的右边界
        Node<T>* head=_ReverseRightEdge(this->root);
        cur=head;
        while(cur!=NULL)
        {
            cout<<cur->data<<" ";
            cur=cur->right;
        }
        //再逆置一次
        _ReverseRightEdge(head);
        cout<<endl;
    }
    int LengthBetweenFastestTwoNodes()
    {
        queue<Node<T>*> q1;
        queue<Node<T>*> q2;
    }
private:
    void _PrintList(Node<T>* _root)
    {
        if(_root==NULL)
            return;
        while(_root!=NULL)
        {
            cout<<_root->data<<" ";
            _root=_root->right;
        }
    }
    Node<T>* _ReverseRightEdge(Node<T>* _root)
    {
        if(_root==NULL)
            return NULL;
        Node<T>* tmp=NULL;
        Node<T>* head=_root;
        Node<T>* cur=NULL;
        cur=head->right;
        head->right=NULL;
        while(cur!=NULL)
        {
            tmp=cur->right;
            cur->right=head;
            head=cur;
            cur=tmp;
        }
        return head;
    }
    int _size(Node<T>* root)
    {
        if(root==NULL)
            return 0;
        return _size(root->left) + _size(root->right) +1;
    }
    void _PrintEdge2(Node<T>* root)
    {
        if(root==NULL)
            return;
        cout<<root->data<<" ";
        if(root->left!=NULL && root->right!=NULL)
        {
            _printLeftEdge(root->left,true);
            _printRightEdge(root->right,true);
        }
        else
        {
            _PrintEdge2(root->left!=NULL?root->left:root->right);
        }
        cout<<endl;
    }
    void _printLeftEdge(Node<T>* root,bool print)
    {
        if(root==NULL)
            return;
        if(print || (root->left==NULL && root->right==NULL))
            cout<<root->data<<" ";
        _printLeftEdge(root->left,true);
        _printLeftEdge(root->right,print && root->left==NULL?true:false);
    }
    void _printRightEdge(Node<T>* root,bool print)
    {
        if(root==NULL)
            return;
        _printRightEdge(root->left,print && root->right==NULL?true:false);
        _printRightEdge(root->right,true);
        if(print || (root->left==NULL && root->right==NULL))
            cout<<root->data<<" ";
    }
    void _printLeafNotInEdge(Node<T>* root,int pos,vector<vector<Node<T>*> > edge)
    {
        if(root==NULL)
            return;
        if(root->left==NULL && root->right==NULL && root!=edge[pos][0] && root!=edge[pos][1])
            cout<<root->data<<" ";
        _printLeafNotInEdge(root->left,pos+1,edge);
        _printLeafNotInEdge(root->right,pos+1,edge);
    }
    void _setEdge(Node<T>* root,int pos,vector<vector<Node<T>*> >& edge)
    {
        if(root==NULL)
            return;
        edge[pos].resize(2);
        edge[pos][0]=edge[pos][0]==NULL?root:edge[pos][0];
        edge[pos][1]=root;
        _setEdge(root->left,pos+1,edge);
        _setEdge(root->right,pos+1,edge);
    }
    int _Depth(const Node<T>* root)
    {
        if(root==NULL)
            return 0;
        int left=_Depth(root->left);
        int right=_Depth(root->right);
        return left>right?left+1:right+1;
    }
    Node<T>* _CreateWithPost(const T* PostOrder,const T* InOrder,int length)
    {
        if(PostOrder==NULL || InOrder==NULL || length<=0)
            return NULL;
        int i=length-1;
        while(i>=0 && InOrder[i]!=PostOrder[length-1])
        {
            i--;
        }
        Node<T>* root=new Node<T>(PostOrder[length-1]);
        root->left=_CreateWithPost(PostOrder,InOrder,i);
        root->right=_CreateWithPost(PostOrder+i,InOrder+i+1,length-i-1);
        return root;
    }
    Node<T>* _CreateWithPre(const T* PreOrder,const T* InOrder,int length)
    {
        if(PreOrder==NULL || InOrder==NULL || length<=0)
            return NULL;
        int i=0;
        while(i<length && InOrder[i]!=PreOrder[0])
        {
            i++;
        }
        Node<T>* root=new Node<T>(PreOrder[0]);
        root->left=_CreateWithPre(PreOrder+1,InOrder,i);
        root->right=_CreateWithPre(PreOrder+i+1,InOrder+i+1,length-i-1);
        return root;
    }
    void _PostOrder(Node<T>* root)
    {
        if(root==NULL)
        {
            return ;
        }
        _PostOrder(root->left);
        _PostOrder(root->right);
        cout<<root->data<<" ";
    }
    void _InOrder(Node<T>* root)
    {
        if(root==NULL)
        {
            return ;
        }
        _InOrder(root->left);
        cout<<root->data<<" ";
        _InOrder(root->right);
    }
    void _PreOrder(Node<T>* root)
    {
        if(root==NULL)
        {
            return ;
        }
        cout<<root->data<<" ";
        _PreOrder(root->left);
        _PreOrder(root->right);
    }
public:
    Node<T>* root;
};
