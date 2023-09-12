#include <stdio.h>
#include <stdlib.h>
#include "lib_a/array_foo.h"
#include "lib_m/matrix_foo.h"
#include <windows.h>

#define true 1

//функция очистки памяти
void cleanup(int** matrix, HMODULE dll)
{
    for(int i = 0; i < 6; i++)
        free(matrix[i]);
    free(matrix);

    FreeLibrary(dll);
}


int main(int argc, char* argv[])
{   
    int menu = 0;
    HMODULE dll;

    system("cls");
    printf("Меню тестирования. \n 1. Тестирование библиотеки для массива.\n 2. Тестирование библиотеки для матрицы.\n\n-> ");

    scanf("%d", &menu);
    system("cls");
    
    if(menu == 1)
    {   
        //инициализируем массив
        int array_size = 67, array[array_size];
        //объявляем указатели на функции
        void (*func1)(int*, int), (*func2)(int*, int);

        //загружаем библиотеку
        dll = LoadLibrary("lib_a/lib1.dll"); 
        if(dll == 0){
            dll = LoadLibrary("third_pracice/lib_a/lib1.dll"); 
        } 

        //Получаем из библиотеки адресс функции заполнения рандомными числами
        func1 = (void*)GetProcAddress(dll, "arr_fill_random");
        if(func1 == NULL){
            FreeLibrary(dll);
            return 1;
        }
        //Получаем из библиотеки адресс функцию вывода
        func2 = (void*)GetProcAddress(dll, "arr_output");
        if(func2 == NULL){
            FreeLibrary(dll);
            return 2;
        }

        //вызываем функцию
        func1(array, array_size);
        printf("\nМассив до изменений:\n");
        func2(array, array_size);

        //вПолучаем из библиотеки адресс функции возведения отрц. числе в ^2
        func1 = (void*)GetProcAddress(dll, "arr_negative_square");
        if(func1 == NULL){
            FreeLibrary(dll);
            return 3;
        }

        //вызываем функцию
        func1(array, array_size);
        printf("\n\nМассив после изменений:\n");
        func2(array, array_size);
        
        FreeLibrary(dll);
        printf("\n\n");         
        return 0;
    }
    else if(menu == 2)
    {
        //выделяем память под матрицу
        int matrix_width = 7, matrix_height = 6;
        int** matrix = (int**)calloc(sizeof(int*), matrix_height);
        for(int i = 0; i < matrix_height; i++){
            matrix[i] = (int*)calloc(sizeof(int), matrix_width);
        }
        //объявляем указатели на функции
        void (*func1)(int**, int, int), (*func2)(int**, int, int);

        dll = LoadLibrary("lib_m/lib2.dll");
        if(dll == 0){
            dll = LoadLibrary("third_pracice/lib_m/lib2.dll"); 
        } 

        //Получаем из библиотеки адресс функции заполнения рандомными числами
        func1 = (void*)GetProcAddress(dll, "matrix_fill_random");
        if(func1 == NULL){
            cleanup(matrix, dll);
            return -1;
        }

        //Получаем из библиотеки адресс функцию вывода
        func2 = (void*)GetProcAddress(dll, "matrix_output");
        if(func2 == NULL){
            cleanup(matrix, dll);
            return -2;
        }  
      
        //вызываем функцию
        func1(matrix, 7, 6);
        printf("\nМатрица до изменений:\n");
        func2(matrix, 7, 6);

        //Получаем из библиотеки адресс функции возведения отрц. числе в ^2
        func1 = (void*)GetProcAddress(dll, "matrix_negative_square");
        if(func1 == NULL){
            cleanup(matrix, dll);
            return -3;
        }

        //вызываем функцию
        func1(matrix, 7, 6);
        printf("\n\nМатрица после изменений:\n");
        func2(matrix, 7, 6);
        
        //очищаем память
        cleanup(matrix, dll);
        printf("\n\n");
        return 0;
    }
    else
    {
        printf("Команда не распознана. Досвидания.");
        return 0;
    }
}