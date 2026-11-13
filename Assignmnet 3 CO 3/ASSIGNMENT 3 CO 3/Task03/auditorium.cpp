#include <iostream>
using namespace std;

class Auditorium {
    int rows, seats, booked;
    bool** map;
public:
    Auditorium(int r, int s) : rows(r), seats(s), booked(0), map(nullptr) {
        if (rows <= 0 || seats <= 0) {
            rows = seats = 0;
        } else {
            map = new bool*[rows];
            int made = 0;
            try {
                for (; made < rows; ++made)
                    map[made] = new bool[seats]{};
            } catch (...) {
                while (made > 0) delete[] map[--made];
                delete[] map;
                map = nullptr;
                rows = seats = 0;
                throw;
            }
        }
        cout << "Event created: " << rows << " x " << seats << '\n';
    }

    bool book(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || map[r][s])
            return false;
        map[r][s] = true;
        ++booked;
        return true;
    }

    bool cancel(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || !map[r][s])
            return false;
        map[r][s] = false;
        --booked;
        return true;
    }

    ~Auditorium() {
        if (map) {
            for (int r = 0; r < rows; ++r) delete[] map[r];
            delete[] map;
        }
        cout << "Event closed. Seats booked: " << booked << '\n';
    }
};

int main() {
    Auditorium local(2, 3);
    local.book(0, 1);
    local.book(1, 2);
    local.cancel(0, 1);

    {
        Auditorium blockEvent(1, 2);
        blockEvent.book(0, 0);
    }

    Auditorium* heapEvent = new Auditorium(2, 2);
    heapEvent->book(1, 1);
    delete heapEvent;

    Auditorium zero(0, 5);
}