#ifndef FIELD_HPP_SENTRY
#define FIELD_HPP_SENTRY

class FieldHandler;
class GameHandler;

/**
 * @brief Класс, представляющий игровое поле.
 */
class Field
{
    friend class FieldHandler;
    friend class GameHandler;

private:
    /**
     * @brief Ширина поля.
     */
    int size_x;
    /**
     * @brief Высота поля.
     */
    int size_y;
    /**
     * @brief Полная длина поля.
     */
    int full_len;
    /**
     * @brief Массив символов, представляющий поле.
     */
    char *field;

public:
    /**
     * @brief Конструктор класса Field.
     * @param _size_x Ширина поля.
     * @param _size_y Высота поля.
     */
    Field(int _size_x, int _size_y);
    /**
     * @brief Деструктор класса Field.
     */
    ~Field();

    /**
     * @brief Получение полной длины поля.
     * @return Полная длина поля.
     */
    int GetFullLen() { return full_len; }
    /**
     * @brief Получение массива символов, представляющего поле.
     * @return Массив символов, представляющий поле.
     */
    const char *GetField() { return field; }
    /**
     * @brief Получение ширины поля.
     * @return Ширина поля.
     */
    int GetSizeX() {
        if (size_x < 0) {
            return 0;
        }
        return size_x;
    }
    /**
     * @brief Получение высоты поля.
     * @return Высота поля.
     */
    int GetSizeY() {
        if (size_y < 0) {
            return 0;
        }
        return size_y;
    }
};

#endif
