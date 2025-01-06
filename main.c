#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sistem düğüm yapısı
typedef struct Sistem
{
    char isim[50];
    int menzil;
    struct Sistem *sonraki;
} Sistem;

Sistem *uzunMenzil = NULL;

Sistem *uzunSistemEkle(Sistem *bas, char *isim)
{
    Sistem *yeni = (Sistem *)malloc(sizeof(Sistem));
    strcpy(yeni->isim, isim);
    // Uzun menzili 3 ayarlama.
    yeni->menzil = 3;
    // Yeni eklenen elemanı başa ekleme.
    yeni->sonraki = bas;
    return yeni;
}

Sistem *uzunSistemSil(Sistem *bas, char *isim)
{
    Sistem *suan = bas;
    Sistem *onceki = NULL;
    // listeyi dolaşma işlemi
    while (suan)
    {
        if (strcmp(suan->isim, isim) == 0)
        {
            // Baş eleman silinirse sonraki elemanı baş yapma.
            if (onceki == NULL)
            {
                bas = suan->sonraki;
            }
            else
            {
                // Öncekini sonrakiyle ilişkilendirme
                onceki->sonraki = suan->sonraki;
            }
            free(suan);
            printf("Sistem '%s' gönderildi.\n", isim);
            return bas;
        }
        onceki = suan;
        suan = suan->sonraki;
    }
    printf("Sistem '%s' bulunamadı.\n", isim);
    return bas;
}

void uzunSistemListele(Sistem *bas)
{
    printf("\n[Uzun Menzilli Savunma Sistemleri]:\n");
    // Tarama ve listeleme işlemi
    while (bas)
    {
        printf("- %s\n", bas->isim);
        bas = bas->sonraki;
    }
}

// 2. Queue (Orta Menzilli Sistemler)
typedef struct Queue
{
    Sistem *bas;
    Sistem *son;
} Queue;

Queue *ortaMenzil;

Queue *ortaKuyrukOlustur()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->bas = q->son = NULL;
    return q;
}

void ortaKuyrukEkle(Queue *q, char *isim)
{
    Sistem *yeni = (Sistem *)malloc(sizeof(Sistem));
    strcpy(yeni->isim, isim);
    yeni->menzil = 2;
    yeni->sonraki = NULL;
    if (!q->son)
    {
        q->bas = q->son = yeni;
    }
    else
    {
        q->son->sonraki = yeni;
        q->son = yeni;
    }
}

void ortaKuyrukSil(Queue *q)
{
    if (!q->bas)
    {
        printf("Orta Menzilli Sistemler boş.\n");
        return;
    }
    Sistem *silinecek = q->bas;
    q->bas = q->bas->sonraki;
    if (!q->bas)
    {
        q->son = NULL;
    }
    printf("Sistem '%s' gönderildi.\n", silinecek->isim);
    free(silinecek);
}

void ortaKuyrukListele(Queue *q)
{
    printf("\n[Orta Menzilli Savunma Sistemleri]:\n");
    Sistem *suan = q->bas;
    while (suan)
    {
        printf("- %s\n", suan->isim);
        suan = suan->sonraki;
    }
}

typedef struct Stack
{
    Sistem *ust;
} Stack;

Stack *kisaMenzil;

Stack *kisaYiginOlustur()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->ust = NULL;
    return s;
}

void kisaYiginEkle(Stack *s, char *isim)
{
    Sistem *yeni = (Sistem *)malloc(sizeof(Sistem));
    strcpy(yeni->isim, isim);
    yeni->menzil = 1;
    yeni->sonraki = s->ust;
    // Yığının üstüne ekleme işlemi
    s->ust = yeni;
}

void kisaYiginSil(Stack *s)
{
    if (!s->ust)
    {
        printf("Kısa Menzilli Sistemler boş.\n");
        return;
    }
    // Silinecek sistemi tanımlama
    Sistem *silinecek = s->ust;
    // Üstteki elemanı sonrakiyle ilişkilendirme
    s->ust = s->ust->sonraki;
    printf("Sistem '%s' gönderildi.\n", silinecek->isim);
    free(silinecek);
}

void kisaYiginListele(Stack *s)
{
    printf("\n[Kısa Menzilli Savunma Sistemleri]:\n");
    Sistem *suan = s->ust;
    while (suan)
    {
        printf("- %s\n", suan->isim);
        suan = suan->sonraki;
    }
}

// 4. Kullanıcı Menüsü
void menu()
{
    printf("\n=== HAVA SAVUNMA SİSTEMİ ===\n");
    printf("1. Uzun Menzilli Sistem Ekle\n");
    printf("2. Orta Menzilli Sistem Ekle\n");
    printf("3. Kısa Menzilli Sistem Ekle\n");
    printf("4. Uzun Menzilli Sistem Gönder\n");
    printf("5. Orta Menzilli Sistem Gönder \n");
    printf("6. Kısa Menzilli Sistem Gönder \n");
    printf("7. Tüm Sistemleri Listele\n");
    printf("8. Çıkış\n");
    printf("Seçiminiz: ");
}

int main()
{
    ortaMenzil = ortaKuyrukOlustur();
    kisaMenzil = kisaYiginOlustur();
    int secim;
    char isim[50];

    do
    {
        menu();
        scanf("%d", &secim);

        switch (secim)
        {
        // Uzun Menzil EKleme İşlemi
        case 1:
            printf("Eklenecek Uzun Menzilli Hava Sistem İsmi: ");
            scanf(" %[^\n]s", isim);
            uzunMenzil = uzunSistemEkle(uzunMenzil, isim);
            printf("Sistem eklendi!\n");
            break;
        // Orta Menzil Ekleme İşlemi
        case 2:
            printf("Eklenecek Orta Menzilli Hava Sistem İsmi: ");
            scanf(" %[^\n]s", isim);
            ortaKuyrukEkle(ortaMenzil, isim);
            printf("Sistem eklendi!\n");
            break;
        // Kısa Menzil Ekleme İşlemi
        case 3:
            printf("Eklenecek Kısa Menzilli Hava Sistem İsmi: ");
            scanf(" %[^\n]s", isim);
            kisaYiginEkle(kisaMenzil, isim);
            printf("Sistem eklendi!\n");
            break;
        // Uzun Menzil Silme İşlemi
        case 4:
            printf("Silinecek Uzun Menzilli Hava Sistem İsmi: ");
            scanf(" %[^\n]s", isim);
            uzunMenzil = uzunSistemSil(uzunMenzil, isim);
            break;
            // Orta Menzil Silme İşlemi
        case 5:
            ortaKuyrukSil(ortaMenzil);
            break;
        // Kısa Menzil Silme İşlemi
        case 6:
            kisaYiginSil(kisaMenzil);
            break;
        ////Listeleme İşlemi
        case 7:
            uzunSistemListele(uzunMenzil);
            ortaKuyrukListele(ortaMenzil);
            kisaYiginListele(kisaMenzil);
            break;
        case 8:
            printf("Sistemden çıkılıyor...\n");
            break;
        default:
            printf("Geçersiz seçim! Tekrar deneyin.\n");
        }
    } while (secim != 8);

    return 0;
}