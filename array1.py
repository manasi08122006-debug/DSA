array=[1, 2, 3, 4, 5]
maximum=array[0]
for i in array:
    if i>maximum:
        maximum=i
print("the maximum integer is:",maximum)

i=-3
while i<=13:
    print("**")
    print("*")
    i=i+1

x=0
x_=1

for i in range(10):
    x,x_=x_,x+x_
    print(x)
x=0
x_=1
for i in range(10):
    x=x_
    x_=x+x_
    print(x)