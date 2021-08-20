/*
Hazırlayacak olduğunuz encryption isimli program libfdr kütüphanesini
kullanarak parametre olarak aldığı dosyada bulunan kelimeleri (karakter bazında), parametre
olarak aldığı aralıkta üretilecek rasgele sayılar ile XOR operatörü kullanarak şifreleyecek ve yeni
bir şifreli kelime elde edecektir. XOR ile şifrelenmiş dosyayı ilgili dizine kaydedecektir.
Şifreleme işleminin tamamlanması için şifreli dosyadaki veriler libfdr dllist yapısı kullanılarak
ters bir şekilde reverse_encrtpted_file isimli dosyaya yazdırılacaktır.

Örnek :
Okunan kelime(fields kullanılacak)-> sakarya
s-> 73 üretilen random sayı-> 56 şifreli karakter (xor operation)->113 (q)
Örnek çalıştırma : C:\user\unalc> ./encrypt plaintext 0-200
Libfdr-dlllist kullanılarak şifreli dosya ters sırada → reverse_encrtpted_file
isimli dosyaya yazdırılacaktır.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libfdr/fields.h"
#include "libfdr/dllist.h"

char * xorencrypt(char * text, int key);

int main(int argc,char **argv){
    
    FILE *fp;
    IS is;
    Dllist l, tmp;
    int i, r, rmin,rmax;
    char* encrypted;

    if(argc!=3){
        fprintf(stderr,"Yanlış kullanım tipi, Örnek: ./encript <dosya adı> <min>-<max>\n");
        exit(1);
    }

    // setup param 1 <dosya adı>
    is = new_inputstruct(argv[1]);
    if(is==NULL){
        perror(argv[1]);
        exit(1);
    }

    // setup param 2 <min>
    char *str = argv[2];
    char delim[] = "-";
    int init_size = strlen(str);
    if (init_size < 1)
    {
        perror(argv[2]);
        exit(1);
    }
    
    char *ptr = strtok(str, delim);
    rmin = atoi(ptr);

    ptr = strtok(NULL, delim);
	rmax = atoi(ptr);

    if (rmax <= rmin)
    {
        perror(argv[2]);
        exit(1);
    }
    

    //Random Initialization
    srand(time(NULL));

    // random between min and max
    r = rmin + rand() % (rmax + 1 - rmin);

    printf("Crypting key is %d.\n", r);

    //New Doubly Linked Lists
    l = new_dllist();

    while (get_line(is)>=0)
    {
        for (i=0; i < is->NF; i++)
        {
            // Append encrtpted string to list
            encrypted = xorencrypt(strdup(is->fields[i]), r);            
            //dll_append(l, new_jval_s(strdup(is->fields[i])));
            dll_append(l, new_jval_s(encrypted));
            printf("%d: %s -> %s\n", is->line, is->fields[i], encrypted);
        }
    }
    
    dll_rtraverse(tmp, l);

    // Write to file reversed order
    fp = fopen("reverse_encrtpted_file", "w+");
    for (tmp = dll_last(tmp); 
            tmp->val.s != NULL; tmp = tmp->blink)
    {
        fprintf(fp,"%s\n",tmp->val.s);
    }
    fclose(fp);
        
    jettison_inputstruct(is);
    exit(0);

    return 0;
}

char * xorencrypt(char * text, int key) {
    size_t textlen = strlen(text);

    char * encrypted = malloc(textlen+1);

    int i;
    for(i = 0; i < textlen; i++) {
        encrypted[i] = text[i] ^ key;
    }
    encrypted[textlen] = '\0';

    return encrypted;
}