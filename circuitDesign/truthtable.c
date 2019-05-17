#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct var{
	char name[100]; 
	int value;
	int index;
}var;
typedef struct cur{  
}cur;

typedef struct opp { 
	char *name;
	int numin; 
	int *selectors;
	struct opp *next;
	int *input ; 
	int *output; 
}opp; 

 

struct opp *root = NULL;
struct opp *ptr = NULL;



int indexoftemp;
int size;
int i =0;
int out=0;
int numberofinput =0;
int indexofout = 0;
char **arr;
char **arr1;
struct var *input;
struct var *output; 


int pr( int a , int b ){

int x=0;
int temp=a;
if ( b ==0) {
	
return 1;	
}
while (x<b-1){	
	
	temp = temp *a;
	x++;
}
return temp; 
}


void loadinputoutputs( FILE *f) {
	char temp[100] = "";
	fscanf( f ,"%s", temp);
 //printf("%s", temp);
	int j =0;
	fscanf( f ,"%*[: ]%16d", &j);
	
	i =j;
	arr = (char**) malloc ( j * sizeof(char*) ) ;    
	int k ;
	for ( k=0 ; k<j ; k++) {
		arr[k] = (char*) malloc(sizeof(char) * 10);
	 
	}
	k=0;
	while (fscanf( f ,"%*[: ]%16s", temp) == 1){
	    //printf( "%s\n" , temp);
		strcpy( arr[k],temp);
	    //printf( "%i\n" , k);
	    //printf( "%s\n" , arr[k]);
	    k++;
	}
	fgetc(f);
	fscanf( f ,"%s", temp);
     int m =0;
	fscanf( f ,"%*[: ]%16d", &m);

	out = m;
	arr1 = (char**) malloc ( out * sizeof(char*) ) ;
	for ( k=0 ; k<out ; k++) {
		arr1[k] = (char*) malloc(sizeof(char) * 10);
	 
	}
	
	k=0;
	while (fscanf( f ,"%*[: ]%16s", temp) == 1){
	    //printf( "%s\n" , temp);
	    strcpy( arr1[k],temp);
	    //printf( "%i\n" , k);
	    //printf( "%s\n" , arr[k]);
	    k++;
 }
 
 input = (struct var *) malloc( sizeof ( struct var) * (i+size+out));
 size = size+i+out;
 int x=0;
 int y=0;
 indexofout = i;
	while ( x < (i)){
	  strcpy(input[x].name, arr[x]);
	   input[x].value = 0;
	   input[x].index = x;
	 x++;
	}
	
	y = i;
	while ( y < (i+out)) {
		strcpy(input[y].name, arr1[y-i]);
		input[y].value = 0;
		input[y].index = y;
	 y++;	
	}
	numberofinput = i;
	indexoftemp = y;
	i = i+out;
	return;
	
} 

int search( char *temp, int x) {
	
  int a =0;
  int b =0;
  
  if( x ==0 ) {
	  if ( temp[0] == '0' || temp[0] == '1'){
		   strcpy(input[indexoftemp].name, temp);
			   
		   input[indexoftemp].value = temp[0] -48;
		   input[indexoftemp].index = indexoftemp;
		   i++;		  
		   indexoftemp++;
		   return indexoftemp-1;
		   
		  }
	  for ( a = 0 ; a <i ; a++) {
	   
	    if ( strcmp(input[a].name,temp) == 0){
		    	
			 return a;
			}  
		}
		 
		     strcpy(input[indexoftemp].name, temp);
		     input[indexoftemp].value = 0;
		     input[indexoftemp].index = indexoftemp;
            i++;		  
		   indexoftemp++;
		   return  (indexoftemp-1);
	}else{
		 if ( temp[0] == '0' || temp[0] == '1'){
		   strcpy(input[indexoftemp].name, temp);
			   
		   input[indexoftemp].value = temp[0] -48;
		   input[indexoftemp].index = indexoftemp;
		   i++;		  
		   indexoftemp++;
		   return indexoftemp-1;
		   
		  }
		for( b =0 ; b<out ;b++) {
		
			
			if ( strcmp(input[indexofout+b].name,temp) == 0){
		    	
			 return  b+ indexofout;
			}
		}
		
				
		     strcpy(input[indexoftemp].name , temp);
		     input[indexoftemp].value = 0;
		   input[indexoftemp].index = indexoftemp;
		    i++;
		   indexoftemp++;
		   return indexoftemp-1;
		}
		
		
		
		
	} 
	  
	 
	 
 





void loadopp( FILE *f) {
	
	char temp[100] = "";
	
		
	
   while ( fgetc(f) != EOF ) {
	
	fscanf( f ,"%s", temp);
	if( strcmp(temp , "MULTIPLEXER") == 0) {
		fscanf( f ,"%*[: ]%16s", temp);
		int x = temp[0]-48;
		 int *temp0  = (int * ) malloc ( sizeof(int )*x);
			int *temp2 = (int * ) malloc ( sizeof(int )* pr(2,x)) ;
			int *temp1 = (int * ) malloc ( sizeof(int ));
				int m =0;
				int c = pr(2,x);
				size = size+c;
				input = (struct var *) realloc( input, sizeof ( struct var) * (size));
				while( m<c) {
					fscanf( f ,"%*[: ]%16s", temp);
					temp2[m] = search(temp, 0);
				  m++;
				}
				m =0;
				while ( m<x) {
					fscanf( f ,"%*[: ]%16s", temp);
					
					temp0[m] = search(temp, 0);
				  m++;
				}
				fscanf( f ,"%*[: ]%16s", temp);
				temp1[0] = search(temp, 1);
				
					if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "MULTIPLEXER";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->selectors= temp2;
						tempopp->next = NULL;
						tempopp->numin = x;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "MULTIPLEXER";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->selectors= temp2;
					tempopp->next = NULL; 
					tempopp->numin = x;
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;			
	}else if( strcmp(temp , "AND") == 0) {
				
			int * temp0  = (int * ) malloc ( sizeof(int )*2);
				int *temp1  = (int * ) malloc ( sizeof(int ));
				
				int s=0;
				while (s<2){
					 fscanf( f ,"%*[: ]%16s", temp);
				
					temp0[s] = search(temp, 0);
					
					s++;
			   }
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0]= search(temp , 1);
			   
				if( root == NULL) {
					     struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "AND";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp)); 
					tempopp->name= "AND";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
			}else if ( strcmp(temp , "OR") == 0) {
				int * temp0  = (int * ) malloc ( sizeof(int )*2);
				int *temp1  = (int * ) malloc ( sizeof(int ));
				 
				int s=0;
				while (s<2){
					 fscanf( f ,"%*[: ]%16s", temp);
					temp0[s] = search(temp, 0);
					s++;
			   }			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "OR";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "OR";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
				
				
			}else if ( strcmp(temp , "NOT") == 0) {
				
				int *temp0 =(int * ) malloc ( sizeof(int ));
				int *temp1  = (int * ) malloc ( sizeof(int ));
					fscanf( f ,"%*[: ]%16s", temp);
					
					temp0[0] = search(temp, 0);
				  			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "NOT";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "NOT";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
			}
				
			else if ( strcmp(temp , "NAND") == 0) {
			  int * temp0  = (int * ) malloc ( sizeof(int )*2);
				int *temp1  = (int * ) malloc ( sizeof(int ));
				 
				int s=0;
				while (s<2){
					 fscanf( f ,"%*[: ]%16s", temp);
					temp0[s] = search(temp, 0);
					s++;
			   }			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "NAND";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "NAND";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
				
				
			}else if ( strcmp(temp , "NOR") == 0) {
				int * temp0  = (int * ) malloc ( sizeof(int )*2);
				int *temp1  = (int * ) malloc ( sizeof(int ));
				 
				int s=0;
				while (s<2){
					 fscanf( f ,"%*[: ]%16s", temp);
					temp0[s] = search(temp, 0);
					s++;
			   }			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "NOR";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "NOR";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
				
				
			}else if ( strcmp(temp , "XOR") == 0) {
				int * temp0  = (int * ) malloc ( sizeof(int )*2);
				int *temp1  = (int * ) malloc ( sizeof(int ));
				 
				int s=0;
				while (s<2){
					 fscanf( f ,"%*[: ]%16s", temp);
					temp0[s] = search(temp, 0);
					s++;
			   }			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "XOR";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "XOR";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
				
				
			}else if ( strcmp(temp , "DECODER") == 0) {
				
				fscanf( f ,"%*[: ]%16s", temp);
				int x = temp[0]-48;
				int c = x;
				int *temp0 = (int*) malloc( sizeof( int ) *c);
				int *temp1 = (int * ) malloc (sizeof( int) *pr(2,c));
				 
				int m=0;
				while (m<c){
					 fscanf( f ,"%*[: ]%16s", temp);
					temp0[m] = search(temp, 0);
					m++;
			   }			   
			    m=0;
			   int b = pr ( 2,c);
			   size = size+b;
			   input = (struct var *) realloc( input, sizeof ( struct var) * (size)); 
			   
			   while( m< b){ 
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[m] = search(temp , 1);
			   m++;
			}
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "DECODER";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						tempopp->numin = c;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "DECODER";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					tempopp->numin = c;
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
				
				
				
				
			}else if ( strcmp(temp , "PASS") == 0) {
				int *temp0 =(int * ) malloc ( sizeof(int ));
				int *temp1  = (int * ) malloc ( sizeof(int ));
					 fscanf( f ,"%*[: ]%16s", temp);
					
					temp0[0] = search(temp, 0);
				  			   
			   fscanf( f ,"%*[: ]%16s", temp);
			   temp1[0] = search(temp , 1);
				
				if( root == NULL) {
					    struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
						tempopp->name=  "PASS";
						tempopp->input= temp0;
						tempopp->output= temp1;
						tempopp->next = NULL;
						root = tempopp; 
						ptr= root; 
				}else{ 
					struct opp *tempopp = (struct opp * ) malloc ( sizeof(opp));
					tempopp->name= "PASS";
					tempopp->input= temp0;
					tempopp->output= temp1;
					tempopp->next = NULL; 
					ptr->next= tempopp;
					ptr=ptr->next; 
				}
				continue;
				
			}
	}	

}


void opperation( struct opp *root) {
	
if (root ==NULL) {
 return ;	
}	
struct opp * ptr = root; 
  while ( ptr != NULL){
   if (  ( strcmp(ptr->name , "AND") )== 0){
	   
	 if ( input[ptr->input[0]].value == 1 && input[ptr->input[1]].value == 1) {
		 
		 input[ ptr->output[0]].value =1;
		} else{
			
			input[ ptr->output[0]].value =0;
		}  
	  
	} else if (  ( strcmp(ptr->name , "OR")) == 0){
		if ( input[ptr->input[0]].value == 1 || input[ptr->input[1]].value == 1) {
		  input[ ptr->output[0]].value =1;
		}else { 
			
			input[ ptr->output[0]].value =0;
			
		}
	}else if ( ( strcmp(ptr->name , "NAND")) ==0) {
		
		if ( input[ptr->input[0]].value == 1 && input[ptr->input[1]].value == 1) {
		  input[ ptr->output[0]].value =0;
		}else { 
			
			input[ ptr->output[0]].value =1;
			
		}
		
		
	} else if ( strcmp(ptr->name , "NOR") ==0){
		
		if ( input[ptr->input[0]].value == 0 && input[ptr->input[1]].value == 0) {
		  input[ ptr->output[0]].value =1;
		}else { 
			
			input[ ptr->output[0]].value =0;
			
		}
	} else if ( strcmp(ptr->name , "NOT") ==0){
	           
	           if ( input[ptr->input[0]].value ==0) {
				   
				   input[ptr->output[0]].value =1;
				   
			   }else{
				   input[ptr->output[0]].value =0;
				   
				   
				   
			   }
	}else if (  strcmp(ptr->name , "PASS") ==0) {
		
		input[ptr->output[0]].value = input[ptr->input[0]].value;
		
	} else if ( strcmp(ptr->name , "MULTIPLEXER") ==0 ) {
		   int sum =0; 
		   int numinput = ptr->numin;
		   int x = numinput-1; 
		   int y =0; 
		   while( y<numinput) {
			  sum = sum + input[ptr->input[y]].value * pr(2,x); 
			   x--;
			   y++;
			 }
			 input[ ptr->output[0]].value = input[ptr->selectors[sum]].value;
		  }else if ( strcmp(ptr->name , "DECODER") ==0 ){
			  int sum=0;
			  int numinput = ptr->numin;
			  int x = numinput-1; 
			  int y =0; 
			  while( y<numinput) {
			  sum = sum + input[ptr->input[y]].value * pr(2,x); 
			   x--;
			   y++;
			 }
			   y =0; 
			  while ( y< pr(2,numinput) ) {
			  if ( y == sum) {
			  input[ptr->output[sum]].value = 1;
			  y++;
			  continue; 
		      } else {
				  input[ptr->output[y]].value = 0;
                     y++; 			  
			  }
			  
			}
			  
			  
			  
			  
		  }else if ( strcmp(ptr->name , "XOR") ==0 ) {
			   
			   if ( (input[ptr->input[0]].value == 1 &&  input[ptr->input[1]].value==1) || (input[ptr->input[0]].value == 0 && input[ptr->input[1]].value == 0 ) ){
				    input[ ptr->output[0]].value = 0;
				   
				  }else {
					  
					  input[ ptr->output[0]].value = 1;
				  }
			  
			  
			  
			 }
		 		  ptr = ptr->next; 
	  }

	
}



int main(int argc, char **argv) {
	 
 
 FILE *file = fopen( argv[1] , "r"); 
 char line[1000];
 while(fscanf(file,"%[^\n]\n" ,line) !=EOF){
		//printf( "%s\n" ,line);
		size++;
	 
	}
	fclose(file);
	
  file= fopen( argv[1] , "r");
 
 loadinputoutputs( file) ;
 //printf("%i\n", size);
 loadopp(file);
 
/* int l =0;
 
	struct opp *ptr = root;
 while ( l<i) {
	 printf( "%s\n" , input[l].name);
	  input[l].value = 1;
	 
	 l++;
	}
 while( ptr !=NULL) {
	 
	 printf( "%s\n", ptr->name);
	 	 printf( "%s\n", input[ptr->input[0]].name);
	  printf ( " %i\n" , input[ptr->input[0]].value);
	 ptr = ptr->next;
	 
	}*/
		
		
		int u ;
	int r;
	for(u = 0; u< pr(2, numberofinput); u++){
			
			// loads the 2 bit version of counter u into 
			// the liveValue of each var of the input set
			
			for(r = 0; r<numberofinput ; r++){
				
				
				if(u/pr(2,numberofinput-r-1)%2 == 0){
					input[r].value=0;
					printf("0");
				} 
				else {
					input[r].value=1;
					printf("1");
				}
				
				printf(" ");
			}
			
			printf("|");
			opperation(root);
			
			for(r = 0; r<out ; r++){
					
					printf( " %i", input[ indexofout+ r].value ) ;
					
			}
			printf("\n");
			
           
   }
  
 return 0;


}
