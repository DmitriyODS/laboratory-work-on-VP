#ifndef COSMODROME_ACTIONTYPES_H
#define COSMODROME_ACTIONTYPES_H


enum class ActionTypes {
    // TODO: Здесь описываем типы всех действий в нашем приложении
    //  а точнее, виды всех событий, которые могут произойти в нашей программе
    //  эти события будет обрабатывать метод reducer

    CHANGE_APP_NAME,
    CLEAR_CURRENT_USER,
    SET_CURRENT_USER,
    ADD_NEW_USER,
    EDIT_USER,
    DELETE_USER,
    ADD_NEW_SPACESHIP,
    EDIT_SPACESHIP,
    DELETE_SPACESHIP,
    ADD_NEW_LAUNCH_TASK,
    EDIT_LAUNCH_TASK,
    DELETE_LAUNCH_TASK,
    SET_INTENT_NEXT_SCREEN,
    SET_INTENT_DATA,
    CLEAR_INTENT_NEXT_SCREEN,
    CLEAR_INTENT_DATA,
    PUSH_STACK_SCREEN,
    CLEAR_PUSH_STACK_SCREEN
};

#endif //COSMODROME_ACTIONTYPES_H
