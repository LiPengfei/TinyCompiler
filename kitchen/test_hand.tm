* This program inputs an interger, computes
* its factorial if it is positive,
* and prints the result

0: IN 0,0,0         r0 = read
1: JLE 0,6(7)       if 0 < r0 then
2: LDC 1,1,0        r1=1
3: LDC 2,1,0        r2=1
4: MUL 1,1,0        r1=r1*r0
5: SUB 0,0,2        r0=r0-r2
6: JNE 0,-3(7)      until r0==0
7: OUT 1,0,0        write r1
8: HALT 0,0,0       HALT
*end of program