#include "../includ/GameHandler.hpp"
#include "../includ/Snake.hpp"

/**
 * @brief Перемещение змеи.
 */
void Snake::Move()
{
    if (move == Position(0, 0))
        return;
    item *tmp;
    for (tmp = first; tmp->next; tmp = tmp->next)
        tmp->pos = tmp->next->pos;
    last->pos += move;
    ((FieldHandler)*the_master).HandleOutOfField(this);
}

/**
 * @brief Изменение направления движения змеи.
 * @param mv Новое направление движения.
 */
void Snake::ChangeDirection(MoveVector *mv)
{
    if (*mv == move || *mv == MoveVector(0, 0))
        return;
    move = *mv;
}

/**
 * @brief Съедение еды.
 * @param food Еда.
 */
void Snake::Eat(Food *food)
{
    item *tmp = new item(first->pos);
    tmp->pos -= move;
    tmp->next = first;
    first = tmp;
    len++;
}
