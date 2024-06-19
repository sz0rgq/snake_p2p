#include "../includ/Food.hpp"
#include "../includ/List.hpp"

/**
 * @brief Специализированная реализация функции Remove для List<Food>.
 * @param cursor Указывает на элемент, который нужно удалить.
 */
template <>
void List<Food>::Remove(ListCursor<Food> *cursor)
{
    item *tmp = (*cursor->itm)->next;
    delete (*cursor->itm)->val;
    delete (*cursor->itm);
    (*cursor->itm) = tmp;
}