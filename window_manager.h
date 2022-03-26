//
// Created by rkb on 3/23/22.
//

#ifndef MAYBEWM_WINDOWMANAGER_H
#define MAYBEWM_WINDOWMANAGER_H

#include <memory>

#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>

class WindowManager {
public:
    static std::unique_ptr<WindowManager> Create();

    explicit WindowManager(xcb_connection_t* connection);
    ~WindowManager();

    void Run();

private:
    xcb_connection_t* connection_;
    xcb_screen_t* screen_;
    xcb_window_t root_;
};


#endif //MAYBEWM_WINDOWMANAGER_H
