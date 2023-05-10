#include <ctime>

tm *getTimeNow() {
    time_t cTime = time(nullptr);
    return localtime(&cTime);
}

class DisplayCalendar {
public:
    virtual ~DisplayCalendar() noexcept = default;

    [[nodiscard]] virtual shared_ptr<DisplayCalendar> clone() const = 0;

    virtual void display() const = 0;

    virtual void nextPage() = 0;

    virtual void previousPage() = 0;
protected:
    map<size_t, shared_ptr<Event>> mEvents;
    size_t mYear;
};
