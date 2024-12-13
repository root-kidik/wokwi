#define ETL_NO_STL 1
#include <etl/hash.h>
#undef ETL_NO_STL

static inline const Vector2i kUp{0, -1};
static inline const Vector2i kDown{0, 1};
static inline const Vector2i kLeft{-1, 0};
static inline const Vector2i kRight{1, 0};

template<typename T>
constexpr Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;

    if (lhs.x != 0)
    {
        if (lhs.x > 0)
            lhs.x %= 8;
        else
            lhs.x = 8 + lhs.x; 
    }

    if (lhs.y != 0)
    {
        if (lhs.y > 0)
            lhs.y %= 8;
        else
            lhs.y = 8 + lhs.y; 
    }

    return lhs;
}

template<typename T>
constexpr Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    auto tmp{lhs};

    tmp.x -= rhs.x;
    tmp.y -= rhs.y;

    return tmp;
}

template<typename T>
constexpr bool operator==(const Vector2<T>& rhs, const Vector2<T>& lhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T>
constexpr bool operator!=(const Vector2<T>& rhs, const Vector2<T>& lhs)
{
    return !(lhs == rhs);
}

template <>
template <typename T>
struct etl::hash<Vector2<T>>
{
    T operator()(const Vector2<T>& vec) const
    {
        return etl::hash<T>()(vec.x) ^ (etl::hash<T>()(vec.y) << 1);
    }
};