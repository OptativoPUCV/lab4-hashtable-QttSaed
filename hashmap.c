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
  if(map->size==map->capacity){
    enlarge(map);
  }
  long posicion=hash(key,map->capacity);
  while(map->buckets[posicion]!=NULL){
    posicion++;
    posicion=posicion%map->capacity;  
  }
  map->buckets[posicion]=createPair(key,value);
  map->size++;
  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** buckets = map->buckets;
    long capacity = map->capacity;
    map->capacity = capacity * 2;
    map->size = 0;
    map->current = -1;
    map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
    for (long i = 0; i < capacity; i++){
      if(buckets[i]!=NULL){
        insertMap(map,buckets[i]->key,buckets[i]->value);
        
      }
    }
    free(buckets);
  

}


HashMap * createMap(long capacity) {
  
    return NULL;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
