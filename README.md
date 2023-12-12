Vargrind 报告：
[scyxc4CSLinux Downloadsl$ valgrind --leak-check=full --track-origins=yes ./new==93436== Memcheck，a memory error detector==934360==Copyright (C) 2002-2017，and GNU GPL'd，by Julian Seward et al.Using Valgrind-3.15.0 and LibVEX;
rerun with -h for copyright info=934360====934360== Command: ./new==934360=
./new
Invalid distance matrix.==934360====934360== 
HEAP SUMMARY:
=934360==
==934360==
==934360==
==934360==22 (16 direct, 6 indirect) bytes in 1 blocks are definitely lost
in loss record 4 of 4
==934360==at 0x4C29F73: malloc (vg replace malloc.c:309)
==934360==by 0x40159D:addStation (new3.c:233)
=934360=by 0x4017CF:main (new3.c:315)
==934360-=
=934360==LEAK SUMMARY:
=-934360=
=-934360=--934360==
==934360===-934360=
=suppressed: bytes in 0 blocks=934360==Reachable blocks (those to which a pointer was found) are not shown.
-934360==To see them.rerun with: --leak-check=full --show-leak-kinds=all
==934360==
==934360==For lists of detected and suppressed errors, rerun with: -s
==934360==ERROR 
SUMMARY: l errors from 1 contexts (suppressed: 0 from 0)
