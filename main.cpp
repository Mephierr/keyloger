#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <iostream>

int main() {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    Window root = DefaultRootWindow(display);
    XSelectInput(display, root, KeyPressMask);

    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            char buffer[32];
            KeySym keysym;
            int len = XLookupString(&event.xkey, buffer, sizeof(buffer), &keysym, NULL);
            if (len > 0) {
                buffer[len] = '0'; // Null-terminate the string
                std::cout << "Key Pressed: " << buffer << std::endl;
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}