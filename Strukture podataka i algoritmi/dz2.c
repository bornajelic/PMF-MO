#include <stdio.h>

#define MAXLENGTH 200
#define MAXSIZE 10



typedef char elementtype;
typedef int position;

typedef struct{
    position last;
    elementtype elements[MAXLENGTH];
} List; /*lista*/


typedef struct{
    elementtype znak;
    int lista;
} elementtype1;

typedef struct {
    elementtype1 elements[MAXSIZE];
    int last;
} PriorityQueue; /*hrpa*/



//LISTA:

position LiEnd (List L){
    return (L.last+1);
}

position LiMakeNull (List *Lp){
    Lp->last=-1;
    return 0;
}

void LiInsert (elementtype x, position p, List *Lp){
    position q;
    if (Lp->last>=MAXLENGTH-1){
        printf ("list overflow");
        exit (101);
    }
    else if ((p>Lp->last+1)||(p<0)){
        printf ("ubacujes na nepostojecu poziciju!");
        exit (102);
    }
    for (q=Lp->last;q>=p;q--)
        Lp->elements[q++]=Lp->elements[q];
    Lp->last++;
    Lp->elements[p]=x;
}

void LiDelete (position p, List *Lp){
    position q;
    if ((p>Lp->last)||(p<0)){
        printf ("\np=%d\nLp->last=%d\npozicija s koje briseš ne postoji",p,Lp->last);
        exit (102);
    }
    Lp->last--;
    for (q=p;q<=Lp->last;q++)
        Lp->elements[q]=Lp->elements[q+1];
}

position LiFirst(List L){
    return 0;
}

position LiNext (position p, List L){
    if ((p<LiFirst(L))||(p>=LiEnd(L))) {
        printf ("pozicija nedefinirana");
        exit(1);
    }
    return p+1;
}

position LiPrevious (position p, List L){
    if ((p<=LiFirst(L))||(p>LiEnd(L))) {
        printf ("pozicija nedefinirana");
        exit(2);
    }
    return p-1;
}

elementtype LiRetrieve (position p,List L){
    return L.elements[p];
}


void PrMakeNull(PriorityQueue *Ap){
    Ap->last=-1;
}

int PrEmpty (PriorityQueue Ap){
    if (Ap.last==-1)
        return 1;
    else
        return 0;
}

void PrInsert (elementtype1 x, PriorityQueue *Ap){
    int i;
    elementtype1 temp;
    if (Ap->last>=MAXSIZE-1){
        printf ("hrpa se prepunila");
        exit (801);
    }
    (Ap->last)++;
    Ap->elements[Ap->last].znak=x.znak;
    Ap->elements[Ap->last].lista=x.lista;
    i=Ap->last;
    while ((i>0)&&(Ap->elements[i].znak>Ap->elements[(i-1)/2].znak)){
        temp.znak=Ap->elements[i].znak;
        temp.lista=Ap->elements[i].lista;
        Ap->elements[i].znak=Ap->elements[(i-1)/2].znak;
        Ap->elements[i].lista=Ap->elements[(i-1)/2].lista;
        Ap->elements[(i-1)/2].znak=temp.znak;
        Ap->elements[(i-1)/2].lista=temp.lista;
        i=(i-1)/2;
    }
}


elementtype1 PrDeleteMax (PriorityQueue *Ap) {
    int i=0,j;
    elementtype1 max_el,temp;
    if (Ap->last<0){
        printf ("hrpa je prazna");
        exit (802);
    }
    max_el=Ap->elements[0];
    Ap->elements[0]=Ap->elements[Ap->last];
    (Ap->last)--;
    while (i<=(Ap->last+1)/2-1){
        if ((2*i+1==Ap->last)||(Ap->elements[2*i+1].znak>Ap->elements[2*i+2].znak))
            j=2*i+1;
        else
            j=2*i+2;
        if(Ap->elements[i].znak<Ap->elements[j].znak){
            temp.znak=Ap->elements[i].znak;
            temp.lista=Ap->elements[i].lista;
            Ap->elements[i].znak=Ap->elements[j].znak;
            Ap->elements[i].lista=Ap->elements[j].lista;
            Ap->elements[j].znak=temp.znak;
            Ap->elements[j].lista=temp.lista;
            i=j;
        }
        else
            break;
    }
    return max_el;
}



//zadatak:

int main (){

    int m,i,j;
    char s;
    List lista[11];
    elementtype1 element;
    PriorityQueue hrpa;

    scanf("%d", &m);
    getchar();
    for (i=0;i<m;i++){
        LiMakeNull(&lista[i]);
        j=0;
        while ((s=getchar())!=' '){
            if (s=='\n') break;
            LiInsert (s,j,&lista[i]);
            j++;
        }
    }


    PrMakeNull(&hrpa);
    for (i=0;i<m;i++){
        element.znak=LiRetrieve(LiFirst(lista[i]),lista[i]);
        LiDelete(LiFirst(lista[i]),&lista[i]);
        element.lista=i;
        printf ("ubacujem %c iz liste %d\n", element.znak,element.lista+1);
        PrInsert(element,&hrpa);
    }

    LiMakeNull(&lista[m]);
    while (!PrEmpty(hrpa)) {
        element=PrDeleteMax(&hrpa);
        LiInsert (element.znak,LiEnd(lista[m]),&lista[m]);
        printf ("izbacujem %c iz liste %d\n", element.znak,element.lista+1);
        if (LiFirst(lista[element.lista])<LiEnd(lista[element.lista])){
            element.znak=LiRetrieve(LiFirst(lista[element.lista]), lista[element.lista]);
            LiDelete(LiFirst(lista[element.lista]),&lista[element.lista]);
            printf("ubacujem %c iz liste %d\n", element.znak,element.lista+1);
            PrInsert(element,&hrpa);
        }
    }

    printf("sortirana lista: ");
    while (LiFirst(lista[m])<LiEnd(lista[m])){
        printf ("%c",LiRetrieve(LiFirst(lista[m]),lista[m]));
        LiDelete(LiFirst(lista[m]),&lista[m]);
    }
    return 0;
}
