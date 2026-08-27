/*
@title: Linear Diophantine Equation
@complexity: O(log min(|a|,|b|))
@tags: extended gcd, ax+by=c, integer solutions
@priority: 20
*/
/*
    Solve:
        a*x + b*y = c
    All solutions:
        x = x0 + k*(b/g)
        y = y0 - k*(a/g)
    Returns false if no solution exists.
    Assumes a and b are not both zero.
*/

using ll = long long;

// Returns g = gcd(a,b), together with ax + by = g.
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

bool find_any_solution(ll a, ll b, ll c, ll& x0, ll& y0, ll& g) {
    if (a == 0 && b == 0)
        return false;
    g = gcd(abs(a), abs(b));
    ll x, y;
    extgcd(abs(a), abs(b), x, y);
    if (c % g != 0)
        return false;
    x0 = x * (c / g);
    y0 = y * (c / g);
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

// Shift a solution by k steps.
void shift_solution(ll& x, ll& y,ll a, ll b, ll k) {
    x += k * b;
    y -= k * a;
}

ll floor_div(ll a, ll b) {
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((r > 0) != (b > 0)))
        --q;
    return q;
}

ll ceil_div(ll a, ll b) {
    return -floor_div(-a, b);
}

// Number of solutions: (rx - lx) / abs(b/g) + 1
bool find_solution_range(
    ll a, ll b, ll c,
    ll minx, ll maxx,
    ll miny, ll maxy,
    ll& lx, ll& rx
) {
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return false;
    a /= g;
    b /= g;
    
    ll klo = LLONG_MIN / 4;
    ll khi = LLONG_MAX / 4;
    klo = max(klo,ceil_div(minx - x, b));
    khi = min(khi,floor_div(maxx - x, b));
    klo = max(klo,ceil_div(y - maxy, a));
    khi = min(khi,floor_div(y - miny, a));

    if (klo > khi)
        return false;

    lx = x + klo * b;
    rx = x + khi * b;

    if (lx > rx)
        swap(lx, rx);

    return true;
}