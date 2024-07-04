#ifndef CORE_H
#define CORE_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raylib.h"

typedef struct {
	float index[3][3];
} Matrix3x3;

typedef struct {
	float index[3];
} Matrix3x1;

typedef struct {
    void* array;         //Array
    size_t count;       //Länge
    size_t capacity;    //Kapazität
    size_t size;      //Größe des Elements
} List;

typedef struct {
    char** array;         //Array of Strings
    size_t count;       //Länge
    size_t capacity;    //Kapazität
} ListStr;

typedef struct {
    float** array;      //Array of Strings
    size_t rows;     //Anzahl Zeilen
    size_t cols;     //Anzahl Spalten
} ListFloat2d;

typedef struct node_t {
    void* data;
    struct node_t* next;
} Node;

typedef struct linkedlist_t {
    Node* head;
    Node* tail;
    size_t size;
} LinkedList;

int random_num(int range_start, int range_end);
float limit_num(float number, float limit);
float constrain_num(float value, float min, float max); // limits value between min and max
float map_num(float n, float range_old, float range_new); // scales value n to a new range

List list_create(size_t capacity, size_t size);
void list_append(List* l, void* val);
void* list_at(List* l, int index);
void list_free(List* l);
void list_reduce(List* l);
ListStr lists_create(size_t capacity);
void lists_append(ListStr* l, char val[]);
void lists_free(ListStr* l);
void lists_reduce(ListStr* l);
ListStr split(char string[], const char delimiter);
ListFloat2d listf2d_create(size_t rows, size_t cols, float val);
void listf2d_free(ListFloat2d* l);

void* arr_create(size_t capacity, size_t elemsize);
size_t arr_len(void* arr);
size_t arr_cap(void* arr);
void arr_append(void* ref_arr, void* val);
void arr_pop(void* ref_arr, size_t idx);
void arr_reduce(void* ref_arr);
void arr_free(void* ref_arr);
#define dynarr_create(capacity, datatype) arr_create(capacity, sizeof(datatype))
#define dynarr_len(arr) arr_len(arr)
#define dynarr_cap(arr) arr_cap(arr)
#define dynarr_append(arr, val) arr_append(&arr, &val)
#define dynarr_pop(arr, idx) arr_pop(&arr, idx)
#define dynarr_reduce(arr) arr_reduce(&arr)
#define dynarr_free(arr) arr_free(&arr)


void llist_push(LinkedList* list, void* data, size_t datasize);
void llist_pop(LinkedList* list);

Vector2 vec2_scale(Vector2 v, float n);
Vector2 vec2_div(Vector2 v, float n);
Vector2 vec2_add(Vector2 v, Vector2 v_add);
Vector2 vec2_sub(Vector2 v, Vector2 v_sub);
Vector2 vec2_norm(Vector2 v);
Vector2 vec2_limit(Vector2 v, float max);
Vector2 vec2_setMag(Vector2 v, float magnitude);
float vec2_dot(Vector2 v1, Vector2 v2);
float vec2_cross(Vector2 v1, Vector2 v2);
Vector2 vec2_perp(Vector2 v);
float vec2_mag(Vector2 v);
float vec2_magsq(Vector2 v);
float vec2_dist(Vector2 v1, Vector2 v2);
Vector2 vec2_rotate(Vector2 v, Vector2 base, float n);
float vec2_heading(Vector2 v);
float vec2_angle(Vector2 v1, Vector2 v2);
float vec2_minDist(Vector2 p, Vector2 start_a, Vector2 end_a);


#endif