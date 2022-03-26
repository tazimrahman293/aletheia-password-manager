//
// Created by jeremy on 2022-03-25.
//

#ifndef PROJECT_CONTEXTMANAGER_H
#define PROJECT_CONTEXTMANAGER_H


enum Context {
    Welcome,  // Initial menu (not authenticated)
    Register,  // Registration menu
    Login,  // Login menu
    Main,  // Main menu after successful login
};


class ContextManager {

    Context context;

public:

    bool authenticated;

    ContextManager() : context(Welcome), authenticated(false) { }

    [[nodiscard]] Context GetContext() const { return context; }
    bool SetContext(Context ctx);

};


#endif //PROJECT_CONTEXTMANAGER_H
