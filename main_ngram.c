/* Tubes PPMC N-gram*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#define N 3
#define char_max 250

/*struct node{
  char word[char_max];
  struct node* next;
};*/

double N;
FILE *file_ref;
double n_random;
struct data{
    char text[char_max];
    char next[20][char_max];
};

struct string{
  char teks[char_max];
};

bool isExist(char text[],struct data *array){
  for(int i=0;i<2000;i++){
    if(strcmp(text,(*(array+i)).text)==0){
      return(true);
    }
  }
  return(false);
}

void pemecah_kata(double n, FILE *fp, struct string *trans_array,struct data *unique_array){
  int counter,j; //N itu input Ngram
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

  //masukkin unique combo ke array
  j =0;
  int h =0;
  while((j - N < counter)) {
    strcpy(temp, (*(trans_array+j)).teks);
    for(int k= 1;k<N;k++){
      strcat(strcat(temp," "),(*(trans_array+(j+k))).teks);
      strcpy(next_temp,(*(trans_array+(j+k+1))).teks);
    }
    
    if(isExist(temp,unique_array)==false){
      strcpy((*(unique_array+h)).text,temp);
      //strcpy(next_temp,tempat nyimpen next word di data pattern)
      printf("elemen ke %d : %s\n",h, unique_array[h].text);
      printf("%s\n",next_temp);
      h+=1;
    }
    //kalau dia udah pernah ada
    //bikin program untuk looping si tempat penyimpanan next_word dari pattern yang bersangkutan
    //terus taruh di setelahnya
    j+=1;
  }
  printf("%s\n",(*(unique_array+0)).text);
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
  char namaFile[30];
  unique_array = (struct data*)malloc(100000*sizeof(struct data));
  trans_array= (struct string*)malloc(100000*sizeof(struct string));
  char temp[char_max];
  char isLoop, isLoop2;

  menu();
  printf("Nama file referensi: ");
  scanf("%s", &namaFile);
  file_ref = fopen(namaFile,"r");

  do{
    printf("Masukkan nilai N: ");
    scanf("%lf", &N);
    if(N<2){
        printf("Nilai N tidak valid!\n");
    }
  }while(N<2);

  pemecah_kata(N,file_ref,trans_array,unique_array);
  
}