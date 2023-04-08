/*
Run command:
gcc c_grep.c -o c_grep.out && ./c_grep.out 'pattern1|pattern2|pattern3' text_files/DonQuijote.txt

Luis Diego Mora Aguilar - 2018147110.
Maria Pia Sancho Zamora - 
Proyecto 1 - Principios de Sistemas Operativos.

grep es un comando unix para terminal el cual nos imprime la linea donde una
expresion regular se encuentra dentro de un archivo de texto.

Sintaxis de uso:
grep 'PATTERN_1\|PATTERN_2\|...\|PATTERN_N' nombreArchivo.extension

En este caso, un ejemplo puede ser 
grep 'pronto' text_files/DonQuijote.txt

Y el output seria 

*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/*
Busca una expresion regular en un texto.
1 = encontrado.
0 = No encontrado
Otro = Error
*/
int regexSearch(char* pPattern, char* pText){
    regex_t reegex;
    regcomp( &reegex, pPattern, 0);
    int result = regexec( &reegex, pText, 0, NULL, 0);
    if(result == 0){
        return 1;
    }
    return 0;
}
int cantidadSecciones;
int analizar(int pIndexSeccion){
    if(pIndexSeccion == cantidadSecciones){
        pthread_exit(NULL);
    }
    //Bloquea el mutex
        //analiza la seccion
    pIndexSeccion++;         //Apunta la siguiente seccion de texto
    // Buscar una nueva seccion
    analizar(pIndexSeccion);analizar(pIndexSeccion);
}

int main(int argc, char* argv[])
{
    /*
    El input puede venir con varios patrones dentro
    ./c_grep.out 'pattern1|pattern2|pattern3' text_files/DonQuijote.txt
    
    Aqui la variable pattern se encarga de extraer cada patron del argumento recibido en consola
    */
    char* pattern = strtok(argv[1], "|");
    while (pattern != NULL){
        printf("Pattern is: %s\n", pattern);
        pattern = strtok(NULL, "|");
    }
    
    //La idea seria que un regcomp() pueda obtener uno de estos patrones para buscarlo con regexec() en algun texto dado.

    
    printf("test1, deberia ser 1 ya que existe: %i\n", regexSearch("Thank you", "Thank your guys"));
    printf("test2, deberia ser 0 ya que no existe: %i\n", regexSearch("Holligan", "Three thousand years"));

    //TODO: Abrir un archivo de texto.
    //TODO: Hacer threads que lean un texto de 8K (8192 bytes) y hagan regexSearch.
    //TODO: Planificar bien las cantidades de threads y la division del archivo entre threads.
    //      Pensar en que cada seccion del archivo tenga un mutex para que solo 1 thread lo tome.
    //      Cada seccion del archivo podemos dividirla en 8K (8192 bytes)
    //TODO: Imprimir cada linea donde se encuentra un regex en el texto.
    //TODO: Medir tiempos y elegir la mejor combinacion de threads. (tabla de Hilos usados y tiempo)

    return 0;
}


/*

*** END OF THE PROJECT GUTENBERG EBOOK DON QUIJOTE ***
Updated editions will replace the previous one—the old editions will be renamed.
Creating the works from print editions not protected by U.S. copyright law means that no one owns a United States copyright in these works, so the Foundation (and you!) can copy and distribute it in the United States without permission and without paying copyright royalties. Special rules, set forth in the General Terms of Use part of this license, apply to copying and distributing Project Gutenberg™ electronic works to protect the PROJECT GUTENBERG™ concept and trademark. Project Gutenberg is a registered trademark, and may not be used if you charge for an eBook, except by following the terms of the trademark license, including paying royalties for use of the Project Gutenberg trademark. If you do not charge anything for copies of this eBook, complying with the trademark license is very easy. You may use this eBook for nearly any purpose such as creation of derivative works, reports, performances and research. Project Gutenberg eBooks may be modified and printed and given away—you may do practically ANYTHING in the United States with eBooks not protected by U.S. copyright law. Redistribution is subject to the trademark license, especially commercial redistribution.
START: FULL LICENSE
THE FULL PROJECT GUTENBERG LICENSE
PLEASE READ THIS BEFORE YOU DISTRIBUTE OR USE THIS WORK


*/

/*
Preguntas para el profe:

Pregunta 1:
    Regex deberia funcionar si el texto contiene el patron pero no sean iguales?
    Ejemplo: Patron: corazon, Texto: corazones
    Resultado del regex: True

    Eso estaria bien?

Pregunta 2:

    El buffer siempre debe tomar 8K?
    Puede tomar menos para resolver el problema de la lectura incompleta de una linea?

Pregunta 3:

    
*/