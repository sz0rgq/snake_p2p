#ifndef SNAKE_HPP_SENTRY
#define SNAKE_HPP_SENTRY

#include "Field.hpp"
#include "Food.hpp"
#include "MoveAndPosition.hpp"

class GameHandler;
class GameHandlerGemstone;

/**
 * @brief Класс для представления змеи в игре.
 * 
 * Этот класс предназначен для управления змеей, включая ее движение, изменение направления и поедание еды.
 */
class Snake
{
    friend class FieldHandler;
    friend class SnakeHandler;
    friend class GameHandler;

    /**
     * @brief Структура для представления элементов змеи.
     * 
     * Каждый элемент змеи имеет позицию и ссылку на следующий элемент.
     */
    struct item
    {
        Position pos; /**< Позиция элемента змеи. */
        item *next; /**< Ссылка на следующий элемент змеи. */

        /**
         * @brief Конструктор для элемента змеи.
         * 
         * @param _pos Позиция элемента змеи.
         */
        item(const Position &_pos) : pos(_pos), next(0) {}
    };

    item *first; /**< Первый элемент змеи. */
    item *last; /**< Последний элемент змеи (голова). */

    int id; /**< Идентификатор змеи. */
    int len; /**< Длина змеи. */

    MoveVector move; /**< Вектор движения змеи. */
    GameHandlerGemstone *the_master; /**< Указатель на обработчик игры. */

public:
    /**
     * @brief Конструктор для змеи.
     */
    Snake() : first(0), last(0), id(0), len(1), move(0, 0), the_master(0) {}

    /**
     * @brief Конструктор для змеи с указанием позиции и идентификатора.
     * 
     * @param _pos Позиция змеи.
     * @param _id Идентификатор змеи.
     * @param _the_master Указатель на обработчик игры.
     */
    Snake(const Position &_pos, int _id, GameHandlerGemstone *_the_master)
        : first(new item(_pos)), last(first), id(_id), len(1),
          move(0, 0), the_master(_the_master) {}

    /**
     * @brief Деструктор для змеи.
     */
    ~Snake()
    {
        while (first)
        {
            item *tmp = first->next;
            delete first;
            first = tmp;
        }
    }

    /**
     * @brief Получает длину змеи.
     * 
     * @return Длина змеи.
     */
    int GetLen() { return len; }

    /**
     * @brief Двигает змей.
     */
    void Move();

    /**
     * @brief Изменяет направление движения змеи.
     * 
     * @param mv Новый вектор движения.
     */
    void ChangeDirection(MoveVector *mv);

    /**
     * @brief Позволяeет змее поесть еду.
     * 
     * @param food Еда, которую змея ест.
     */
    void Eat(Food *food);
};

#endif
