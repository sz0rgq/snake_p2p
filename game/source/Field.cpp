#include "../includ/Field.hpp"

/**
 * @brief Конструктор класса Field.
 * @param _size_x Ширина поля.
 * @param _size_y Длина поля.
 */
Field::Field(int _size_x, int _size_y)
    : size_x(_size_x), size_y(_size_y),
      full_len((size_x + 1) * size_y + 1), field(new char[full_len])
{
}

/**
 * @brief Деструктор класса Field.
 * Освобождает динамически выделенную память для поля.
 */
Field::~Field()
{
    delete[] field;
}
