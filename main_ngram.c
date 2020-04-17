/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok : 4 (Rombongan E)
* Hari dan Tanggal : Jumat, 17 April 2020
* Asisten (NIM) : Ryan D. C. (13217018)
* Nama File : main_ngram.c
* Deskripsi : N-Grams
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define char_max 250


double N;
FILE *file_ref;
unsigned int n_random;
int counter,j, h, k;
char temp_print[char_max];

struct data{
    char text[char_max];
    char next[20][char_max];
    int id_count;
};

struct string{
  char teks[char_max];
};

bool isExist(char text[],struct data *array){
  for(int i=0;i<counter;i++){
    if(strcmp(text,(*(array+i)).text)==0){
      return(true);
    }
  }
  return(false);
}

bool isNext_Exist(char text[],struct data *array){
  for(int i=0;i<counter;i++){
    for(int k=0; k<20;k++){
      if(strcmp(text,(*(array+i)).next[k])==0){
        return(true);
      }
    }
  }
  return(false);
}

void pemecah_kata(double n, FILE *fp, struct string *trans_array,struct data *unique_array){//struct string *next_array
  char str[char_max];
  char temp[char_max];
  char next_temp[char_max];

  counter=0;

  //tester masuk array total
  while(fscanf(fp, "%s", str) != EOF){
      strcpy((*(trans_array+counter)).teks,str);
      counter+=1;
  }
  //masukkin unique combo ke array
  j =0;h=0;k=0;
  while((j - N < counter)&&(counter-j>N)) {
    strcpy(temp, (*(trans_array+j)).teks);
    for(int k= 1;k<N;k++){
      strcat(strcat(temp," "),(*(trans_array+(j+k))).teks);
      strcpy(next_temp,(*(trans_array+(j+k+1))).teks);
    }
    if(isExist(temp,unique_array)==false){
      strcpy((*(unique_array+h)).text,temp);
      strcpy((*(unique_array+h)).next[0],next_temp);
      (*(unique_array+h)).id_count = 1;
      h+=1;
    }
    else{
      for(int z=0;z<(counter+1);z++){
        if(strcmp(temp,(*(unique_array+z)).text)==0){
          if(isNext_Exist(next_temp,unique_array)==false){
            //kalo ga sama
            strcpy((*(unique_array+z)).next[(*(unique_array+z)).id_count],next_temp);
            (*(unique_array+z)).id_count += 1;
          }
        }
      }
    }
    j+=1;
  }
}

void tabelngram(struct data *unique_array){
    int i=0, next_count = -1; char value[99];
    printf("\t\t\t***Tabel n gram***\n\n");
    printf("%200s%25.200s\n","KEY","VALUE");

    while (next_count != 0) {
        next_count = (*(unique_array+i)).id_count;
        if (next_count > 1){
            strcat(value, "{");
            strcat(value, ((*(unique_array+i)).next[0]));

            for (int j = 1; j < next_count; j++){
                    strcat(value, ", ");
                    strcat(value, ((*(unique_array+i)).next[j]));
            }
            strcat(value, "}");
            printf("%200s%25.200s\n",((*(unique_array+i)).text), value);

        }else{
            printf("%200s%25.200s\n",((*(unique_array+i)).text),((*(unique_array+i)).next[0]));
        }
        i+=1;
    }
}

void cetak_loop(char temp_print[],struct data *unique_array,double N){
    srand((unsigned)time(0));
    char temp2[char_max];
    int rand_num3;
    int point = N+1;
    while(point<n_random){
      for(int z=0;z<(h+1);z++){
        if(strcmp(temp_print,(*(unique_array+z)).text)==0){//kalo key sama
          rand_num3=(rand()%(*(unique_array+z)).id_count);
          printf(" %s",(*(unique_array+z)).next[rand_num3]);
          strcat(strcat(temp_print," "),(*(unique_array+z)).next[rand_num3]);
        }
      }
      int count=0;
      while(temp_print[count]!=' '){
        count++;
      }
      j=0;
      //diatas ini tujuannya untuk tau space/batas kata pertama di mana
      for(int i=(count+1);i<=strlen(temp_print);i++){
        temp2[j]=temp_print[i];
        j++;
      }//susun ke temporary, sisa kalimat tanpa kata pertama
      strcpy(temp_print,temp2);
      point++;
    }
    printf("...");
}

void cetak(struct string *next_array, struct data *unique_array,char temp_print[], double N){
  srand((unsigned)time(0));
  char temp[char_max];
  int rand_num1;

  rand_num1 = rand()%(h+1);//h di sini tuh Neff nya key di unique array, randomin key yang keluar
  strcpy(temp,(*(unique_array+rand_num1)).text);//taro di temp untuk dipotong aja, dipisah perkata
  //ini untuk mecah dari 1 kalimat panjang jadi beberapa kata
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


  //mulai proses cetak
  printf("\n...");
  printf("%s",(*(next_array+0)).teks);//cetak kata pertama dari key random yang udah dipisah

  //print sisa kata dari key random yang udah dipisah
  for(int i=1;i < ctr;i++){
    printf(" %s",(*(next_array+i)).teks);
  }
  //untuk nyusun key selanjutnya, di mana kata pertama dari key sebelumnya dibuang
  strcpy(temp_print,(*(next_array+1)).teks);
  for(int i = 2;i<=(N-1);i++){
    strcat(strcat(temp_print," "),(*(next_array+i)).teks);
  }//nyatuin sama sisa kata dari key random sebelumnya yang udah dipisah
    int rand_num2; //untuk random value dari key sebelumnya
    rand_num2=(rand()%(*(unique_array+rand_num1)).id_count);
    //langsung cetak value dari key pertama
    printf(" %s",(*(unique_array+rand_num1)).next[rand_num2]);
    //satuin sama word yang sebelumnya untuk membentuk key selanjutnya
    strcat(strcat(temp_print," "),(*(unique_array+rand_num1)).next[rand_num2]);
    cetak_loop(temp_print,unique_array,N);
}

void menu(){
    printf("===PROGRAM N-GRAM===\n\n");
    printf("Sekilas tentang n-gram : \n");
    printf("N-gram merupakan sebuah model yang digunakan untuk memprediksi kata berikutnya \nyang mungkin dari kata N-1 sebelumnya. N-gram menampilkan probabilitas pada kata \nselanjutnya yang mungkin dapat digunakan untuk melakukan kemungkinan penggabungan \npada keseluruhan kalimat.\n\n");
}


int main(){
  struct data* unique_array;
  struct string* trans_array;
  struct string* next_array;
  char namaFile[30];
  char temp[char_max];

  unique_array = (struct data*)malloc(100000*sizeof(struct data));
  trans_array= (struct string*)malloc(100000*sizeof(struct string));
  next_array= (struct string*)malloc(100000*sizeof(struct string));//tester array

  char isLoop, isLoop2;
   menu();
    do{
    //input
     do {
        printf("Nama file referensi: ");
        scanf("%s", &namaFile);
        file_ref = fopen(namaFile,"r");

        if (!file_ref)
            printf("File tidak ada!\n");

    }while (!file_ref);

    do {
        printf("Masukkan nilai N: ");
        scanf("%lf", &N);
        if (N < 3)
            printf("Nilai N tidak valid!\n");
    } while (N < 3);

    pemecah_kata(N,file_ref,trans_array,unique_array);
    fclose(file_ref);
    tabelngram(unique_array);

    do {
        printf("Masukkan jumlah kata random : ");
        scanf("%u", &n_random);
        if(n_random <2000)
            printf("Nilai tidak valid!\n");
        else{
            cetak(next_array,unique_array,temp_print,N);
            printf("\nMasih ingin memasukkan n random?[Y/N]: ");
            scanf("%s", &isLoop2);}
        system("cls");
    }while (n_random < 2000 || isLoop2 == 'Y');

    printf("\nMasih ingin memasukkan nama file?[Y/N]: ");
    scanf("%s", &isLoop);

    system("cls");

    }while (isLoop == 'Y');

    return 0;

}

