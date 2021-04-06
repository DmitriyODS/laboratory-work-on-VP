#include "LaunchTask.h"

// инитим начальное значение id для пользователей
unsigned int LaunchTask::current_id_launch_task{};

std::ostream &operator<<(std::ostream &out, const tm &dateTime) {
    out << std::put_time(&dateTime, "%c");
    return out;
}
