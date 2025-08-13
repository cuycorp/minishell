Alright — let’s connect **everything** so your wildcard expansion works for:

* **Normal args**: `ls *.txt` expands into multiple tokens.
* **Quoted args**: `ls "*.txt"` stays as one token.
* **Redirections**:

  * If expansion → 0 matches → keep literal (like bash).
  * If expansion → 1 match → use that filename.
  * If expansion → >1 match → error: `bash: *.txt: ambiguous redirect`.

I’ll split this into **four helpers + main expansion function** so it’s clear.

---

## **1. Wildcard matching helper**

```c
#include <fnmatch.h>

static int match_pattern(const char *pattern, const char *str)
{
    return fnmatch(pattern, str, 0) == 0;
}
```

---

## **2. Directory/basename extractors**

(using the ones I gave you earlier)

```c
char *get_dir_part(const char *path);
char *get_basename_part(const char *path);
```

---

## **3. Wildcard resolver**

Opens the target directory, matches entries, returns a `char **` array of matches (NULL-terminated).

```c
#include <dirent.h>
#include <stdio.h>

char **ft_resolve_wildcard_pattern(const char *pattern)
{
    DIR *dir;
    struct dirent *entry;
    char **matches = NULL;
    size_t count = 0;
    char *dir_part;
    char *base_part;

    dir_part = get_dir_part(pattern);
    base_part = get_basename_part(pattern);
    if (!dir_part || !base_part)
        goto cleanup;

    dir = opendir(dir_part);
    if (!dir)
        goto cleanup;

    while ((entry = readdir(dir)))
    {
        if (match_pattern(base_part, entry->d_name))
        {
            char **tmp = realloc(matches, sizeof(char *) * (count + 2));
            if (!tmp)
                goto cleanup_dir;
            matches = tmp;
            matches[count++] = strdup(entry->d_name);
            matches[count] = NULL;
        }
    }

cleanup_dir:
    closedir(dir);
cleanup:
    free(dir_part);
    free(base_part);
    return matches; // May be NULL if no matches or error
}
```

---

## **4. Replace token with matches**

```c
#include "tokens.h" // Your t_token struct

static void ft_replace_current_token_with_matches(
    t_token **head, t_token *current, char **matches)
{
    t_token *prev = current->prev;
    t_token *next = current->next;
    size_t i = 0;
    t_token *last_inserted = NULL;

    while (matches && matches[i])
    {
        t_token *new_token = ft_create_token(TOKEN_WORD, matches[i]);
        free(matches[i]);
        if (!new_token)
            return;
        if (!prev) // Inserting at head
        {
            new_token->next = *head;
            if (*head)
                (*head)->prev = new_token;
            *head = new_token;
        }
        else
        {
            prev->next = new_token;
            new_token->prev = prev;
        }
        prev = new_token;
        last_inserted = new_token;
        i++;
    }
    if (last_inserted)
        last_inserted->next = next;
    if (next)
        next->prev = last_inserted;

    ft_free_token(current); // remove original
}
```

---

## **5. Main expansion loop**

```c
#include <string.h>

void ft_expand_wildcard_in_token_list(t_token **head)
{
    t_token *current = *head;

    while (current)
    {
        // Only expand unquoted words
        if (current->type == TOKEN_WORD)
        {
            if (strpbrk(current->value, "*?["))
            {
                char **matches = ft_resolve_wildcard_pattern(current->value);
                if (matches && matches[0])
                {
                    ft_replace_current_token_with_matches(head, current, matches);
                    free(matches);
                    // Restart from head because list changed
                    current = *head;
                    continue;
                }
                else
                {
                    // No match: keep literal (bash behavior)
                    free(matches);
                }
            }
        }
        current = current->next;
    }
}
```

---

## **6. Special case: Redirections**

Before replacing a token in a redirection position (TOKEN\_REDIR\_IN, TOKEN\_REDIR\_OUT, etc.):

```c
if (redir_target && strpbrk(redir_target->value, "*?["))
{
    char **matches = ft_resolve_wildcard_pattern(redir_target->value);
    if (!matches || !matches[0])
    {
        // No match → keep as literal
    }
    else if (matches[1])
    {
        // More than 1 match → ambiguous
        fprintf(stderr, "bash: %s: ambiguous redirect\n", redir_target->value);
        g_exit_status = 1;
        // handle error cleanup
    }
    else
    {
        // Exactly 1 match → replace value
        free(redir_target->value);
        redir_target->value = matches[0];
        free(matches);
    }
}
```

---

## **7. Test cases**

| Command                      | Behavior                           |
| ---------------------------- | ---------------------------------- |
| `ls *.txt`                   | expands to all `.txt` files in cwd |
| `ls "*.txt"`                 | stays as literal `"*.txt"`         |
| `cat file?.c`                | expands if matches exist           |
| `cat no_match_*.c`           | keeps literal                      |
| `> *.txt` (multiple matches) | `bash: *.txt: ambiguous redirect`  |
| `< *.txt` (1 match)          | uses that match                    |
| `cat src/*.c`                | expands relative to `src` dir      |

---

This setup **fully connects wildcard expansion with redirection ambiguity detection** and keeps quoted tokens untouched.
If you want, I can merge **wildcard + variable expansion** so they run in the same token pass for efficiency.

Do you want me to merge them so expansion happens in a single traversal? That’s how bash does it.
