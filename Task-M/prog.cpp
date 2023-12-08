#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class DS
{
private:
    vector<int> sortedValues;

public:
    DS(vector<int>& inval);
    ~DS();
    bool compare(int k, int x);
};

DS::DS(vector<int>& inval)
{
    sortedValues = inval;
    sort(sortedValues.begin(), sortedValues.end());
};

DS::~DS()
{
};

bool DS::compare(int k, int x)
{
    auto it = lower_bound(sortedValues.begin(), sortedValues.end(), x);
    return (sortedValues.end() - it) >= k;
}

int main()
{
    int z;
    cin >> z;
    while (z)
    {
        int n, q;
        vector<int> val;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            val.push_back(x);
        }
        DS ds = DS(val);
        while (q)
        {
            int x, k;
            cin >> k >> x;
            if (ds.compare(k, x))
                cout << "YES\n";
            else
                cout << "NO\n";
            q--;
        }
        z--;
    }

    return 0;
}
