#include<iostream>

using namespace std;

struct node
{
       int key;
       node *parent;
       char color;
       node *left;
       node *right;
};
class RBtree
{
      node *root;
      node *q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      ~RBtree()
      {
        DestroyTree(root);
      }
      void insert();
      void insertfix(node *);
      void leftrotate(node *);
      void rightrotate(node *);
      void del();
      node* successor(node *);
      void delfix(node *);
      void disp();
      void display( node *);
      void search();
      void DestroyTree(node *);
};
void RBtree::DestroyTree(node *some_node){
if(some_node->right != NULL)
DestroyTree(some_node->right);
if(some_node->left != NULL)
DestroyTree(some_node->left);
delete some_node;
}
void RBtree::insert() //âñòàâêà, âñå âðåìÿ êðàñíàÿ
{
     int z,i=0;
     cout<<"\nÂâåäèòå çíà÷åíèå äëÿ ââåäåíèÿ â äåðåâî: ";
     cin>>z;
     node *p,*q;
     node *t=new node;
     t->key=z;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->key<t->key)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->key<t->key)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
}
void RBtree::insertfix(node *t) //ïðîâåðêà ïðàâèë êð÷
{
     node *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           node *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}

void RBtree::del() //ôóíêöèÿ óäàëåíèÿ,êîãäà äâà ïîòîìêà â çíà÷åíèå óçëà ïèøåòñÿ ñàìàÿ ìàëåíüêîå çíà÷åíèå èç áîëüøèõ or ñàìîå áîëüøîå èç ìåíüøèõ
{
     if(root==NULL)
     {
           cout<<"\nÏóñòîå äåðåâî." ;
           return ;
     }
     int x;
     cout<<"\nÂâåñòè çíà÷íåèå äëÿ óäàëåíèÿ: ";
     cin>>x;
     node *p;
     p=root;
     node *y=NULL;
     node *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->key==x)
               found=1;
           if(found==0)
           {
                 if(p->key<x)
                    p=p->right;
                 else
                    p=p->left;
           }
     }
     if(found==0)
     {
            cout<<"\nÝëåìåíò íå íàéäåí.";
            return ;
     }
     else
     {
         cout<<"\nÓäàëåííûé ýëåìåíò: "<<p->key;
         cout<<"\nÖâåò: ";
         if(p->color=='b')
     cout<<"×åðíîå\n";
    else
     cout<<"Êðàñíîå\n";

         if(p->parent!=NULL)
               cout<<"\nÐîäèòåëü: "<<p->parent->key;
         else
               cout<<"\nÓ óçëà íåò ðîäèòåëÿ.  ";
         if(p->right!=NULL)
               cout<<"\nÏðàâûé ïîòîìîê: "<<p->right->key;
         else
               cout<<"\nÓ óçëà íåò ïðàâûõ äåòåé.  ";
         if(p->left!=NULL)
               cout<<"\nËåâûé ïîòîìîê: "<<p->left->key;
         else
               cout<<"\nÓ óçëà íåò ïðàâûõ ïîòîìêîâ.  ";
         cout<<"\nÓçåë óäàëåí.";
         if(p->left==NULL||p->right==NULL)
              y=p;
         else
              y=successor(p);
         if(y->left!=NULL)
              q=y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->parent=y->parent;
         if(y->parent==NULL)
              root=q;
         else
         {
             if(y==y->parent->left)
                y->parent->left=q;
             else
                y->parent->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->key=y->key;
         }
         if(y->color=='b')
             delfix(q);
     }
}

void RBtree::delfix(node *p) //âîññòàíîâëåíèå öâåòîâ è ïîâîðîòîâ
{
    node *s;
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;
                  if(s->color=='r')
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color=='b';
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

void RBtree::leftrotate(node *p) //ëåâûé ïîâîðîò
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBtree::rightrotate(node *p) //ïðàâûé ïîâîðîò
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

node* RBtree::successor(node *p) //ôóíêöèÿ íàõîæäåíèÿ èùåò çàìåíó óäàëåííîìó ýëåìåíòó âñ 2 ïîòîìêàìè
{
      node *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

void RBtree::disp()
{
     display(root);
}
void RBtree::display(node *p) //âûâîä ëèáî êîíêðåòíîãî óçëà, ëèáî ïðè root âñåãî äåðåâà
{
     if(root==NULL)
     {
          cout<<"\nÏóñòîå äåðåâî.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t óçåë: ";
                cout<<"\n Çíà÷åíèå: "<<p->key;
                cout<<"\n Öâåò: ";
    if(p->color=='b')
     cout<<"×åðíîå";
    else
     cout<<"Êðàñíîå";
                if(p->parent!=NULL)
                       cout<<"\n Ðîäèòåëü: "<<p->parent->key;
                else
                       cout<<"\n Ó óçëà íåò ðîäèòåëÿ.  ";
                if(p->right!=NULL)
                       cout<<"\n Ïðàâûé ïîòîìîê: "<<p->right->key;
                else
                       cout<<"\n Ó óçëà íåò ïðàâûõ ïîòîìêîâ.  ";
                if(p->left!=NULL)
                       cout<<"\n Ëåâûé ïîòîìîê: "<<p->left->key;
                else
                       cout<<"\n Ó óçëà íåò ëåâûõ ïîòîìêîâ.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nËåâî:\n";
     display(p->left);
    }

    if(p->right)
    {
     cout<<"\n\nÏðàâî:\n";
                 display(p->right);
    }
     }
}
void RBtree::search()//ââîäèøü çíà÷åíèå, åãî ïîèñê
{
     if(root==NULL)
     {
           cout<<"\nÏóñòîå äåðåâî\n" ;
           return  ;
     }
     int x;
     cout<<"\nÂâåäèòå çíà÷åíèå äëÿ ïîèñêà: ";
     cin>>x;
     node *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->key==x)
                found=1;
            if(found==0)
            {
                 if(p->key<x)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\nÝëåìåíò íå íàéäåí.";
     else
     {
                cout<<"\n\t Íàéäåí óçåë: ";
                cout<<"\n Çíà÷åíèå óçëà: "<<p->key;
                cout<<"\n Öâåò: ";
    if(p->color=='b')
     cout<<"×åðíûé";
    else
     cout<<"Êðàñíûé";
                if(p->parent!=NULL)
                       cout<<"\n Ðîäèòåëü: "<<p->parent->key;
                else
                       cout<<"\n Ó óçëà íåò ðîäèòåëÿ.  ";
                if(p->right!=NULL)
                       cout<<"\n Ïðàâûé ðåáåíîê: "<<p->right->key;
                else
                       cout<<"\n Ó ðîäèòåëÿ íåò ïðàâûõ äåòåé.  ";
                if(p->left!=NULL)
                       cout<<"\n Ëåâûé ðåáåíîê: "<<p->left->key;
                else
                       cout<<"\n Ó óçëà íåò ëåâûõ äåòåé.  ";
                cout<<endl;

     }
}
int main()
{setlocale(LC_ALL,"Russian");
    int ch,y=0;
    RBtree obj;
    do
    {
                cout<<"\n\t Ê×Ä " ;
                cout<<"\n 1. Âñòàâèòü â äåðåâî ";
                cout<<"\n 2. Óäàëèòü óçåë";
                cout<<"\n 3. Ïîèñê ýëåìåíòà";
                cout<<"\n 4. Ïîêàçàòü äåðåâî ";
                cout<<"\n 5. Âûõîä " ;
                cout<<"\n ×òî áóäåì äåëàòü? -> ";
                cin>>ch;
                switch(ch)
                {
                          case 1 : obj.insert();
                                   cout<<"\nÓçåë âñòàâëåí\n";
                                   break;
                          case 2 : obj.del();
                                   break;
                          case 3 : obj.search();
                                   break;
                          case 4 : obj.disp();
                                   break;
                          case 5 : y=1;
                                   break;
                          default : cout<<"\nÂâåäèòå êîððåêòíóþ îïåðàöèþ.";
                }
                cout<<endl;

    }while(y!=1);
    return 1;
}
