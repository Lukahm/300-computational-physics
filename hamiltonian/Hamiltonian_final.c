
int evaluatehamiltonian();



int evaluatehamiltonian(int x) 
{
	int energy;
	energy=0;
	
	int i;

				// H= H+ Contributions due to the nearest neighbours
		
				i=x; 				
                             energy+=  Spins[x]*Spins[i];         
				i=(x+1)%L; 
			      energy+=  Spins[x]*Spins[i];   
				i=x;    
      				energy+=  Spins[x]*Spins[i];
				  i=(x+L-1)%L;  
				
				energy+=  Spins[x]*Spins[i];
				          

			
			
	return (-1)*energy;
	
	
	
	
}
