static long long getHash(byte* buffer, size_t size)
{
    static long long const base = 1000000007ll;
    long long hash = 0;
    for (int i = 0; i != size; i++)
    {
        hash *= base;
        hash += buffer[i];
    }

    return hash;
}