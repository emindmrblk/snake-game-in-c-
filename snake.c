#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define satir_sayisi 16
#define kolon_sayisi 8


#define LIKELY(x) __builtin_expect(!!(x),1)
#define UNLIKELY(x) __builtin_expect(!!(x),0) 


typedef struct 
{
    uint8_t i;
    uint8_t j;

}konum;


typedef struct 
{
    char *map[kolon_sayisi][satir_sayisi];
    konum govde[kolon_sayisi*satir_sayisi];// başından konum takibi
    int8_t health;
    uint8_t uzunluk;

}Snake;

Snake s;


void map_Olustur();
void yem_Olustur();
void snake_Olustur();

void dinamikMap(char yon);
void klavyegirdisi_Al();


typedef void (*calismaSirasi)();
void run();

int main(){

    s.health = 3;
    s.uzunluk = 1;

    srand(time(NULL));  
    return 0;
}


void map_Olustur(){
    
    for (uint8_t i = 0; i < kolon_sayisi; i++)
    {
        for (uint8_t j = 0; j < satir_sayisi; j++)
        {
            printf("[ ]"); 
        }
        printf("\n");
    }
    
}

void yem_Olustur(){
    

    uint8_t kolonYem = rand() % 8;
    uint8_t satirYem = rand() % 16;

    if (s.map[kolonYem][satirYem] != "[•]") // yılan orada değil ise oluştur
    {
        s.map[kolonYem][satirYem] = "[.]";    
    }
    else yem_Olustur();
    
}

void snake_Olustur(){ 
    
    
    uint8_t kolonSnake = rand() % 8;
    uint8_t satirSnake = rand() % 16;


    
    if (s.map[kolonSnake][satirSnake] != "[.]")
    {   
        s.map[kolonSnake][satirSnake] = "[•]";
        s.govde[0].i = kolonSnake;
        s.govde[0].j = satirSnake;

    }
    else snake_Olustur();
    
}

void klavyegirdisi_Al(){

    while (1){
        if ( _kbhit() ){
            int key_code = _getch();
            if (key_code == 27)
            {
                break;
            }

            if (key_code == 224 || key_code == 0)
            {
                int yon = _getch();

                if (yon == 80) // asagi yon tusu
                {
                    dinamikMap('s');
                }
                else if (yon == 72) // yukari yon
                {
                    dinamikMap('w');
                }
                else if (yon == 77) // sag
                {
                    dinamikMap('d');
                }
                else if (yon == 75) // sol
                {
                    dinamikMap('a');
                }
                dinamikMap('k');
            }else{
                if (key_code == 'w')
                {
                    dinamikMap('w')
                }
                else if (key_code == 's')
                {
                    dinamikMap('s');
                }
                else if (key_code == 'a')
                {
                    dinamikMap('a');   
                }
                else if (key_code == 'd')
                {
                    dinamikMap('d');
                }
                dinamikMap('k');
            }
            
        }
        else continue;
       
            
    }

}

void dinamikMap(char yon){

    char ensonBasilan = 'k';
    bool yemvar = false;
    for (uint8_t i = 0; i < kolon_sayisi; i++)
    {
        for (uint8_t j = 0; j < satir_sayisi; j++)
        {
            if (strcmp(s.map[i][j],"[.]") == 0) // yem var mi diye taranır
            {
                yemvar = true;  
                break; 
            }
        }
        if (yemvar)
        {
            break;
        }
        
    }
    if (!yemvar)
    {
        yem_Olustur();
    }
    

    for (uint8_t i = 0; i < kolon_sayisi; i++)
    {
        for (uint8_t j = 0; j < satir_sayisi; j++)
        {
            
            if (s.map[i][j] == "[•]") 
            {
                char aktifYon = 'k';

                if (yon != 'k') {
                aktifYon = yon;
                ensonBasilan = yon;
                } 
                else if (ensonBasilan != 'k') {
                    aktifYon = ensonBasilan;
                } 
                else {
                    char yonler[4] = {'w', 's', 'a', 'd'};
                    aktifYon = yonler[rand() % 4];
                    ensonBasilan = aktifYon; 
                }
            
                
                int8_t yeni_i = s.govde[0].i;
                int8_t yeni_j = s.govde[0].j;

                if (yeni_i < 0 || yeni_i >= satir_sayisi || yeni_j < 0 || yeni_j >= kolon_sayisi) {
                    s.health--; // Duvara carpti, cani azalt (veya oyunu bitir)
                    return;
                }

                int8_t eskikuyruk_i = s.govde[s.uzunluk-1].i; // en sonki indisin bir fazlasi aslinda yeni govdenin parcasidir.
                int8_t eskikuyruk_j = s.govde[s.uzunluk-1].j;

                if (aktifYon == 'w')      yeni_i++;
                else if (aktifYon == 's') yeni_i--;
                else if (aktifYon == 'a') yeni_j--;
                else if (aktifYon == 'd') yeni_j++;

                
                for (int k = s.uzunluk-1; k > 0; k--)
                {
                    s.govde[k] = s.govde[k-1];
                }
                
                bool yemYendi = false;
                if (yeni_i >= 0 && yeni_i < satir_sayisi && yeni_j >= 0 && yeni_j < kolon_sayisi) {
                    
                    if (strcmp(s.map[yeni_i][yeni_j],"[.]") == 0) // yem yendiyse
                    { 
                         yemYendi = true;
                    }
                    yenikonum[yeni_i][yeni_j] = s.map[yeni_i][yeni_j];
                }
                s.map[yeni_i][yeni_j] = "[•]";
                if (yemYendi) // kuyruğun sonuncu indisi ilerlendiği için
                {
                    s.govde[s.uzunluk].i = eskikuyruk_i;
                    s.govde[s.uzunluk].j = eskikuyruk_j;

                    s.uzunluk++;

                    s.map[eskikuyruk_i][eskikuyruk_j] = "[*]" // uzunluğu arttırdık

                }else{
                    s.map[eskikuyruk_i][eskikuyruk_j] = "[ ]"; 
                }
                
            
            }
        
        }
    }
    
}