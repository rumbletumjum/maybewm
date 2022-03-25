//
// Created by rkb on 3/23/22.
//

#include "window_manager.h"

std::unique_ptr<WindowManager> WindowManager::Create()
{
    xcb_connection_t *connection = xcb_connect(nullptr, nullptr);
    return std::make_unique<WindowManager>(connection);
}

WindowManager::WindowManager(xcb_connection_t* connection)
    : connection_(connection),
      screen_(xcb_aux_get_screen(connection, 0))
{
}

