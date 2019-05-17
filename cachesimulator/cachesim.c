#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

int valid=0;
int cachehit=0;
int cachemiss=0;
int mread=0;
int mwrite=0;
int prefix=0;
int setbits =0;
int blockbits =0;
uint64_t set_b=0;
int logbase2( int num) {
	
	int x =0;
	if ( num ==1) {
		return 0;
	}
	
	if ( (num %2) == 1) {
		return -1;
		} 
	while ( (num %2) == 0) {
	   num = num/2;
	   x++;
	   }
	
	
	
return x;	
}

typedef struct blocks{
	
    int leastac;
	uint64_t tag;
	int valid ;
}blocks;

typedef struct sets{
	int oldest;
	struct blocks * b;
	int last; 
	
	
}sets;


int tagcmp ( long int tag1 , long int tag2) {
	uint64_t tag3 = tag1 >> (blockbits+setbits);
	uint64_t tag4 = tag2 >> (blockbits+setbits);
	
	if ( tag3 == tag4) {
		return 0;
	}else {
		return 1;
	}
}
void inc( int set , struct sets *sets1, int lines) {

int a = 0;

while ( a < lines) {
	
	if( sets1[set].b[a].tag != -1) {
	sets1[set].b[a].valid++;
	sets1[set].b[a].leastac--;
   }
	a++;
}

}


void prefh(  uint64_t tag, int set , struct sets *sets1 , int lines , char *rp , char c) {
	set = (tag >>  blockbits ) & set_b;
	int x =0; 
	while (x<lines) {
		if (  tagcmp(sets1[set].b[x].tag, tag) == 0) {
			sets1[set].b[x].leastac++;
			return;
		}
		x++;
	}
	 x=0;
	while( x<lines) {
		if (sets1[set].b[x].valid == -1) {
			mread++;
			sets1[set].b[x].tag = tag;
			sets1[set].b[x].valid =-1;
			sets1[set].b[x].leastac =lines;
			inc( set, sets1, lines);
			return;
		}
		x++;
	} 
	int a =0; 
		 int oldest =0;
		 int index=0; 
		 while( a < lines) {
			if ( sets1[set].b[a].valid > oldest) {
				index = a;
				oldest = sets1[set].b[a].valid;
			} 
			a++; 
		}
	if ( strcmp( rp ,"fifo") ==0 )  {
		
		mread++;
		int m = index;
		//printf( "%i\n" , m);
		sets1[set].b[m].tag = tag; 
		sets1[set].b[m].valid =-1;
		inc( set , sets1, lines);
		return; 
	}
	 a =1;
		int lru =sets1[set].b[0].leastac;
		 index =0;
		while( a<lines) {
			if (sets1[set].b[a].leastac == lru) {
				if ( sets1[set].b[a].valid > sets1[set].b[index].valid) {
					index=a;
				}
				
			}
			if (   lru> sets1[set].b[a].leastac) {
				lru = sets1[set].b[a].leastac;
				index = a;
			}
			a++;
		}
		if ( strcmp( rp ,"lru") ==0 )  {
			
			mread++;
		int m = index;
		//printf( "%i\n" , m);
		sets1[set].b[m].tag = tag; 
		sets1[set].b[m].valid =-1;
		sets1[set].b[m].leastac =lines;
		inc( set , sets1, lines);
		return; 
		}
	
	
	printf( "%s" , "problem");
}
int load( int set , uint64_t tag , struct sets *sets1 , char c, int lines , char *rp  , char *pref , int block_size) {
	
	
	int x =0; 
	
	while( x<lines) {
		
		if ( tagcmp(sets1[set].b[x].tag, tag) == 0 && c == 'R') {
			if( prefix ==0){
			cachehit++;
		  }
			sets1[set].b[x].leastac++;
            prefix=0;
            return 0;     		
		}else if ( tagcmp(sets1[set].b[x].tag ,tag) == 0 && c == 'W'){
			
			cachehit++; 
			mwrite++;
			sets1[set].b[x].leastac++;
			return 0;
		}
		x++;
	}
	
	x=0;
	while ( x<lines) {
		
		if( sets1[set].b[x].valid ==-1  && c == 'R'){
			valid++;
			mread++;
			if( prefix==0){
			cachemiss++;
			}
			sets1[set].b[x].tag = tag; 
			sets1[set].b[x].valid =-1;
			sets1[set].b[x].leastac =lines;
			inc( set, sets1, lines);
			if(  strcmp(pref, "p1") ==0){
				
				 uint64_t m = tag + block_size;
				//printf( "%s\n" , "inside");
				prefh( m, set , sets1 , lines , rp , c); 
			}
			prefix=0;
			return 0;
			
		}
		if ( sets1[set].b[x].valid == -1 && c== 'W') {
			valid++;
			cachemiss++;
			mread++;
			sets1[set].b[x].tag = tag;
			sets1[set].b[x].valid =-1;
			sets1[set].b[x].leastac =lines;
			inc( set, sets1, lines);
			mwrite++;
			if( strcmp(pref, "p1") ==0){
				
				 uint64_t m = tag + block_size;
				//printf( "%s\n" , "inside");
				 prefh( m, set , sets1 , lines , rp , c);
			}
			prefix=0;
			return 0;
			
		}
		x++;
		
	}
	if ( strcmp( rp, "fifo") ==0 ) {
		 int a =0; 
		 int oldest =0;
		 int index=0; 
		 while( a < lines) {
			if ( sets1[set].b[a].valid > oldest) {
				index = a;
				oldest = sets1[set].b[a].valid;
			} 
			a++; 
		}
		
		int m = index;
		//printf( "%i\n" , m);
		sets1[set].b[m].tag = tag; 
		sets1[set].b[m].valid =-1;
		inc( set , sets1, lines);
		if ( c == 'R') {
			if( prefix ==0){
			cachemiss++;
		 }
			mread++;
		} if ( c=='W') {
			cachemiss++;
			mwrite++;
			mread++;
			
		}
		if(  strcmp(pref, "p1") ==0){
				//printf( "%s\n" , "inside");
				
				 uint64_t m = tag + block_size;
				prefh( m, set , sets1 , lines , rp, c);
			}
			prefix=0;
		return 0;
	} else if ( strcmp( rp , "lru") == 0){
		int a =1;
		int lru =sets1[set].b[0].leastac;
		int index =0;
		while( a<lines) {
			if ( sets1[set].b[a].leastac == lru) {
				if( sets1[set].b[a].valid > sets1[set].b[index].valid) {
					
					index = a;
				}
				
			}
			if (  lru > sets1[set].b[a].leastac) {
				lru = sets1[set].b[a].leastac;
				index = a;
			}
			a++;
		}
     int m = index;
		//printf( "%i\n" , m);
		sets1[set].b[m].tag = tag; 
		sets1[set].b[m].valid =-1;
		sets1[set].b[m].leastac =lines;
		inc( set , sets1, lines);
		if ( c == 'R') {
			if( prefix ==0){
			cachemiss++;
		 }
			mread++;
		} if ( c=='W') {
			cachemiss++;
			mwrite++;
			mread++;
			
		}
		if(  strcmp(pref, "p1") ==0){
				//printf( "%s\n" , "inside");
				
				 uint64_t m = tag + block_size;
				prefh( m, set , sets1 , lines , rp, c);
			}
			prefix=0;
		return 0;
		
	}
	
	
	
	
	
	
	
	
	
	return -1;
	
}
int main ( int argc , char **argv) {
	
int c_size =0;
int b_size =0;
char *asso;
char *pref;
char *rp;
FILE *f;



int temp1 = atoi(argv[1]); 
int temp2 =0;
c_size = logbase2(temp1); 
asso = argv[2];
pref = argv[3];
rp = argv[4];
temp2 = atoi(argv[5]);
b_size = logbase2(temp2);
f = fopen(argv[6], "r");
if ( b_size == -1 || c_size == -1) {
	
printf ( "%s" , "error" ) ;
return 0;	
}
int set =0;
int lines =0;
if ( strcmp( asso, "assoc") ==0) {
  set=1;	
  lines = temp1/temp2;
}else if ( strcmp( asso, "direct") ==0){
	
  
  set = temp1/temp2;
  lines = 1;
	
 }else {
	 if ( logbase2( asso[6]-48) == -1) {
		 printf ( "%s" , "error" ) ;
			return 0;
		}
	 lines = asso[6]-48;
	 set =  temp1/(lines*temp2);
	 
	 
	 
}





int setbits1 = logbase2(set);

struct sets *set1 = (sets *) malloc ( sizeof (sets) * set);
int x =0;
while( x<set) {
	set1[x].b = (blocks *) malloc ( sizeof ( struct blocks) * lines );
	  int a =0;
	  while( a<lines) {
	  set1[x].b[a].valid =-1;
       set1[x].b[a].tag =-1;
       a++;  
  }
	  x++;
}
setbits = setbits1;
blockbits = b_size;

//int blockbits = b_size;
char *ptr;
char a;
char add[16];
 int setoff;
 //long int tag; 
char notim[100];
//printf( "%i\n" , lines);
//printf( "%i\n" , set);
set_b = set-1;
while( fscanf(f, "%s %c %s\n", notim, &a , add) ==3) { 

uint64_t m =strtoll(add, &ptr, 16);
uint64_t setb = set-1;
setoff =  (m >>  b_size ) & setb;
//tag = m>>  (b_size + setbits1);
//printf ( "%lx\n" , tag);
if( load(setoff , m , set1 , a, lines , rp , pref , temp2) == -1){
printf ("problem ");	
}


}

//printf( "%i\n", blockbits) ;
 //printf( "%i\n", setbits) ;
printf("%s" , "Memory reads: ");
printf("%i\n" , mread);
printf("%s" , "Memory writes: ");
printf("%i\n" , mwrite);
printf("%s" , "Cache hits: ");
printf("%i\n" , cachehit);
printf("%s" , "Cache misses: ");
printf("%i\n" , cachemiss);


	//printf ( "%i\n" , lines);
	//printf ( "%i\n" , setbits);
	
return 0;	
	
}

