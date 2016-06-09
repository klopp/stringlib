#include "convert.h"

unsigned long asc2ulong(const char *s, unsigned base, int ignore_errors) {
    char *endp;
    unsigned long rc = strtoul(s, &endp, base);
    if(*endp && !ignore_errors) {
        return -1;
    }
    return rc;
}

unsigned long long asc2ullong(const char *s, unsigned base, int ignore_errors) {
    char *endp;
    unsigned long long rc = strtoull(s, &endp, base);
    if(*endp && !ignore_errors) {
        return -1;
    }
    return rc;
}

long asc2long(const char *s, unsigned base, int ignore_errors) {
    char *endp;
    long rc = strtol(s, &endp, base);
    if(*endp && !ignore_errors) {
        return -1;
    }
    return rc;
}

long long asc2llong(const char *s, unsigned base, int ignore_errors) {
    char *endp;
    long long rc = strtoll(s, &endp, base);
    if(*endp && !ignore_errors) {
        return -1;
    }
    return rc;
}

