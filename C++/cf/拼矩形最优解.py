t=int(input())
for _ in range(t):
    l1,b1,l2,b2,l3,b3=map(int,input().split())
    ok=(l1==l2==l3) and (b1+b2+b3==l1)or\
        (b1==b2==b3) and (l1+l2+l3==b1)or\
        (l1==l2+l3 and b2==b3 and b2+b1==l1)or\
        (b1==b3+b2 and l2==l3 and l2+l1==b1)
    print('YES' if ok else 'NO')