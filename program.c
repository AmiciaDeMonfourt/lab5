#include <stdio.h>
#include <stdlib.h>
#include "lib_a/array_foo.h"
#include "lib_m/matrix_foo.h"
#include <windows.h>

#define true 1

//�㭪�� ���⪨ �����
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
    printf("���� ���஢����. \n 1. ����஢���� ������⥪� ��� ���ᨢ�.\n 2. ����஢���� ������⥪� ��� ������.\n\n-> ");

    scanf("%d", &menu);
    system("cls");
    
    if(menu == 1)
    {   
        //���樠�����㥬 ���ᨢ
        int array_size = 67, array[array_size];
        //���塞 㪠��⥫� �� �㭪樨
        void (*func1)(int*, int), (*func2)(int*, int);

        //����㦠�� ������⥪�
        dll = LoadLibrary("lib_a/lib1.dll"); 
        if(dll == 0){
            dll = LoadLibrary("third_pracice/lib_a/lib1.dll"); 
        } 

        //����砥� �� ������⥪� ����� �㭪樨 ���������� ࠭����묨 �᫠��
        func1 = (void*)GetProcAddress(dll, "arr_fill_random");
        if(func1 == NULL){
            FreeLibrary(dll);
            return 1;
        }
        //����砥� �� ������⥪� ����� �㭪�� �뢮��
        func2 = (void*)GetProcAddress(dll, "arr_output");
        if(func2 == NULL){
            FreeLibrary(dll);
            return 2;
        }

        //��뢠�� �㭪��
        func1(array, array_size);
        printf("\n���ᨢ �� ���������:\n");
        func2(array, array_size);

        //�����砥� �� ������⥪� ����� �㭪樨 ���������� ����. �᫥ � ^2
        func1 = (void*)GetProcAddress(dll, "arr_negative_square");
        if(func1 == NULL){
            FreeLibrary(dll);
            return 3;
        }

        //��뢠�� �㭪��
        func1(array, array_size);
        printf("\n\n���ᨢ ��᫥ ���������:\n");
        func2(array, array_size);
        
        FreeLibrary(dll);
        printf("\n\n");         
        return 0;
    }
    else if(menu == 2)
    {
        //�뤥�塞 ������ ��� ������
        int matrix_width = 7, matrix_height = 6;
        int** matrix = (int**)calloc(sizeof(int*), matrix_height);
        for(int i = 0; i < matrix_height; i++){
            matrix[i] = (int*)calloc(sizeof(int), matrix_width);
        }
        //���塞 㪠��⥫� �� �㭪樨
        void (*func1)(int**, int, int), (*func2)(int**, int, int);

        dll = LoadLibrary("lib_m/lib2.dll");
        if(dll == 0){
            dll = LoadLibrary("third_pracice/lib_m/lib2.dll"); 
        } 

        //����砥� �� ������⥪� ����� �㭪樨 ���������� ࠭����묨 �᫠��
        func1 = (void*)GetProcAddress(dll, "matrix_fill_random");
        if(func1 == NULL){
            cleanup(matrix, dll);
            return -1;
        }

        //����砥� �� ������⥪� ����� �㭪�� �뢮��
        func2 = (void*)GetProcAddress(dll, "matrix_output");
        if(func2 == NULL){
            cleanup(matrix, dll);
            return -2;
        }  
      
        //��뢠�� �㭪��
        func1(matrix, 7, 6);
        printf("\n����� �� ���������:\n");
        func2(matrix, 7, 6);

        //����砥� �� ������⥪� ����� �㭪樨 ���������� ����. �᫥ � ^2
        func1 = (void*)GetProcAddress(dll, "matrix_negative_square");
        if(func1 == NULL){
            cleanup(matrix, dll);
            return -3;
        }

        //��뢠�� �㭪��
        func1(matrix, 7, 6);
        printf("\n\n����� ��᫥ ���������:\n");
        func2(matrix, 7, 6);
        
        //��頥� ������
        cleanup(matrix, dll);
        printf("\n\n");
        return 0;
    }
    else
    {
        printf("������� �� �ᯮ�����. ��ᢨ�����.");
        return 0;
    }
}