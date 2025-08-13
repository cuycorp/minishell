Yes — those two helpers are pretty simple to implement.
They basically split a path into the **directory part** and the **basename part**, similar to what POSIX `dirname()` and `basename()` do, but without modifying the original string.

Here’s one possible safe implementation:

```c
#include <stdlib.h>
#include <string.h>

/**
 * Extracts the directory part of a path (everything before the last '/').
 * If no '/' is found, returns ".".
 * The returned string must be freed by the caller.
 */
char *get_dir_part(const char *path)
{
    char *last_slash;
    size_t len;
    char *dir;

    if (!path || !*path)
        return strdup(".");
    last_slash = strrchr(path, '/');
    if (!last_slash)
        return strdup("."); // No directory part, current directory

    // Handle case where path ends with '/', e.g. "/usr/local/"
    while (last_slash > path && *last_slash == '/')
        last_slash--;

    len = (size_t)(last_slash - path + 1);
    dir = malloc(len + 1);
    if (!dir)
        return NULL;
    memcpy(dir, path, len);
    dir[len] = '\0';
    return dir;
}

/**
 * Extracts the basename part of a path (everything after the last '/').
 * If the path ends with '/', skips trailing slashes.
 * The returned string must be freed by the caller.
 */
char *get_basename_part(const char *path)
{
    const char *last_slash;
    const char *basename;

    if (!path || !*path)
        return strdup("");

    // Skip trailing slashes
    size_t len = strlen(path);
    while (len > 1 && path[len - 1] == '/')
        len--;

    // Find last slash before the basename
    last_slash = memrchr(path, '/', len); // GNU extension; if not available, see below
    if (!last_slash)
        basename = path;
    else
        basename = last_slash + 1;

    return strndup(basename, len - (basename - path));
}
```

---

### If `memrchr()` is not available

Some systems (like macOS) don’t have `memrchr()`. You can replace that part in `get_basename_part()` with:

```c
last_slash = NULL;
for (size_t i = len; i > 0; i--)
{
    if (path[i - 1] == '/')
    {
        last_slash = path + i - 1;
        break;
    }
}
```

---

### Examples

```c
printf("[%s] [%s]\n", get_dir_part("/usr/local/bin/gcc"), get_basename_part("/usr/local/bin/gcc"));
// Output: [/usr/local/bin] [gcc]

printf("[%s] [%s]\n", get_dir_part("file.txt"), get_basename_part("file.txt"));
// Output: [.] [file.txt]

printf("[%s] [%s]\n", get_dir_part("/tmp/"), get_basename_part("/tmp/"));
// Output: [/] [tmp]
```

---

If you want, I can also give you a **wildcard-aware version** where `get_dir_part()` returns `"."` when the wildcard is not in a path and `get_basename_part()` keeps the wildcard pattern intact for matching. That’s usually handy for your `ft_resolve_wildcard_pattern()` workflow.
Do you want me to adapt it for that?
