


//8 processors

L=8;
N=4;
P=L/N;


for(sites=0;sites<p;sites+=2){


//Metropolis update on site



}



int ip;//counter for processors  
int is;//counter for spins



int Allspins[L]; 

if(my_node==0){
Allspins=malloc(sizeof(int)*L);



}



newarray=malloc(sizeof(int)*(portion+z));


if(my_node==0){
for(is=1;is<=portion;is++){
newarray[is]=allspins[is-1];
}

newarray[0]=allspins[L-1];//PBC


newarray[portion]=allspins[portion];

}



if (my_rank==...){

for(){
MPI_Send();
MPI_Recv();

}


}
