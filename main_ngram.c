/* Tubes PPMC N-gram*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define char_max 250

/*struct node{
  char word[char_max];
  struct node* next;
};*/

double N;
FILE *file_ref;
double n_random;
int counter,j;
struct data{
    char text[char_max];
    char next[20][char_max];
    int id_count;

};

struct string{
  char teks[char_max];
};

void cetak(struct data *unique_array)
{
	printf("\n(cetak string)\n");
	srand((unsigned)time(0));
    printf("%s", (*(unique_array+rand()%30)).text);//print kata random dari unique_array[].text
}

bool isExist(char text[],struct data *array){
  for(int i=0;i<counter;i++){
    if(strcmp(text,(*(array+i)).text)==0){
      return(true);
    }
  }
  return(false);
}

void pemecah_kata(double n, FILE *fp, struct string *trans_array,struct data *unique_array){//struct string *next_array
   //N itu input Ngram
  char str[char_max];
  char temp[char_max];
  char next_temp[char_max];
  if(fp == NULL) {
      printf("Error opening file");
  }
  counter=0;

  //tester masuk array total
  while( fscanf(fp, "%s", str) != EOF){
      strcpy((*(trans_array+counter)).teks,str);
      //printf("elemen ke %d : %s\n", counter,(*(trans_array+counter)).teks);
      counter+=1;
  }
  printf("elemen ke 0 : %s\n",(*(trans_array+4)).teks);
  //masukkin unique combo ke array
  j =0;
  int h =0;
  //printf("1\n");
  while((j - N < counter)&&(counter-j>N)) {
    strcpy(temp, (*(trans_array+j)).teks);
    for(int k= 1;k<N;k++){
      strcat(strcat(temp," "),(*(trans_array+(j+k))).teks);
      strcpy(next_temp,(*(trans_array+(j+k+1))).teks);
    }
    //printf("2\n");
    if(isExist(temp,unique_array)==false){
      strcpy((*(unique_array+h)).text,temp);
      strcpy((*(unique_array+h)).next[0],next_temp);
      (*(unique_array+h)).id_count = 1;

      h+=1;
    }
    else{
      //printf("4\n");
      for(int z=0;z<(counter+1);z++){
        if(strcmp(temp,(*(unique_array+z)).text)==0){
          int k = 0;
          while(strcmp(next_temp,(*(unique_array+z)).next[k])==0){
            k+=1;
          }
          strcpy((*(unique_array+z)).next[k+1],next_temp);
          (*(unique_array+z)).id_count += 1;
          printf("%d elemen ke %d : %s\n",z,(k+1),(*(unique_array+z)).next[k+1]);
          printf("%d elemen ke %d : %d\n",z,(k+1),(*(unique_array+z)).id_count);
          printf("%d elemen ke %d : %s\n",z,(k+1),(*(unique_array+z)).next[k+1]);
        }
      }
      //printf("5\n");
    }
    j+=1;
  }
  
  printf("%s\n",(*(unique_array+0)).next[0]);
  printf("%s\n",(*(unique_array+0)).next[1]);
  printf("%d\n",(*(unique_array+0)).id_count);
	//inicuma buat testing
  printf("%s\n",(*(unique_array+0)).text);
  printf("%s\n",(*(unique_array+0)).next[0]);
  printf("%s\n",(*(unique_array+0)).next[1]);
  fclose(fp);
}

void menu(){
    printf("===PROGRAM N-GRAM===\n\n");
    printf("Sekilas tentang n-gram : \n");
    printf("N-gram merupakan sebuah model yang digunakan untuk memprediksi kata berikutnya yang mungkin dari kata N-1 sebelumnya. \nN-gram menampilkan probabilitas kemungkinan pada kata selanjutnya yang mungkin dapat digunakan untuk melakukan kemungkinan penggabungan pada keseluruhan kalimat.\nSebuah string yang terdiri dari kata-kata acak akan dibuat dan program n-gram akan membuat string acak tersebut memiliki gaya penulisan manusia.\n\n");
}


void main(){
  struct data* unique_array;
  struct string* trans_array;
  struct string* next_array;
  char namaFile[30];
  unique_array = (struct data*)malloc(100000*sizeof(struct data));
  trans_array= (struct string*)malloc(100000*sizeof(struct string));
  next_array= (struct string*)malloc(100000*sizeof(struct string));//tester array
  next_array= (struct string*)malloc(100000*sizeof(struct string));
  char temp[char_max];
  char isLoop, isLoop2;

  menu();
  printf("Nama file referensi: ");
  scanf("%s", &namaFile);
  file_ref = fopen(namaFile,"r");

  do{
    printf("Masukkan nilai N: ");
    scanf("%lf", &N);
    if(N<=2){
        printf("Nilai N tidak valid!\n");
    }
  }while(N<=2);

  pemecah_kata(N,file_ref,trans_array,unique_array);

  
}
=======
  pemecah_kata(N,file_ref,trans_array,unique_array);//next_array
  
}
