#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"


typedef struct NodeObj{
   KEY_TYPE k;
   VAL_TYPE v;
   int color;
   struct NodeObj* Parent;
   //struct NodeObj* Parent;
   struct NodeObj* LChild;
   struct NodeObj* RChild;
} NodeObj;
// Node
typedef NodeObj* Node;
// constructor for private Node type
Node newNode(KEY_TYPE k, VAL_TYPE v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->color=NULL;
   N->k = k;
   N->v = v;  
   N->LChild =  NULL;
   N->RChild =  NULL;
   N->Parent =  NULL;
   return(N);
}
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
typedef struct DictionaryObj{
   Node root;
   Node currentN;
   int unique;
   int size;
}DictionaryObj;
Dictionary newDictionary(int unique){
   Dictionary N = malloc(sizeof(DictionaryObj));
   assert(N!=NULL);
   N->currentN=NULL;
   N->root=NULL;
   N->unique=unique;
   N->size=0;
   return N;
}  
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
}
void makeEmpty(Dictionary D){
   (D->size)=0;
   makeE(D->root);
   D->root=NULL;
   D->currentN=NULL;
   return;
}
void makeE(Node N){
    if(N != NULL){
        makeE(N->LChild);
        makeE(N->RChild);
        free(N);
    }
}
int size(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling size() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->size);
}
int getUnique(Dictionary D){
   return(D->unique);
}
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
   if(D->size==0){
      return VAL_UNDEF;
   }
   Node temp = D->root;
   while(temp!=NULL){
      if(KEY_CMP(k,temp->k)==0){
         return temp->v;
      }else if(KEY_CMP(k,temp->k)<0){
         temp=temp->LChild;
      }else{
         temp=temp->RChild;
      }
   }
   return VAL_UNDEF;
}
void LeftRotate(Dictionary D, Node x){
   // set y
   Node y = x->RChild; 
   // turn y's left subtree into x's right subtree
   x->RChild = y->LChild; 
   if(y->LChild !=NULL){
      (y->LChild)->Parent = x;
   }
   // link x's parent to y
   y->Parent = x->Parent; 
   if(x->Parent == NULL)
      D->root = y;
   else if(x == x->Parent->LChild)
      x->Parent->LChild = y;
   else 
      x->Parent->RChild = y;
   // put x on y's left
   y->LChild= x;
   x->Parent = y;
}
void RightRotate(Dictionary D, Node x){
   // set y
   Node y = x->LChild; 
   // turn y's left subtree into x's right subtree
   x->LChild = y->RChild; 
   if(y->RChild !=NULL){
      (y->RChild)->Parent = x;
   }
   // link x's parent to y
   y->Parent = x->Parent; 
   if(x->Parent == NULL)
      D->root = y;
   else if(x == x->Parent->RChild)
      x->Parent->RChild = y;
   else 
      x->Parent->LChild = y;
   // put x on y's left
   y->RChild= x;
   x->Parent = y;
}
void RB_InsertFixUp(Dictionary T,Node z){// black 0 red 1
   Node y=NULL;
   if(z->Parent->Parent==NULL){
      return;      
   }
   while (z->Parent!=NULL && z->Parent->color == 1){// so it has a paren
      //printf("what about here?hmmmmmmm\n");
      if (z->Parent == z->Parent->Parent->LChild){// and a great parent
        // printf("what about here?\n");// seg fualt past this line time to find it lmlao :)
         y = z->Parent->Parent->RChild;// great parent has no right
         //no fualt 
         // y is being put to null so no color
         //hmmmmmmmmmm
         if( y!=NULL && y->color == 1){
            
            z->Parent->color = 0;             // case 1
            y->color = 0;                    // case 1
            z->Parent->Parent->color = 1;         // case 1
            z = z->Parent->Parent;  
           // printf("what about here?\n");               // case 1
         }else{ 
           // printf("what about here3?\n");
            if(z == z->Parent->RChild){
               z = z->Parent;                     // case 2
               LeftRotate(T, z);        
            }         // case 2
            z->Parent->color = 0;             // case 3
            z->Parent->Parent->color = 1;         // case 3
            RightRotate(T, z->Parent->Parent);  
         } //does not reach here
           // case 3
      }else{ 
        // printf("what about here2?\n");
         y = z->Parent->Parent->LChild;
         if( y!=NULL && y->color == 1){
            z->Parent->color = 0;              // case 4
            y->color = 0;                     // case 4
            z->Parent->Parent->color = 1;         // case 4
            z = z->Parent->Parent;                 // case 4
         }else{ 
            if( z == z->Parent->LChild){
               z = z->Parent;                     // case 5
               RightRotate(T, z);
            }                // case 5
            z->Parent->color =0;             // case 6
            z->Parent->Parent->color = 1;         // case 6
            LeftRotate(T, z->Parent->Parent); 
         }
      } 
   }     // case 6
   T->root->color = 0;
}
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
   if(getUnique(D) == 1){
        VAL_TYPE check = lookup(D, k);
        if(check != VAL_UNDEF){
            return;
        }
    }
   Node ins =newNode(k,v);
   if(D->size == 0){
        D->root = ins;
        ins->color=0;
        (D->size)++;
        return;
   }
   Node temp = D->root;
   Node tempP;
   while((temp)!=NULL){// left is insert <0 less >
         tempP=temp;
         if(KEY_CMP(k,temp->k)<0){
            temp=temp->LChild;   
         }else{  
            temp=temp->RChild;
         } 
   }
   ins->Parent = tempP;// wow im finally looking at the psuodo code provided and my god its so overpowered. so many things i was doing just lengthing mu code
   if(KEY_CMP(k, tempP->k) < 0){
        tempP->LChild = ins;
        D->size ++;
        //return;
    }
    else{
        tempP->RChild = ins;
        //ins->Parent = tempP;
        D->size ++;
        //return;
    }
    ins->color=1;
    RB_InsertFixUp(D, ins);
}
void RB_Transplant(Dictionary T, Node u, Node v){// giving a seg fualt when v ==null
   if(u->Parent == NULL){
      
      T->root = v;
   }
   else if( u == u->Parent->LChild){
     
      //printf(KEY_FORMAT"\n", v->k);
      if(v==NULL){
         (u->Parent)->LChild = NULL;
      }else{
         (u->Parent)->LChild = v;
      }
   }
   else{
      if(v==NULL){
         (u->Parent)->RChild = NULL;
      }else{
         (u->Parent)->RChild = v;
      }
   }if(v!=NULL){
      v->Parent = u->Parent;
   }
}
Node miN(Node N) { 
   
    Node c = N; 
    while (c && c->LChild != NULL) 
        c = c->LChild; 
    return c; 
} 
void RB_DeleteFixUp(Dictionary T, Node x){// time to fix this one
  // printf("2\n");
   if(x==NULL){
      
      return;
   }
   while(x != T->root && x->color == 0){
      //printf("1\n");
      if( x == x->Parent->LChild){
         //printf("2\n");
         Node w = x->Parent->RChild;
         if (w->color == 1){
            w->color = 0;                        // case 1
            x->Parent->color = 1;                   // case 1
            LeftRotate(T, x->Parent);                // case 1
            w = x->Parent->RChild;  
         }                   // case 1
         if( (((w->LChild)->color) == 0) && (((w->RChild)->color) == 0)){
            w->color = 1;                         // case 2
            x = x->Parent;                           // case 2
         }else{ 
            if(w->RChild->color == 0){
               w->LChild->color = 0;                // case 3
               w->color = 1;                       // case 3
               RightRotate(T, w);                   // case 3
               w = x->Parent->RChild; 
            }                 // case 3
            w->color = x->Parent->color;               // case 4
            x->Parent->color = 0;                // case 4
            w->RChild->color = 0;                  // case 4
            LeftRotate(T, x->Parent);                // case 4
            x = T->root;  
         }                           // case 4
      }else{
        // printf("3\n");
         Node w = x->Parent->LChild;
         if( w->color == 1){
            w->color = 0;                        // case 5
            x->Parent->color =1;                 // case 5
            RightRotate(T, x->Parent);               // case 5
            w = x->Parent->LChild;                      // case 5
         }
         if (w->RChild->color == 0 && w->LChild->color == 0){
            w->color = 1;                          // case 6
            x = x->Parent;                           // case 6
         }else{ 
            if (w->LChild->color == 0){
               w->RChild->color = 0;               // case 7
               w->color = 1;                      // case 7
               LeftRotate(T, w);                    // case 7
               w = x->Parent->LChild;
            }                   // case 7
            w->color = x->Parent->color;               // case 8
            x->Parent->color =0;                 // case 8
            w->LChild->color = 0;                   // case 8
            RightRotate(T, x->Parent);               // case 8
            x = T->root;  
         }
      }
   } 
  // printf("4\n");                      // case 8
   x->color = 0;
  // printf("5\n");
}
void RB_Delete(Dictionary T, Node z,KEY_TYPE k){// time to fix this so it works for keys  Z is if we passed in a node not a key hmmm
   if(z==NULL){
      return;
   }else if(KEY_CMP(k,z->k)<0){// key is less still go to left
      RB_Delete(T,z->LChild,k);
   }else if(KEY_CMP(k,z->k)>0){// key is to the right
      RB_Delete(T,z->RChild,k);
   }else{
      Node x=NULL;
      Node y = z;
      int y_original_color = y->color;
      if(z->LChild == NULL){
         x = z->RChild;
         free(y);
         (T->size)--;
         RB_Transplant(T, z, z->RChild);
      }else if( z->RChild == NULL){
        x = z->LChild;
         (T->size)--;
         free(y);
         RB_Transplant(T, z, z->LChild);
      }else{
         
         y = miN(z->RChild);
         y_original_color = y->color;
         x = y->RChild;
         if( y->Parent == z){
            x->Parent = y;
         }
         else{ 
            RB_Transplant(T, y, y->RChild);
            y->RChild = z->RChild;
            y->RChild->Parent = y;
         }
         RB_Transplant(T, z, y);
         y->LChild = z->LChild;
         y->LChild->Parent = y;
         y->color = z->color;
         (T->size)--;
      }
      if (y_original_color == 0){
         RB_DeleteFixUp(T, x);
      }
   }
}
void delete(Dictionary D, KEY_TYPE k){
   if(D->size==0){
      return;
   }
   Node T=D->root;
   RB_Delete(D,T,k);
}
VAL_TYPE beginForward(Dictionary D){
   if(D==NULL){
      return VAL_UNDEF;
   } 
   if(D->size==0){
      return VAL_UNDEF;
   }
  VAL_TYPE lmao;
   D->currentN=D->root;
   if((D->currentN)->LChild==NULL){
      lmao=(D->currentN)->v;
      return lmao;
   } 
   while((D->currentN)->LChild!=NULL){
      (D->currentN)=(D->currentN)->LChild;

   } 
   lmao=(D->currentN)->v;
   return lmao;
}
VAL_TYPE beginReverse(Dictionary D){
   if(D==NULL){
      return VAL_UNDEF;
   }
   if(D->size==0){
      return VAL_UNDEF;
   }
  VAL_TYPE lmao;
   D->currentN=D->root;
   if((D->currentN)->RChild==NULL){
      lmao=(D->currentN)->v;
      return lmao;
   } 
   while((D->currentN)->RChild!=NULL){
      (D->currentN)=(D->currentN)->RChild;

   } 
   lmao=(D->currentN)->v;
   return lmao;
}
KEY_TYPE currentKey(Dictionary D){
   if(D->currentN==NULL){
      return KEY_UNDEF;
   }
   return (D->currentN)->k;
}
VAL_TYPE currentVal(Dictionary D){
   if(D->currentN==NULL){
      return VAL_UNDEF;
   }
   return (D->currentN)->v;
}
VAL_TYPE next(Dictionary D){
    if(D->currentN == NULL){
        return VAL_UNDEF;
    }

    Node temp = D->currentN;

    Node test = D->root;
    while(test->RChild != NULL){
        test = test->RChild;
    }

    if(temp == test){
        D->currentN = NULL;
        return VAL_UNDEF;
    }

    if(temp->RChild != NULL){
        temp = temp->RChild;
        while(temp->LChild != NULL){
            temp = temp->LChild;
        }
        D->currentN = temp;
        return temp->v;
    }

    Node tempTemp = temp->Parent;


    while(tempTemp != NULL && temp == tempTemp->RChild){
        temp = tempTemp;
        tempTemp = temp->Parent;
    
    }




    D->currentN = tempTemp;
    return tempTemp->v;
}
VAL_TYPE prev(Dictionary D){
    if(D->currentN == NULL){
        return VAL_UNDEF;
    }

    Node temp = D->currentN;

    Node test = D->root;
    while(test->LChild != NULL){
        test = test->LChild;
    }

    if(temp == test){
        D->currentN = NULL;
        return VAL_UNDEF;
    }

    if(temp->LChild != NULL){
        temp = temp->LChild;
        while(temp->RChild != NULL){
            temp = temp->RChild;
        }
        D->currentN = temp;
        return temp->v;
    }

    Node tempTemp = temp->Parent;


    while(tempTemp != NULL && temp == tempTemp->LChild){
        temp = tempTemp;
        tempTemp = temp->Parent;
    
    }




    D->currentN = tempTemp;
    return tempTemp->v;
}
void PrintPre(FILE* out, Node N){
   if(N==NULL){
      return;
   }
   fprintf(out,""KEY_FORMAT"\n",N->k);
   PrintPre(out,N->LChild);
   PrintPre(out,N->RChild);
}
void PrintPost(FILE* out, Node N){
   if(N==NULL){
      return;
   }
   PrintPost(out,N->LChild);
   PrintPost(out,N->RChild);
   fprintf(out,""KEY_FORMAT"\n",N->k);
}
void PrintIN(FILE* out, Node N){
   if(N==NULL){
      return;
   }
   PrintIN(out,N->LChild);
   fprintf(out,""KEY_FORMAT"\n",N->k);
   PrintIN(out,N->RChild);
   
}
void printDictionary(FILE* out, Dictionary D, const char* ord){// print out keys not values
//pre, post, in
   if(strcmp(ord,"in")==0){
      fprintf(out,"******************************************************\n");
      fprintf(out,"IN-ORDER:\n");
      fprintf(out,"******************************************************\n");
     PrintIN(out,D->root);
   }else if(strcmp(ord,"pre")==0){
      fprintf(out,"******************************************************\n");
      fprintf(out,"PRE-ORDER:\n");
      fprintf(out,"******************************************************\n");
      PrintPre(out,D->root);
   }else if(strcmp(ord,"post")==0){
      fprintf(out,"******************************************************\n");
      fprintf(out,"POST-ORDER:\n");
      fprintf(out,"******************************************************\n");
      PrintPost(out,D->root);
   }

}



