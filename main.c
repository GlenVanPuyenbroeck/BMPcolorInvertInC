#include <stdio.h>
#include <stdlib.h>

struct nodeFile
{
    int *file;
    int *newFile;
    struct node *next;
    struct node *nextInvers;
};

static int length= 0;
static int widht = 0;
static int newfield = 0;

void Data(FILE*,FILE*);  				// Deze functie koppieërd de header naar de nieuwe file.
void InversData(FILE*,FILE*,int); 				// Deze functie inverteerd de kleuren.
void GrooteAfbeelding(FILE*,FILE*); 			// Deze functie berekend de oppervlakte van de BMP file.
void DataBMP(int,int*);

int main(void)
{
                FILE *pointer = fopen("C:/Users/11800025/Documents/ColorInvert/bmpwatamote.bmp","rb"); 	      // Deze opent de input file.
                FILE *invers = fopen("C:/Users/11800025/Documents/ColorInvert/invers.bmp","wb");              // Zal het geïnverteerde bestand aanmaken met de naam "invers"

                              if(pointer == NULL)   		      // Als de file pointer een null geeft zal de programma stoppen met werken.
                               {
                                     printf("File werd niet geopend.\n");
                                     exit(EXIT_FAILURE);
                               }

                                printf("File werd geopend , karakters worden nu ingelezen\n\n");

                Data(pointer,invers);                              // verwijzing naar de functie data
                GrooteAfbeelding(pointer,invers);
                InversData(pointer,invers,newfield);

                fclose(pointer);
                fclose(invers);

    return 0;
}

void Data(FILE *bestand,FILE *nieuwebestand)
{
    struct nodeFile *head = NULL;
    head = (struct nodeFile*)malloc(sizeof(struct nodeFile));
    int a = 0;

        for (int i = 0; i < 54; i++)
                {
                    a = fgetc(bestand); 	// Leest de karakters één per één.
                    head -> file = &a;
                    head -> next = NULL;
                    fputc( *head -> file ,nieuwebestand); // Zet de gelezen karakters in de nieuwe file.
                    DataBMP(i, head -> file);
                }
}

void DataBMP(int counter , int *data)
{

    switch(counter)
    {
            case 0: if( *data != 66)
                        {
                            printf("Type file klopt niet. Einde programma\n");
                            exit(EXIT_FAILURE);
                        } break;

            case 1 : if(*data != 77)
                           {
                             printf("Type file klopt niet. Einde programma\n");
                              exit(EXIT_FAILURE);
                            } break;
            case 18: if(*data == 44)
                            {
                               printf("Breedte is te klein. Einde programma\n");
                                exit(EXIT_FAILURE);
                            }
                                    else
                                    {
                                        length = *data;
                                    }
            case 22: if(*data == 44)
                            {
                               printf("Lengte is te klein. Einde programma\n");
                                exit(EXIT_FAILURE);
                            }
                                    else
                                    {
                                           widht = *data;
                                    }
    }
}

void GrooteAfbeelding(FILE*originele,FILE* hallo )
{
                printf("Breedte pixels is %d\n",widht);
                printf("Hoogte pixels is %d\n",length);
                newfield = ((widht)*(length)*4)+54;
                printf("Oppervlakte afbeelding = %d\n",newfield); // Standaard formule voor het berekenen van de omtrek.

}

void InversData(FILE *origineel,FILE* nieuw, int lang)
{
        struct nodeFile *head = NULL;
        head = (struct nodeFile*)malloc(sizeof(struct nodeFile));

                int a = 0;
                for (int i = 54; i < lang; i++)
                    {
                          *head -> newFile = fgetc(origineel);
                          head -> next = NULL;
                          a = ~(*head -> newFile);// Karakters worden eerst geïnverteerd voordat ze in de file gezet wordt.
                          fputc(a,nieuw);
                    }


                printf("De afbeelding is met succes aangemaakt. Einde programma\n");
}


/*
*Deze programma veranderd de kleuren van een BMP file;
*@param = FILE *pointer.
*@return = is void.
*/
