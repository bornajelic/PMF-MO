#include <stdio.h>

/*
IMPLEMENTACIJA ATP "BINARNO STABLO"
IZRADIO: TOMISLAV BUKIC, 2013/11
*/
#include <stdlib.h>

#define LAMBDA NULL

typedef char labeltype; /*odreduje sa kojim podacima struktura barata*/

typedef struct celltag { /*struktura binarno stablo, sa podatkom label*/
    labeltype label;
    struct celltag *leftchild, *rightchild;
    } celltype;

typedef celltype *node; /*pokazivac na cvor*/
typedef celltype *BinaryTree; /*pokazivac na binarno stablo*/

void BiMakeNull (BinaryTree *Tp) { /*pretvara *Tp u prazno stablo*/
    *Tp=LAMBDA;
    }

int BiEmpty (BinaryTree T) { /*ako je T prazno vraæa 1, inace 0: */
    if (T) return 0;
    return 1;
    }

void BiCreate (labeltype l, BinaryTree TL, BinaryTree TR, BinaryTree *Tp) { /*stvara stablo *T sa djecom TL i TR te oznakom l: */
    *Tp=(celltype*)malloc(sizeof(celltype));
    if ((*Tp)==LAMBDA) {
        printf ("greska u alokaciji, BiCreate");
        exit(-1);
        }
    (*Tp)->label=l;
    (*Tp)->leftchild=TL;
    (*Tp)->rightchild=TR;
    }

void BiLeftSubtree (BinaryTree T, BinaryTree *Tlp) { /*vraca lijevo podstablo stabla T: */
    if (T->leftchild)
        *Tlp=T->leftchild;
    }

void BiRightSubtree (BinaryTree T, BinaryTree *Trp) { /*vraca desno podstablo stabla T: */
    if (T->rightchild)
        *Trp=T->rightchild;
    }

node BiInsertLeftChild (labeltype l, node i, BinaryTree *Tp) { /*stablu T dodaje lijevo dijete sa ozakom l i oba pokazivaca LAMBDA*/
    node a;
    a=(node)malloc(sizeof(celltype));
    if((a)==LAMBDA){
        printf ("greska u alokaciji, BiInsertLeftChild");
        exit(-1);
        }
    i->leftchild=a;
    a->label=l;
    a->leftchild=LAMBDA;
    a->rightchild=LAMBDA;
    return a;
    }

node BiInsertRightChild (labeltype l, node i, BinaryTree *Tp) { /*stablu T dodaje desno dijete sa ozakom l i oba pokazivaca LAMBDA*/
    node a;
    a=(node)malloc(sizeof(celltype));
    if((a)==LAMBDA){
        printf ("greska u alokaciji, BiInsertRightChild");
        exit(-1);
        }
    i->rightchild=a;
    a->label=l;
    a->leftchild=LAMBDA;
    a->rightchild=LAMBDA;
    return a;
    }

node BiRoot (BinaryTree T) { /*vraca korijen od T*/
    return T;
    }

node BiLeftChild (node i, BinaryTree T) { /*vraca lijevo dijete cvora i*/
    return i->leftchild;
    }

node BiRightChild (node i, BinaryTree T) { /*vraca desno dijete cvora i*/
    return i->rightchild;
    }

node BiParent (node i, BinaryTree T) { /*vraca roditelja cvora i u stablu T*/
    if (i==T) return LAMBDA;
    if ((i==T->rightchild)||(i==T->leftchild)) return T;
    node a;
    if (T->leftchild!=LAMBDA)
        if ((a=BiParent (i, T->leftchild))!=LAMBDA) return a;
    if (T->rightchild!=LAMBDA)
        if ((a=BiParent (i, T->rightchild))!=LAMBDA) return a;
    return LAMBDA;
    }


void BiDelete (node i, BinaryTree *Tp) { /*brise cvor iz stabla*/
    node a=BiParent (i, *Tp);
    if (a->rightchild==i)
        a->rightchild=LAMBDA;
    else
        a->leftchild=LAMBDA;
    free(i);
    }

labeltype BiLabel (node i, BinaryTree T) { /*vraca oznaku  cvora i stabla T) */
    return i->label;
    }

void BiChangeLabel (labeltype l, node i, BinaryTree *Tp) { /* mijenja oznaku l cvora i stabla *Tp  */
    i->label=l;
    }



/*
PreOrder, InOrder i PostOrder obilasci binarnoga stabla:
    -u programu je potrebno definirati sto funkcija_Xorder radi
    pri obilasku binarnoga stabla
*/

void funkcija_Xorder (node N);

void BiPreOrder (BinaryTree T) {
    funkcija_Xorder (T);
    if (BiLeftChild(T,T)!=LAMBDA)
        BiPreOrder (BiLeftChild(T,T));
    if (BiRightChild(T,T)!=LAMBDA)
        BiPreOrder (BiRightChild(T,T));
    return;
    }

void BiInOrder (BinaryTree T) {
    if (BiLeftChild(T,T)!=LAMBDA)
        BiInOrder (BiLeftChild(T,T));
    funkcija_Xorder (T);
    if (BiRightChild(T,T)!=LAMBDA)
        BiInOrder (BiRightChild(T,T));
    return;
    }

void BiPostOrder (BinaryTree T) {
    if (BiLeftChild(T,T)!=LAMBDA)
        BiPostOrder (BiLeftChild(T,T));
    if (BiRightChild(T,T)!=LAMBDA)
        BiPostOrder (BiRightChild(T,T));
    funkcija_Xorder (T);
    return;
    }

/*
Zadatak:
Implementirajte a.t.p. BinaryTree koji pomocu pointera i napisite potprogram koji kreira binarno stablo
iz prefix oblika logickog izraza. Za kontrolu napravite i preorder obilazak dobivenog stabla.

ULAZNI PODACI: string koji sadrzi prefix oblik izraza
IZLAZNI PODACI: binarno stablo koje odgovara unesenom izrazu: ako stablo ima n cvorova onda treba ispisati n
redova, svaki red je oblika cvor, lijevo dijete, desno dijete (ako nekog djeteta nema, ispisite NULL). Na
kraju jos ispisite PREORDER obilazak dobivenog stabla.
Na primjer, za ulazne podatke:
|A&B|^CED
treba ispisati:
| A &
A NULL NULL
& B |
B NULL NULL
| ^ D
C NULL NULL
E NULL NULL
D NULL NULL
|A&B|^CED
*/

/*
RJESENJE:
*/

void funkcija_Xorder (node n) {
    printf ("%c", BiLabel(n,n));
    return;
    }

int operator (labeltype a) { /*vraća 1 ako je a=&,|,^*/
    if ((a=='|')||(a=='^')||(a=='&'))
        return 1;
    return 0;
    }

void Unos (node P, BinaryTree T) {/*stvara stablo*/
    labeltype a=getchar();
    if (operator(a)) { /*stvara cvor ako je unesen neki od operatora*/
        if (BiLeftChild(P,T)==LAMBDA) { /*ako je lijevo podstablo 'slobodno' koristi ga (jer je binarni operator)*/
            BiInsertLeftChild(a, P, &T);
            Unos(BiLeftChild (P,T),T);
            }
        else { /*ako je lijevo podstablo vec iskoristeno ide u desno*/
            BiInsertRightChild(a, P, &T);
            Unos(BiRightChild (P,T),T);
            }
        }
    else { /*ako znak koji je na redu nije operator*/
        if (BiLeftChild(P,T)==LAMBDA) { /*ako je lijevo podstablo slobodno smjesta ga lijevo*/
            BiInsertLeftChild(a, P, &T);
            Unos (P,T); /*iduci ce znak biti dijete istog cvora, ali ce ici desno*/
            }
        else { /*ako je lijevo podstablo zauzeto operator ce biti smjesten desno*/
            BiInsertRightChild(a, P, &T);
            do { /*ide unazad i trazi prvi cvor koji nema desno dijete*/
                P=BiParent(P,T);
                } while ((BiRightChild(P,T)!=LAMBDA)&&(P!=BiRoot(T)));
            if ((BiRoot(T)==P)&&((BiRightChild(P,T))!=LAMBDA)) return;
            Unos (P,T);
            }
        }
    return;
    }

BinaryTree Unesi (BinaryTree T) { /*stvara korijen stabla, ako je stablo samo korijen*/
    labeltype a=getchar();
    node P;
    BiCreate (a, LAMBDA, LAMBDA, &T);
    if (operator(a)) {
        P=BiRoot(T);
        Unos (P,T);
        }
    return T;
    }

void Ispisi (BinaryTree T) {
    printf ("%c ", BiLabel(T,T));
    if (BiLeftChild(T,T)==LAMBDA)
        printf ("NULL ");
    else
        printf ("%c ", BiLabel (BiLeftChild(T,T),T));
    if (BiRightChild(T,T)==LAMBDA)
        printf ("NULL\n");
    else
        printf ("%c\n", BiLabel (BiRightChild(T,T),T));
    if (BiLeftChild(T,T)!=LAMBDA)
        Ispisi(BiLeftChild(T,T));
    if (BiRightChild(T,T)!=LAMBDA)
        Ispisi (BiRightChild(T,T));
    return;
    }

void Ispis (BinaryTree T) {
    if (BiLabel(T,T)=='\n')
        printf ("NULL");
    else
        Ispisi (T);
    }

int main () {
    BinaryTree T;
    T=Unesi (T);
    Ispis (T);
    BiPreOrder(T);
    return 0;
    }
