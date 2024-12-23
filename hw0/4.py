n = int(input())
numbers = input()
number_list = numbers.split()
# print(number_list)
number_list = [int(i) for i in number_list ]
# print(number_list)
number_list.sort()
# print(number_list)
print(number_list[int(n/2)+n%2-1])
