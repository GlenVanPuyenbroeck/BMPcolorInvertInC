#include <stdio.h>
#include <stdlib.h>

struct nodeFile
{
    int *file;
    struct nodeFile *next;
};

static int *memory = NULL;
static struct nodeFile *head_ref= NULL;
static struct nodeFile *BMP = NULL;
static int end =  0;
static int teller = 0;

void setFree(struct nodeFile **head_ref)
{
    struct nodeFile *prev = *head_ref;

    while(*head_ref != NULL)
    {
        *head_ref = (*head_ref) -> next;
        free(prev);
        prev = *head_ref;
    }
}

void append(struct nodeFile** head_ref , FILE * new)
{
       BMP = (struct nodeFile*) malloc(sizeof(struct nodeFile));
       struct nodeFile *last = *head_ref;

       BMP->file  = &end;
       BMP->next = NULL;
       fputc( *BMP -> file , new);

       if (*head_ref == NULL)
       {
          *head_ref = BMP;
          return;
       }

       while (last->next != NULL)
           last = last->next;

       last->next = BMP;
       return;
}

void Data(FILE *bestand,FILE *new)
{
    while ((end = fgetc(bestand)) != EOF )
    {
        memory = (int *)malloc(sizeof(int));
        memory = &end;
        switch(teller)
        {
                case 0 || 1: if((end != 66 ) &&  (end != 77))
                            {
                                printf("Type file klopt niet. Einde programma\n");
                                exit(EXIT_FAILURE);
                            } break;
        }

        (teller < 54  ) ?  append(&head_ref, new) :fputc( ~(*memory),new); ;
        teller++;
        free(memory);
    }
}

int main(void)
{
                FILE *pointer = fopen("C:/Users/11800025/Documents/GitHub/BMPcolorInvertInC/bmpwatamote.bmp","rb"); 	      // Deze opent de input file.
                FILE *invers = fopen("C:/Users/11800025/Documents/GitHub/BMPcolorInvertInC/invers.bmp","wb");              // Zal het geïnverteerde bestand aanmaken met de naam "invers"

                              if(pointer == NULL)   		      // Als de file pointer een null geeft zal de programma stoppen met werken.
                               {
                                     printf("File werd niet geopend.\n");
                                     exit(EXIT_FAILURE);
                               }
                               printf("File werd geopend , karakters worden ingelezen en verwertk\n");

                Data(pointer,invers);                              // verwijzing naar de functie data
                fclose(pointer);
                fclose(invers);
                setFree(&head_ref);
                printf("Einde Programma\n");

    return 0;
}
/*
*Deze programma veranderd de kleuren van een BMP file;
*@param = FILE *pointer.
*@return = is void.
*/
