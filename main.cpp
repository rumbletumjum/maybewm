#include <memory>

#include <boost/log/trivial.hpp>

#include "window_manager.h"

int main() {
    BOOST_LOG_TRIVIAL(info) << "test";

    std::unique_ptr<WindowManager> wm = WindowManager::Create();
    if (!wm) {
        BOOST_LOG_TRIVIAL(error) << "error initializing window manager";
        return EXIT_FAILURE;
    }

    wm->Run();

    return EXIT_SUCCESS;
}
