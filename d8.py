n=int(input('enter'))
lst=[]
for i in range(n):
    lst.append(input())

vo='AEIOUaeiou'
alvoin=[]
for s in lst:
    for j in s:
        if j in vo :
            alvoin.append(j)

alvoin.reverse()
x=0
for i in range(len(lst)):
    char=list(lst[i])
    for j in range(len(char)):
        if char[j] in vo:
            char[j]=alvoin[x]
            x=x+1
    lst[i]="".join(char)
    
for s in lst:
    print(s)