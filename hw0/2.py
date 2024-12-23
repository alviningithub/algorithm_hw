n = int(input())
for i in range(n):
    length = int(input())
    strand_1 = input()
    for char in strand_1[::-1]:
        match char:
            case 'A':
                print('T',end='')
            case 'T':
                print('A',end='')
            case 'C':
                print('G',end='')
            case 'G':
                print('C',end='')
    print()
    