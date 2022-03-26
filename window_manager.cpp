//
// Created by rkb on 3/23/22.
//
#include <boost/log/trivial.hpp>
#include <xcb/xcb_event.h>

#include "events.h"
#include "window_manager.h"

std::unique_ptr<WindowManager> WindowManager::Create()
{
    xcb_connection_t* connection = xcb_connect(nullptr, nullptr);
    if (connection == nullptr || xcb_connection_has_error(connection)) {
        return nullptr;
    }

    return std::make_unique<WindowManager>(connection);
}

WindowManager::~WindowManager()
{
    xcb_disconnect(connection_);
}

WindowManager::WindowManager(xcb_connection_t* connection)
    : connection_(connection),
      screen_(xcb_aux_get_screen(connection, 0)),
      root_(screen_->root)
{
}

void WindowManager::Run()
{
    BOOST_LOG_TRIVIAL(info) << "Root window: " << root_;
    const uint32_t event_mask = XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT
                                | XCB_EVENT_MASK_STRUCTURE_NOTIFY
                                | XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY
                                | XCB_EVENT_MASK_PROPERTY_CHANGE;

    xcb_change_window_attributes(connection_, root_, XCB_CW_EVENT_MASK, &event_mask);

    xcb_flush(connection_);
    BOOST_LOG_TRIVIAL(info) << "Starting event loop";

    xcb_generic_event_t *ev;
    while ((ev = xcb_wait_for_event(connection_))) {
        BOOST_LOG_TRIVIAL(info) << evnames[ev->response_type];

        switch (XCB_EVENT_RESPONSE_TYPE(ev)) {
            case XCB_MAP_REQUEST: {
                auto e = (xcb_map_request_event_t *)ev;
                BOOST_LOG_TRIVIAL(info) << "MapRequest: " << e->window;
                xcb_map_window(connection_, e->window);
                xcb_flush(connection_);
                break;
            }
            case XCB_CONFIGURE_NOTIFY: {
                auto e = (xcb_configure_notify_event_t*)ev;
                BOOST_LOG_TRIVIAL(info) << "ConfigureNotify: " << e->window;
                break;
            }
            case XCB_CONFIGURE_REQUEST: {
                auto e = (xcb_configure_request_event_t*)ev;
                BOOST_LOG_TRIVIAL(info) << "ConfigureRequest: " << e->window;
                break;
            }
        }
    }
}
