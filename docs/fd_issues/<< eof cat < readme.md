<< eof cat < readme.md
> gfjhf
> eof
==189189==
==189189== FILE DESCRIPTORS: 3 open (3 std) at exit.
==189189==
==189189== HEAP SUMMARY:
==189189==     in use at exit: 208,222 bytes in 225 blocks
==189189==   total heap usage: 872 allocs, 647 frees, 241,474 bytes allocated
==189189==
==189189== LEAK SUMMARY:
==189189==    definitely lost: 0 bytes in 0 blocks
==189189==    indirectly lost: 0 bytes in 0 blocks
==189189==      possibly lost: 0 bytes in 0 blocks
==189189==    still reachable: 0 bytes in 0 blocks
==189189==         suppressed: 208,222 bytes in 225 blocks
==189189==
==189189== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
--189189--
--189189-- used_suppression:     62 ignore_readline_leaks readline.supp:4 suppressed: 204,147 bytes in 221 blocks
--189189-- used_suppression:      4 ignore_history_leaks readline.supp:11 suppressed: 4,075 bytes in 4 blocks
==189189==
==189189== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==189190== Memcheck, a memory error detector
==189190== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==189190== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==189190== Command: /usr/bin/cat
==189190==
# Minishell


## excel
https://docs.google.com/spreadsheets/d/1Hmm0iZH9rjNX2PAvrIKSHf8TSN89Nc-2WByL6XfGi6U/edit?gid=0#gid=0
==189190==
==189190== FILE DESCRIPTORS: 1 open (0 std) at exit.
==189190== Open file descriptor 3:
==189190==    <inherited from parent>
==189190==
==189190==
==189190== HEAP SUMMARY:
==189190==     in use at exit: 0 bytes in 0 blocks
==189190==   total heap usage: 31 allocs, 31 frees, 139,232 bytes allocated
==189190==
==189190== All heap blocks were freed -- no leaks are possible
==189190==
==189190== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
exit code = 0
