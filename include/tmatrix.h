// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        // Проверка корректности размера
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    // Конструктор из C-массива
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        copy(arr, arr + sz, pMem);// Копирование данных из массива
    }
    // Конструктор копирования
    TDynamicVector(const TDynamicVector& v) :sz(v.sz), pMem(new T[v.sz])
    {
        copy(v.pMem, v.pMem + v.sz, pMem); // Поэлементное копирование
    }
    // Конструктор перемещения
    TDynamicVector(TDynamicVector&& v) noexcept :sz(v.sz), pMem(v.pMem)
    {
        v.sz = 0;        // Обнуление размера у исходного объекта
        v.pMem = nullptr; // Обнуление указателя у исходного объекта
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    // Копирование
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v) {

            if (sz != v.sz) {
                delete[] pMem;
                sz = v.sz;
                pMem = new T[sz];
            }
            std::copy(v.pMem, v.pMem + sz, pMem);
        }
        return *this;
    }
    // Перемещение(очищаем b)
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
            delete[] pMem;  
            sz = v.sz;     
            pMem = v.pMem;  
            v.sz = 0;      
            v.pMem = nullptr;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация(неконстантный доступ)
    T& operator[](size_t ind)
    {
        // Проверка выхода за границы
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind]; 
    }
    //(константный доступ)
    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }
    // индексация с контролем(неконстантный)
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }
    // индексация с контролем(константный)
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) // Сначала проверяем размеры
            return false;
        // Поэлементное сравнение
        for (size_t i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v); // Используем уже реализованный оператор ==
    }



    // скалярные операции 


    //(вектор + скаляр)
    TDynamicVector operator+(T val)
    {
        TDynamicVector result(sz); // Создаем новый вектор
        // Прибавляем скаляр к каждому элементу
        for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] + val;
        return result;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] - val;
        return result;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] * val;
        return result;
    }

    // векторные операции

    TDynamicVector operator+(const TDynamicVector& v)
    {
        // Проверка совпадения размеров
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal");
        TDynamicVector result(sz);
        // Поэлементное сложение
        for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] + v.pMem[i];
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; i++) result.pMem[i] = pMem[i] - v.pMem[i];
        return result;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw invalid_argument("Vector sizes must be equal");
        T result = T(); // Инициализация результата
        // Вычисление суммы произведений соответствующих элементов
        for (size_t i = 0; i < sz; i++) result += pMem[i] * v.pMem[i];
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        // Чтение каждого элемента из потока
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    //вывод
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using base = TDynamicVector<TDynamicVector<T>>;
    using base::pMem;
    using base::sz;
public:
    TDynamicMatrix(size_t s = 1) : base(s)
    {
        // Проверка корректности размера
        if (sz <= 0 || sz > MAX_MATRIX_SIZE)
            throw out_of_range("Размер матрицы должен быть положительный");
        // Создание каждой строки матрицы (каждый элемент - вектор размера s)
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz); // Инициализация строк
    }

    using base::operator[];
    using base::size;
    using base::at;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false; // Проверка размеров
        // Построчное сравнение
        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m.pMem[i]) return false;
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz); // Создание результирующей матрицы
        // Умножение каждой строки на скаляр
        for (size_t i = 0; i < sz; i++) result[i] = pMem[i] * val;
        return result;
    }

    // матрично-векторные операции

    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        // Проверка совпадения размеров
        if (sz != v.size()) throw invalid_argument("Размеры должны совпадать");
        TDynamicVector<T> result(sz); // Результирующий вектор
        // Умножение каждой строки матрицы на вектор
        for (size_t i = 0; i < sz; i++) {
            result[i] = pMem[i] * v; // Скалярное произведение строки на вектор
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Размеры должны совпадать");
        TDynamicMatrix result(sz);
        // Построчное сложение
        for (size_t i = 0; i < sz; i++) result[i] = pMem[i] + m.pMem[i];
        return result;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Размеры должны совпадать");
        TDynamicMatrix result(sz);
        // Построчное вычитание
        for (size_t i = 0; i < sz; i++) result[i] = pMem[i] - m.pMem[i];
        return result;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Размеры должны совпадать");
        TDynamicMatrix result(sz); // Результирующая матрица
        // Классический алгоритм умножения матриц O(n³)
        for (size_t i = 0; i < sz; i++) {         // По строкам первой матрицы
            for (size_t j = 0; j < sz; j++) {     // По столбцам второй матрицы
                result[i][j] = T(); // Инициализация нулем
                for (size_t k = 0; k < sz; k++) { // Суммирование произведений
                    result[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return result;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        // Построчное чтение матрицы
        for (size_t i = 0; i < m.sz; i++) {
            istr >> m.pMem[i]; // Чтение каждой строки
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        // Построчный вывод матрицы
        for (size_t i = 0; i < m.sz; i++) {
            ostr << m.pMem[i] << '\n'; // Каждая строка на новой линии
        }
        return ostr;
    }
};

#endif