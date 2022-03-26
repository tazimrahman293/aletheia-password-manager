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

    ContextManager() : context(Welcome) { }

    [[nodiscard]] Context GetContext() const { return context; }
    void SetContext(Context ctx);

};


#endif //PROJECT_CONTEXTMANAGER_H
