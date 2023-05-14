#include "event.h"

std::ostream & operator<<(std::ostream & out, const Event &self)
{
    return self.print(out);
}
