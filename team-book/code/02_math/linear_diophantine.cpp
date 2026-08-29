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

ll mygcd(ll a, ll b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

// Returns g = gcd(a,b), any solution x0,y0 to a*x0+b*y0=c.
bool find_any_solution(ll a, ll b, ll c, ll& x0, ll& y0, ll& g) {
    if (a == 0 && b == 0)
        return false;
    g = mygcd(llabs(a), llabs(b));
    if (c % g != 0)
        return false;
    ll x, y;
    extgcd(llabs(a), llabs(b), x, y);
    x0 = x * (c / g);
    y0 = y * (c / g);
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

ll floor_div(ll a, ll b) {
    ll q = a / b, r = a % b;
    if (r != 0 && ((r > 0) != (b > 0))) --q;
    return q;
}

ll ceil_div(ll a, ll b) { return -floor_div(-a, b); }

// Finds the range of x-values (lx..rx) among all solutions of a*x+b*y=c
// with x in [minx,maxx] and y in [miny,maxy].
// Number of such solutions = (rx-lx)/abs(b/g) + 1.
// NOTE: correctly handles negative/zero a or b (unlike the naive
// cp-algorithms-style version, which silently breaks on negative coeffs).
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

    // minx <= x + k*b <= maxx
    if (b > 0) {
        klo = max(klo, ceil_div(minx - x, b));
        khi = min(khi, floor_div(maxx - x, b));
    } else if (b < 0) {
        klo = max(klo, ceil_div(maxx - x, b));
        khi = min(khi, floor_div(minx - x, b));
    } else if (x < minx || x > maxx) {
        return false; // b == 0 (a != 0): x is fixed, must lie in [minx,maxx]
    }

    // miny <= y - k*a <= maxy
    if (a > 0) {
        klo = max(klo, ceil_div(y - maxy, a));
        khi = min(khi, floor_div(y - miny, a));
    } else if (a < 0) {
        klo = max(klo, ceil_div(y - miny, a));
        khi = min(khi, floor_div(y - maxy, a));
    } else if (y < miny || y > maxy) {
        return false; // a == 0 (b != 0): y is fixed, must lie in [miny,maxy]
    }

    if (klo > khi)
        return false;

    lx = x + klo * b;
    rx = x + khi * b;
    if (lx > rx) swap(lx, rx);
    return true;
}