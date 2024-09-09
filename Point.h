#if !defined(__POINT_H__)
#define __POINT_H__

class Point {
public:
    int x;
    int y;

    Point() : x(-1), y(-1) {}
    Point(int x_, int y_) : x(x_), y(y_) {}

    bool operator<(const Point& autre) const {
        return x < autre.x || (x == autre.x && y < autre.y);
    }

    bool operator==(const Point& autre) const {
        return x == autre.x && y == autre.y;
    }
};
#endif