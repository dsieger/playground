double square(double x)
{
    return x*x;
}

double twice(double x)
{
    return 2.0*x;
}

#if defined _MSC_VER
size_t getSize()
{
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (size_t)info.WorkingSetSize;
}
#endif
