/*
 * str.h
 * This file is part of vallaurisoft
 *
 * Copyright (C) 2013 - gnuze
 *
 * vallaurisoft is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * vallaurisoft is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vallaurisoft. If not, see <http://www.gnu.org/licenses/>.
 */

/* if used in c++, compile with -Wno-write-strings to avoid "deprecated" warnings */

#ifndef STR_H
#define  STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_STR 4096
#define MAX_VET 1000
#define MAX 4096



void free_all(char** _morto);
char** crea_vet(void); /*crea un vettore di stringhe prendendo in input il numero di stringhe e le stringhe stesse*/
char* join_str (char* str,char* s);/*mette la seconda stringa in coda alla prima separata da uno spazio*/
char* compatta (char** vet);/*da un vettore di stringhe crea una stringa contenente quelle del vettore separate da uno spazio*/
char* sub_str(char* s,int pos,int lun);

char** split (char* str);
void show(char** v);
void show_str(char* s);
char* cpy_str (char* s); /*riceve la stringa e la restituisce come puntatore a un'altra*/
int len_str(char *s);/*riceve la stringa e restituisce la lunghezza*/
char* input_str();/*riceve una stringa in input*/
void errore(char *s,int n);
int find_str(char* s,char c);

char** crea_vet(void)/*crea un vettore di stringhe prendendo in input il numero di stringhe e le stringhe stesse*/
   {
    int n,i; 
    char** ret;
    printf("Inserire il numero di stringhe contenute nel vettore: ");
    scanf("%d",&n);
    ret=(char**)malloc(sizeof(char*)*(n+1));
    for (i=0;i<n;i++)
       {
        ret[i]=(char*)malloc(sizeof(char)*20);
        printf("Inserire il contenuto della stringa %d: ",i+1);
        fflush(stdin);
        scanf("%s",ret[i]);
       }  
    ret[i]=NULL; 
       
    return ret;
   }
   
char* compatta (char** vet)
   {
    char* ret;    
    int i=0,lun=0;
    while (*(vet+i))
       {
        lun+=len_str(*(vet+i));        
        i++;
       }
    
    ret=(char*)malloc(sizeof(char)*lun);
    for (i=0;vet[i];i++)
       join_str(ret,vet[i]); 
    return ret;
   }

char* join_str (char* str,char* s)
   {
    int j;
    char tmp[MAX];
    for(j=0;str[j];j++);
    if (j!=0)
       {
        tmp[j]=str[j];
        j++;
       }     
     
    for (;*s;s++,j++)
       {
        *(tmp+j)=*s;
       }
    tmp[j]='\0';
	return cpy_str(tmp);
   }
   

void show_str(char* s)
