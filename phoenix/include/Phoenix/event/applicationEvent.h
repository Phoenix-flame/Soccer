#ifndef __APPLICATION__EVENT__
#define __APPLICATION__EVENT__

#include "event.h"
#include <sstream>

namespace Phoenix{
    class WindowResizeEvent : public Event{
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : _width(width), _height(height) {}

        unsigned int GetWidth() const { return _width; }
        unsigned int GetHeight() const { return _height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << _width << ", " << _height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        unsigned int _width, _height;
    };

    class WindowCloseEvent : public Event{
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}

#endif