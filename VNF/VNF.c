#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//COMPILE: gcc VNF.c -o VNF.exe ; ./VNF.exe -n d.txt -o NAME.vnf


#define ARRAY_CONCAT(TYPE, A, An, B, Bn) \
  (TYPE *)array_concat((const void *)(A), (An), (const void *)(B), (Bn), sizeof(TYPE));
 
char key[]        = {0,0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};
const int MAX_KEY = 11;
char *fileName = "out.vnf";
char *vnfFileName = "VNF.vnf";

void *array_concat(const void *a, size_t an,
                   const void *b, size_t bn, size_t s)
{
  char *p = malloc(s * (an + bn));
  memcpy(p, a, an*s);
  memcpy(p + an*s, b, bn*s);
  return p;
}


int ToAlloc(FILE *file){

  int ch  = getc(file);
     int itr = 0;

     while (ch != EOF) 
     {  
        ch = getc(file);
        itr++;
     }

     return itr;
}

char *Crypt(char *c,int count){

  
  int itr = 0;
  while( itr < count){
    
    c[itr] = 12 + (c[itr] ^ key[itr%11]);

    itr++;
  }

  
   return c;

}


int main(int argc, char const *argv[])
{

   if(argc == 1){
   	puts("usage: VNF.exe {FileName} Optional-{Key}");
   	return 1;
   }
   int i  = 0;
   int Kcount = 0;
   int nameCount = 0; 


   if(argc > 1){
      while(argv[++nameCount] != NULL){
        if(0 == strcmp(argv[nameCount], "-n")){
          vnfFileName = argv[nameCount +1];

        }
      }


   }

  

   if(argc >= 3){       

     while(argv[++Kcount] != NULL){
        if(0 == strcmp(argv[Kcount], "-k")){  

     if(argv[Kcount +1][11] != NULL && argv[Kcount +1][12] == NULL){
      puts("You need to pass key with 11 characters!");
      return 2;

    }

      while(i < MAX_KEY){
      key[i] = argv[Kcount +1][i];
      i++;  
    }    
  }
 }

      int count = 0; 
      while(argv[++count] != NULL){
        if(0 == strcmp(argv[count], "-o")){

        fileName = argv[count +1];     //TODO: NPARAWIĆ -o NAZWA ARGUMENT
        }
      }
    }

   
  
  char heading[] = {0,0x56,0x4E,0x46,0,0,0,0,0,0};
 




     FILE *file = fopen(vnfFileName,"rb");
    
     int toal = ToAlloc(file);

     char *ptr = (char*)malloc(toal);
     fclose(file);
     char data[10+toal];
     char Cdata[10+toal+11];

     FILE *file0 = fopen(vnfFileName,"rb");

     FILE *vnf  = fopen(fileName,"wb");
     

     int chr  = getc(file0);
     toal = 0;

     while (chr != EOF) 
     {
        if(chr == 0x5E){// = ^ 
          ptr[toal] = 0x1d;  

          chr = getc(file0);
          toal++;

          continue;
        } 
        ptr[toal] = chr;

        chr = getc(file0);

        toal++;
     }


     fclose(file0);


     char *Cptr = Crypt(ptr,toal);
     memcpy(data,ptr,10+toal);
     
     char *c = ARRAY_CONCAT(char, heading, 10, data, toal);


     char *CdWithKey = ARRAY_CONCAT(char,c,sizeof(data),key,11);


     fwrite(CdWithKey,sizeof(char),10+toal+11,vnf);

     fclose(vnf);
     free(ptr);


	return 0;
}
