#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

template <typename T = double>
class Point
{
public:
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    Point(const Point<T> &obj);
    Point<T> &operator=(const Point<T> &obj);
    Point<T> operator+(const Point<T> &a);
    Point<T> operator-(const Point<T> &a);
    Point<T> &operator+=(const Point<T> &a);
    Point<T> &operator-=(const Point<T> &a);
    bool operator<(const Point<T> &p) const;

    T getX();
    T getY();
    void setX(T _x);
    void setY(T _y);
    void set(T _x, T _y);
    /**
     * @return the distance from point (0,0).
     */
    T distance();

    template <typename Q>
    friend ostream &operator<<(ostream &output, const Point<Q> &p);

protected:
    T x;
    T y;
};

template <typename T>
Point<T>::Point(const Point<T> &obj)
{
    if (this != &obj)
    {
        x = obj.x;
        y = obj.y;
    }
}

template <typename T>
Point<T> &Point<T>::operator=(const Point<T> &obj)
{
    if (this == &obj)
    {
        x = obj.x;
        y = obj.y;
    }
    return *this;
};

template <typename T>
Point<T> Point<T>::operator+(const Point<T> &a)
{
    return Point<T>(x + a.x, y + a.y);
}

template <typename T>
Point<T> Point<T>::operator-(const Point<T> &a)
{
    return Point<T>(x - a.x, y - a.y);
}

template <typename T>
Point<T> &Point<T>::operator+=(const Point<T> &a)
{
    this->x += a.x;
    this->y += a.y;
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator-=(const Point<T> &a)
{
    this->x -= a.x;
    this->y -= a.y;
    return *this;
}

template <typename T>
bool Point<T>::operator<(const Point<T> &p) const
{
    if (this->x == p.x)
    {
        return this->y < p.y;
    }
    else
    {
        return this->x < p.x;
    }
}

template <typename T>
T Point<T>::getX()
{
    return this->x;
}

template <typename T>
T Point<T>::getY()
{
    return this->y;
}

template <typename T>
void Point<T>::setX(T _x)
{
    this->x = _x;
}

template <typename T>
void Point<T>::setY(T _y)
{
    this->y = _y;
}

template <typename T>
void Point<T>::set(T _x, T _y)
{
    this->x = _x;
    this->y = _y;
}

/**
 * @return the distance from point (0,0).
 */
template <typename T>
T Point<T>::distance()
{
    return sqrt(x * x + y * y);
}

template <typename Q>
std::ostream &operator<<(std::ostream &output, const Point<Q> &p)
{
    output << "(" << p.x << "," << p.y << ")" << endl;
    return output;
}

#endif