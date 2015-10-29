
int evaluatehamiltonian();



int evaluatehamiltonian() 
{

int energy;
energy=0;
	
int i,j,x,y;
	
for(x = 0; x < L; x++)
{
	for(y = 0; y < L; y++)
	{
	// H= H+ Contributions due to the nearest neighbours
			
			i=x;          j=(y+1)%L;
                        energy+=  Spins[x][y]*Spins[i][j];
					
                        i=(x+1)%L;    j=y;
			energy+=  Spins[x][y]*Spins[i][j];
					
                        i=x;          j=(y+L-1)%L;
			energy+=  Spins[x][y]*Spins[i][j];
				   
                        i=(x+L-1)%L;  j=y;
		        energy+=  Spins[x][y]*Spins[i][j];
				          

	}
			
}
	
return (-1)*energy;
	
	
}
