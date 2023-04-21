#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  long indice = hash(key,map->capacity);

  while(map->buckets[indice] != NULL && map->buckets[indice]->key != NULL){
      indice = (indice +1) % map->capacity;
    }
  map->buckets[indice]=createPair(key,value);
  map->size++;
  map->current = indice;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = malloc(sizeof(HashMap));
  Pair ** buckets = calloc(capacity ,sizeof(Pair));

  mapa->buckets = buckets;
  mapa->size = 0;
  mapa->capacity = capacity;
  mapa->current = -1;
  return mapa;

    
}

void eraseMap(HashMap * map,  char * key) {   
  
  for(long i=0 ; i < map->capacity ; i++) 
    {
      if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
      {
        if(strcmp(key,map->buckets[i]->key)==0)
        {
          map->buckets[i]->key = NULL;
          map->size--;
          break;
        }
      } 
    }


}

Pair * searchMap(HashMap * map,  char * key) 
{   
  long encontrado = 0; 
  for(long i=0 ; i < map->capacity ; i++) 
    {
      if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
        if(strcmp(key,map->buckets[i]->key)==0)
        {
          map->current = i;
          encontrado = 1;
          break;
        }
      }
    }
  if(encontrado)
  {
    return map->buckets[map->current];
  }
    else
  {
    return NULL;
  }

}

Pair * firstMap(HashMap * map) {
  map->current = -1;
  return nextMap(map);
}


Pair * nextMap(HashMap * map) {

  if (map->current == -1)
  {
      return NULL;
  }
  for (long i=map->current +1  ; i <  map->capacity; i++)
    {
      if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }

  map->current = -1;
  return NULL;
}


