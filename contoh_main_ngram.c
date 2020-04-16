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
        }
      }
      //printf("5\n");
    }
    j+=1;
  }
  
  printf("%s\n",(*(unique_array+0)).next[0]);
  printf("%s\n",(*(unique_array+0)).next[1]);
  printf("%d\n",(*(unique_array+0)).id_count);
  fclose(fp);
}

void tabelngram(double n, FILE *fp, struct string *trans_array,struct data *unique_array){
    double N;
    printf("\t\t***Tabel n gram***\n\n");
    printf("\t\t%3s%12s\n","KEY","VALUE");
    i=0;
    while(unique_array+1){
        if (next_count>1){
        	printf("\t\t%{200s%11}.{200s%11}\n",(*(unique_array+0)).text,(*(unique_array+0)).next[0]));
        }
	else {
		printf("\t\t%200s%11.200s%11\n",(*(unique_array+0)).text,(*(unique_array+0)).next[0]));
        i+=1;
	}
    }
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

  //proses cetak

  //1. pilih key random sebagai awalan --> langsung cectak ke layar!
  //2. langsung akses value dari key tsb. agar random, pake rand()%.id_count 
  //yang merupakan structure dari data yang merepresentasikan ada brp value
  //yang diasosiasikan dengan key tsb --> langsung cetak ke layar!
  //3. simpan value yang terpilih ke suatu variabel temporary
  //4. lakukan declutter string spt di bawah :

  //memasukkan string random dari unique array ke dalam queue
  //masing2 node dalam queue menyimpan satu kata, jadi
  //string dalam key harus dipecah
  //langakh2 untuk memecah string
  printf("%s\n",(*(unique_array+0)).text);//untuk nge cek, pilihan 0 hanya untuk percobaan. nanti di isi dengan hasil index rand yang dipilih sebelumnya
  strcpy(temp,(*(unique_array+0)).text);//taro di temp untuk sementara aja
  j=0; int ctr=0;//counter operator
  for(int i=0;i<=(strlen(temp));i++){
    //jika ditemukan space atau null
    if(temp[i]==' '||temp[i]=='\0'){
      (*(next_array+ctr)).teks[j] = '\0';
      ctr++;//untuk kata selanjutnya
      j=0;
    }
    else{
      (*(next_array+ctr)).teks[j] = temp[i]; //langsung disusun
      j++;
    }
  }
  //next array ini nantinya diganti jadi queue
  printf("\n Strings or words after split by space are :\n");
  for(int i=0;i < ctr;i++){
    printf(" %s\n",(*(next_array+i)).teks);
  }//ini hanya untuk testing hasil

  //5. !! queue dipasang dengan kapasitas = N gram
  //6. queue yang sudah diisi dengan key awalan, lakukan dequeue(membuang) pada kata pertama
  //7. lakukan enqueue(memasukkan data), data yang dimasukkan adalah value yang didapat(yang disimpan di temp)
  //8. !!mungkin buat fungsi untuk step 8 ini!
  //bikin queue proxy, yang nanti isinya sama queue asli ini
  //satukan semua word dari masing2 node jadi 1 string utuh
  //cara satuin --> akses data di head terus pop. di loop sampe queue proxy hilang/ semua data ke ambil
  //lakukan pencocokan dengan key yang ada untuk mendapatkan value berikutnya
  //cetak value yang didapat ke layar!
  //9. lakukan dequeue dan enqueue seperti sebelumnya pada QUEUE ASLI
  //10. ulangi step 8 sampe 9 hingga jumlah kata random tercapai.
}
