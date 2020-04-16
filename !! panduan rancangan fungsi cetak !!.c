//Panduan cetak untuk qiva

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