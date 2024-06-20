#ifndef GAMEINIT_HPP_SENTRY
#define GAMEINIT_HPP_SENTRY

/**
 * @class GameInit
 * @brief Класс для инициализации настроек игры.
 */
class GameInit {
    // Константы, используемые в инициализации игры
    enum {
        max_argc = 11,           ///< Максимальное количество аргументов командной строки

        std_port = 8808,         ///< Стандартный порт сервера

        std_width = 100,         ///< Стандартная ширина игрового поля
        std_height = 40,         ///< Стандартная высота игрового поля
        std_food_count = 15      ///< Стандартное количество еды на игровом поле
    };
    
    int argc;                   ///< Количество аргументов командной строки
    const char **argv;          ///< Массив аргументов командной строки

public:
    /**
     * @brief Конструктор класса GameInit.
     * @param _argc Количество аргументов командной строки.
     * @param _argv Массив аргументов командной строки.
     */
    GameInit(int _argc, const char **_argv) : argc(_argc), argv(_argv) {}

    /**
     * @brief Деструктор класса GameInit.
     */
    ~GameInit() {}

    /**
     * @brief Метод для старта инициализации игры.
     * @return Код завершения: 0 - успешное завершение, 1 - ошибка.
     */
    int Start();

private:
    /**
     * @brief Проверяет, является ли аргумент одним из допустимых.
     * @param argv Массив допустимых аргументов.
     * @param arg Проверяемый аргумент.
     * @param argc Количество допустимых аргументов.
     * @param matched_argv_idx Указатель для хранения индекса совпавшего аргумента.
     * @return true, если аргумент найден, false в противном случае.
     */
    bool IsOneOfArgv(const char *argv[6], const char *arg, 
                     int argc, int *matched_argv_idx);

    /**
     * @brief Обрабатывает аргументы командной строки.
     * @param argv_idx Индекс текущего обрабатываемого аргумента.
     * @param matched_argv Индекс совпавшего аргумента.
     * @param num_args Массив для хранения значений числовых аргументов.
     * @param ip Указатель для хранения значения IP адреса.
     * @return true, если аргумент "help" был найден и обработка завершена, false в противном случае.
     */
    bool HandleArgv(int argv_idx, int matched_argv, 
                    int *num_args, const char **ip);

    /**
     * @brief Выводит информацию о доступных аргументах командной строки.
     */
    void WriteHelp();
};

#endif
