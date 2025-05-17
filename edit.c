#include <stdio.h>              // Dosya islemleri icin gerekli (fopen, fgets, fclose)
#include <string.h>             // String islemleri icin gerekli (strncpy, strcspn)
#include "cse232editor.h"       
// edit fonksiyonu  dosyayi acar , okur ve buffera yukler

// node textbuffer[25];        // 25 satırlık editor buffer'i (her eleman bir node)
// int free_head = 0;          // Free list'in başını gösteren index (boş düğümlerin bağlı listesi)
// int inuse_head = -1;        // Kullanılan bağlı listenin (aktif satırlar) başını gösteren index
// Edit fonksiyonu:
// - Kullanicidan alinan dosya adini parametre olarak alır.
// - Eger dosya varsa, satirlari okur ve textbuffer[]'a bagli liste seklinde yukler.
// - Eger dosya yoksa, bos bir dosya olusturur ve cikis yapar.
void edit(char *filename) {
    FILE *fp = fopen(filename, "r");  // Dosyayı okuma modunda açmayı dene
    // Her çağrıda textbuffer'ı sıfırla (temiz buffer ve free list oluştur)
    for (int i = 0; i < 24; i++) {
        textbuffer[i].next = i + 1;   // Free list için sıradaki düğümü işaret et
        textbuffer[i].prev = -1;      // Henüz kullanılmıyor, prev boş (-1)
    }
    textbuffer[24].next = -1;         // Son düğümün nexti -1 olmalı (end of list)
    textbuffer[24].prev = -1;

    free_head = 0;       // Free list'in başını 0. düğüme ayarla
    inuse_head = -1;     // Kullanılan aktif liste şu an boş
    // Eğer dosya yoksa (fp == NULL), yeni boş dosya oluştur ve fonksiyonu bitir
    if (!fp) {
        fp = fopen(filename, "w");    // yazma modunda ac (yeni boş dosya)
        if (fp) fclose(fp);           // dosyayi kapat
        return;                       
    }
    char buffer[40];       // gecici buffer: dosyadan okunan bir satırı tutar (max 39 karakter + '\0')
    int prev_index = -1;   // Bağlantıları kurarken önceki düğümün index'i

    // Dosyadaki her satırı sırayla oku
    while (fgets(buffer, sizeof(buffer), fp)) {
        // fgets() sonunda '\n' karakteri bırakır bunu temizliyoruz alt satirda
        buffer[strcspn(buffer, "\n")] = '\0';

        // Eger free list bos ise yani buffer doluysa kullanıcıyı uyar ve işlemi kes
        if (free_head == -1) {
            printf("Text buffer is full.\n");
            break;
        }

        // free listten bir düğüm al (ilk boş düğüm)
        int idx = free_head;
        free_head = textbuffer[idx].next;  // free_head = next bos dugum

        // Satır verisini düğüme kopyala 
        strncpy(textbuffer[idx].statement, buffer, 39);
        textbuffer[idx].statement[39] = '\0';  // null sonlandırıcı

        
        textbuffer[idx].prev = prev_index;   // bu dugumun prev'i, bir önceki dugum
        textbuffer[idx].next = -1;           // simdilik son düğüm

        if (prev_index != -1)
            textbuffer[prev_index].next = idx;  // onceki dugumun nextini guncelle
        else
            inuse_head = idx;  // eger ilk dugumse, inuse_head olarak ayarla

        prev_index = idx;  // Bir sonraki satir icin prev_index guncelle
    }
    fclose(fp);  // Dosya okuma islemi bittiginde dosyayı kapat
}



