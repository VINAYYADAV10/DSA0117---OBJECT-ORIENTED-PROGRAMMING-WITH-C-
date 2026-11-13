#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Time {
    int seconds;
public:
    explicit Time(int s = 0) : seconds(s) {
        if (s < 0) throw invalid_argument("negative time");
    }

    Time& operator++() {
        ++seconds;
        return *this;
    }

    Time operator++(int) {
        Time old = *this;
        ++seconds;
        return old;
    }

    bool operator==(const Time& t) const { return seconds == t.seconds; }
    bool operator<(const Time& t) const { return seconds < t.seconds; }

    friend ostream& operator<<(ostream& os, const Time& t) {
        int h = t.seconds / 3600;
        int m = (t.seconds / 60) % 60;
        int s = t.seconds % 60;
        return os << h << ':' << (m < 10 ? "0" : "") << m
                  << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    vector<string> tracks;
public:
    Playlist(initializer_list<string> x) : tracks(x) {}

    string& operator[](int i) {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("track index");
        return tracks[i];
    }

    const string& operator[](int i) const {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw out_of_range("track index");
        return tracks[i];
    }

    int size() const { return static_cast<int>(tracks.size()); }
};

int main() {
    Time t(3598);
    Time a = t++;
    Time b = ++t;
    cout << a << " | " << b << " | " << t << '\n';

    Playlist p{"Song A", "Song B", "Song C"};
    cout << p[0] << " / " << p[2] << '\n';

    try {
        cout << p[p.size()] << '\n';
    } catch (const out_of_range& e) {
        cout << "Error: " << e.what() << '\n';
    }
}