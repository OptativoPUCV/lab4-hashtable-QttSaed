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
  HashMap * map=(HashMap*)malloc(sizeof(HashMap));
  if(map==NULL)return NULL;
  map->buckets=(Pair**)calloc(capacity,sizeof(Pair*)); 
  if(map->buckets==NULL)return NULL;
  map->size=0; 
  map->capacity=capacity;
  map->current=-1;
  return map;
  
}

void eraseMap(HashMap * map,  char * key) {    
  for (long i = 0; i < map->capacity; i++) {
      Pair *pair = (Pair *)map->buckets[i];
        if (pair != NULL && strcmp(pair->key, key) == 0) {
            pair->key = NULL;
            map->size--;
            return;
        }
  }
}

Pair * searchMap(HashMap * map,  char * key){ 
  long index = hash(key, map->capacity);
  while (map->buckets[index] != NULL){
    Pair *pair =(Pair *)map->buckets[index];
    if(pair->key != NULL && is_equal(pair->key, key) == 0){
      return pair;
    }
    index = (index + 1) % map->capacity;
  }
    return NULL;
}

Pair * firstMap(HashMap * map) {
  for(long i=0;i< map->capacity;i++){
    Pair *pair = (Pair *)map->buckets[i];
    if(pair!=NULL && pair->key !=NULL){
      map->current=i;
      return pair;
    }
  }

    return NULL;
}

Pair * nextMap(HashMap * map) {
  for(long i = map->current+1 ; i < map->capacity ;i++){
    Pair *pair = (Pair *)map->buckets[i];
    if(pair!=NULL && pair->key !=NULL){
      map->current=i;
      return pair;
    }
  }

    return NULL;
}
