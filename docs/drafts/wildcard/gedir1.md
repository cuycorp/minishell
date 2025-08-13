Alright — here’s the **wildcard-aware** version of `get_dir_part()` and `get_basename_part()`
that works well for your `ft_resolve_wildcard_pattern()` flow.

The logic changes slightly:

* If the wildcard pattern contains **no `/`**, `get_dir_part()` always returns `"."` and `get_basename_part()` returns the full pattern (so `*.txt` stays as `*.txt`).
* If there’s a `/`, the split works like a normal path, but we keep the wildcard part untouched in the basename.

---

```c
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Checks if the given string contains wildcard chars (*, ?, [).
 */
static bool contains_wildcard(const char *str)
{
    while (*str)
    {
        if (*str == '*' || *str == '?' || *str == '[')
            return true;
        str++;
    }
    return false;
}

/**
 * Extract directory part for wildcard expansion.
 * If the pattern has no '/', returns ".".
 */
char *get_dir_part(const char *path)
{
    const char *last_slash;
    size_t len;
    char *dir;

    if (!path || !*path)
        return strdup(".");

    last_slash = strrchr(path, '/');
    if (!last_slash)
        return strdup("."); // No '/' → current dir

    // Handle case like "/usr/local/"
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
 * Extract basename part for wildcard expansion.
 * If no '/', returns the original pattern.
 */
char *get_basename_part(const char *path)
{
    const char *last_slash;

    if (!path || !*path)
        return strdup("");

    last_slash = strrchr(path, '/');
    if (!last_slash)
        return strdup(path); // No '/' → basename is the whole thing

    return strdup(last_slash + 1);
}
```

---

### Why this is good for wildcard expansion

Example cases:

| Input Pattern            | `get_dir_part()` | `get_basename_part()` |
| ------------------------ | ---------------- | --------------------- |
| `"*.txt"`                | `"."`            | `"*.txt"`             |
| `"src/*.c"`              | `"src"`          | `"*.c"`               |
| `"docs/chap*/intro?.md"` | `"docs"`         | `"chap*/intro?.md"`   |
| `"/var/log/*.log"`       | `"/var/log"`     | `"*.log"`             |
| `"no/wildcard/here.txt"` | `"no/wildcard"`  | `"here.txt"`          |

This way your `ft_resolve_wildcard_pattern()` can:

1. **Get dir part** → open that directory.
2. **Get basename part** → run the match against each entry from that dir.
3. Preserve quoted strings (`TOKEN_WORD_DOUBLE_QUOTED` etc.) by skipping expansion earlier in the loop.

---

If you want, I can now show you **the full chain**:
`ft_expand_wildcard_in_token_list()` → `ft_resolve_wildcard_pattern()` → wildcard matching (fnmatch/globbing) → reinsertion into the token list with ambiguous redirect detection.

That would connect all the dots with your redirection cases too.
Do you want me to?
