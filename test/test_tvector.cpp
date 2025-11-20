#include "tmatrix.h"  // Подключаем заголовочный файл с классом TDynamicVector
#include <gtest.h>    // Подключаем библиотеку Google Test для модульного тестирования


TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));// создание вектора размером 5 не вызывает исключений
}


TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1)); //превышение максимального размера вызывает исключение
}


TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5)); //  отрицательный размер вызывает исключение
}


TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10); 

    ASSERT_NO_THROW(TDynamicVector<int> v1(v)); // копирование проходит без исключений
}


TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;           // Заполняем вектор значениями
    TDynamicVector<int> v1(v); // Создаем копию

    EXPECT_EQ(v, v1); // Проверяем, что векторы равны
}

// скопированный вектор имеет собственную память 
TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    TDynamicVector<int> v1(v);
    v1[0] = 10;              

    // Проверяем, что изменение в копии не повлияло на оригинал
    EXPECT_NE(v[0], v1[0]);
    EXPECT_EQ(v[0], 1);    
    EXPECT_EQ(v1[0], 10);   
}

//  можно получить размер вектора
TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4); 
    EXPECT_EQ(4, v.size());  
}

// можно установить и получить элемент вектора
TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4); 
    v[0] = 4;                

    EXPECT_EQ(4, v[0]); 
}

// Тест: исключение при установке элемента с отрицательным индексом
TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(3); // Создаем вектор размером 3

    ASSERT_ANY_THROW(v.at(-1)); // Проверяем, что обращение к отрицательному индексу вызывает исключение
}

// Тест: исключение при установке элемента с индексом вне границ
TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(3); // Создаем вектор размером 3 (индексы 0-2)

    ASSERT_ANY_THROW(v.at(3)); // Проверяем, что обращение к индексу 3 (равному размеру) вызывает исключение
}

// Тест: можно присвоить вектор самому себе
TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3; // Заполняем вектор значениями

    ASSERT_NO_THROW(v = v); // Проверяем, что самоприсваивание не вызывает исключений
    // Проверяем, что данные не испортились
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

// Тест: можно присвоить векторы одинакового размера
TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3; // Заполняем первый вектор
    TDynamicVector<int> v2(3);
    v2 = v1;   // Присваиваем v1 к v2

    // Проверяем, что данные скопировались корректно
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

// Тест: оператор присваивания изменяет размер вектора
TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(5); // Вектор размером 5
    TDynamicVector<int> v2(3); // Вектор размером 3

    v2 = v1; // Присваиваем большой вектор маленькому

    EXPECT_EQ(v2.size(), 5); // Проверяем, что размер изменился на 5
}

// Тест: можно присвоить векторы разного размера
TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) v1[i] = i + 1; // Заполняем вектор значениями 1-5
    TDynamicVector<int> v2(3); // Вектор меньшего размера
    v2 = v1; // Присваиваем большой вектор маленькому

    EXPECT_EQ(v2.size(), 5); // Проверяем, что размер изменился
    // Проверяем, что все данные скопировались корректно
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(v2[i], i + 1);
    }
}

// Тест: сравнение одинаковых векторов возвращает true
TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    TDynamicVector<int> v2(3); // Создаем идентичный вектор
    v2[0] = 1;
    v2[1] = 2;
    v2[2] = 3;

    EXPECT_TRUE(v1 == v2); // Проверяем, что оператор == возвращает true
}

// Тест: вектор равен самому себе
TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    EXPECT_TRUE(v == v); // Проверяем рефлексивность операции ==
}

// Тест: векторы разного размера не равны
TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(3); // Вектор размером 3
    TDynamicVector<int> v2(5); // Вектор размером 5

    EXPECT_TRUE(v1 != v2); // Проверяем, что оператор != возвращает true
}

// Тест: можно прибавить скаляр к вектору
TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    TDynamicVector<int> result = v + 5; // Прибавляем 5 к каждому элементу

    // Проверяем результат поэлементно
    EXPECT_EQ(result[0], 6); // 1 + 5 = 6
    EXPECT_EQ(result[1], 7); // 2 + 5 = 7
    EXPECT_EQ(result[2], 8); // 3 + 5 = 8
}

// Тест: можно вычесть скаляр из вектора
TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 5;
    v[1] = 6;
    v[2] = 7;
    TDynamicVector<int> result = v - 2; // Вычитаем 2 из каждого элемента

    // Проверяем результат поэлементно
    EXPECT_EQ(result[0], 3); // 5 - 2 = 3
    EXPECT_EQ(result[1], 4); // 6 - 2 = 4
    EXPECT_EQ(result[2], 5); // 7 - 2 = 5
}

// Тест: можно умножить вектор на скаляр
TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    TDynamicVector<int> result = v * 3; // Умножаем каждый элемент на 3

    // Проверяем результат поэлементно
    EXPECT_EQ(result[0], 3); // 1 * 3 = 3
    EXPECT_EQ(result[1], 6); // 2 * 3 = 6
    EXPECT_EQ(result[2], 9); // 3 * 3 = 9
}

// Тест: можно сложить векторы одинакового размера
TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    TDynamicVector<int> v2(3);
    v2[0] = 4;
    v2[1] = 5;
    v2[2] = 6;
    TDynamicVector<int> result = v1 + v2; // Складываем векторы поэлементно

    // Проверяем результат поэлементно
    EXPECT_EQ(result[0], 5); // 1 + 4 = 5
    EXPECT_EQ(result[1], 7); // 2 + 5 = 7
    EXPECT_EQ(result[2], 9); // 3 + 6 = 9
}

// Тест: нельзя сложить векторы разного размера
TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3); // Вектор размером 3
    TDynamicVector<int> v2(5); // Вектор размером 5

    ASSERT_ANY_THROW(v1 + v2); // Проверяем, что сложение вызывает исключение
}

// Тест: можно вычесть векторы одинакового размера
TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 5;
    v1[1] = 7;
    v1[2] = 9;
    TDynamicVector<int> v2(3);
    v2[0] = 1;
    v2[1] = 2;
    v2[2] = 3;
    TDynamicVector<int> result = v1 - v2; // Вычитаем векторы поэлементно

    // Проверяем результат поэлементно
    EXPECT_EQ(result[0], 4); // 5 - 1 = 4
    EXPECT_EQ(result[1], 5); // 7 - 2 = 5
    EXPECT_EQ(result[2], 6); // 9 - 3 = 6
}

// Тест: нельзя вычесть векторы разного размера
TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(3); // Вектор размером 3
    TDynamicVector<int> v2(5); // Вектор размером 5

    ASSERT_ANY_THROW(v1 - v2); // Проверяем, что вычитание вызывает исключение
}

// Тест: можно вычислить скалярное произведение векторов
TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;
    TDynamicVector<int> v2(3);
    v2[0] = 4;
    v2[1] = 5;
    v2[2] = 6;
    int result = v1 * v2; // Вычисляем скалярное произведение

    EXPECT_EQ(result, 32); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
}

// Тест: нельзя вычислить скалярное произведение векторов разного размера
TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2); // Вектор размером 2
    TDynamicVector<int> v2(4); // Вектор размером 4

    ASSERT_ANY_THROW(v1 * v2); // Проверяем, что скалярное умножение вызывает исключение
}