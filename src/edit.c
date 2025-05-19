#include <stdlib.h>
#include <stdio.h>              // Dosya işlemleri için gerekli (fopen, fgets, fclose)
#include <string.h>             // String işlemleri için gerekli (strncpy, strcspn)
#include <ncurses.h>           // ncurses kütüphanesi
#include "texteditor.h"       

void edit(char *filename) {
    // ncurses başlat
    initscr();                // ncurses modunu başlat
    cbreak();                 // Karakterleri hemen al
    noecho();                 // Klavye girişlerini ekrana yazma

    FILE *fp = fopen(filename, "r");  // Dosyayı okuma modunda açmayı dene

    // Her çağrıda textbuffer'ı sıfırla (temiz buffer ve free list oluştur)
    for (int i = 0; i < 24; i++) {
        textbuffer[i].next = i + 1;   // Free list için sıradaki düğümü işaret et
        textbuffer[i].prev = i - 1;      // Henüz kullanılmıyor, prev boş (-1)
    }
    textbuffer[24].next = -1;         // Son düğümün nexti -1 olmalı (end of list)
    textbuffer[24].prev = 23;

    free_head = 0;       // Free list'in başını 0. düğüme ayarla
    inuse_head = -1;     // Kullanılan aktif liste şu an boş

    // Eğer dosya yoksa (fp == NULL), yeni boş dosya oluştur ve fonksiyonu bitir
    if (!fp) {
        fp = fopen(filename, "w");    // Yazma modunda aç (yeni boş dosya)
        if (fp) fclose(fp);           // Dosyayı kapat
        fp = fopen(filename, "r");  // Okuma modunda tekrar aç      
    }

    char buffer[40];       // Geçici buffer: dosyadan okunan bir satırı tutar (max 39 karakter + '\0')
    int prev_index = -1;   // Bağlantıları kurarken önceki düğümün index'i

    // Dosyadaki her satırı sırayla oku
    while (fgets(buffer, sizeof(buffer), fp)) {
        // fgets() sonunda '\n' karakteri bırakır bunu temizliyoruz alt satırda
        buffer[strcspn(buffer, "\n")] = '\0';

        // Eğer free list boş ise yani buffer doluysa kullanıcıyı uyar ve işlemi kes
        if (free_head == -1) {
            printw("Text buffer is full.\n");
            refresh();
            getch(); // Kullanıcının bir tuşa basmasını bekle
            break;
        }

        // free listten bir düğüm al (ilk boş düğüm)
        int idx = free_head;
        free_head = textbuffer[idx].next;  // free_head = next boş düğüm

        // Satır verisini düğüme kopyala 
        strncpy(textbuffer[idx].statement, buffer, 39);
        textbuffer[idx].statement[39] = '\0';  // null sonlandırıcı

        textbuffer[idx].prev = prev_index;   // Bu düğümün prev'i, bir önceki düğüm
        textbuffer[idx].next = -1;           // Şimdilik son düğüm

        if (prev_index != -1)
            textbuffer[prev_index].next = idx;  // Önceki düğümün nextini güncelle
        else
            inuse_head = idx;  // Eğer ilk düğümse, inuse_head olarak ayarla

        prev_index = idx;  // Bir sonraki satır için prev_index güncelle
    }
    fclose(fp);  // Dosya okuma işlemi bittiğinde dosyayı kapat

   
}

