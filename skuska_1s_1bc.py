

# uloha 1
def je_mocnina2(a):
    mocnina = 2
    while True:
        if a == mocnina:
            return True
        if mocnina > a:
            return False
        mocnina = mocnina * 2


# uloha 2
def uloha2(n):
    if n < 1:
        return 0
    c = int(input())
    temp = uloha2(n-1)
    if je_mocnina2(c):
        return temp + 1
    else:
        return temp


# uloha 3
def uloha3(t):
    del t[0]
    del t[0]


# uloha 4
def uloha4(A):
    pozicia = [0,0]
    naj = A[0][0]

    for i in range(len(A)):
        for j in range (len(A[i])):
            if A[i][j] > naj:
                pozicia[0] = i
                pozicia[1] = j
                naj = A[i][j]
    return pozicia


# uloha 5
def uloha5(ret1, ret2):
    for znak in ret1:
        if znak not in ret2:
            return False
    return True


# uloha 6
def uloha6(n):
    t = []
    pouzite = []

    while len(pouzite) < n:
        c = int(input())
        t.append(c)
        if c not in pouzite:
            pouzite.append(c)

    return t


# uloha 7
def uloha7():
    naj = 0
    last = None
    naj_last = 0

    while True:
        c = int(input())
        if last is None:
            last = c
        if c == last:
            naj_last = naj_last + 1
        else:
            if naj_last > naj:
                naj = naj_last
                naj_last = 1
        last = c
        if c == 0:
            break

    return naj

# uloha 1
#for i in range(34):
#    print(str(i) + str(je_mocnina2(i)))

# uloha 2
#print(uloha2(6))

# uloha 3
#t = [1,2,3,4,5,6]
#uloha3(t)
#print(t)

# uloha 4
#A = [[0,0,1],[0,1,0]]
#print(uloha4(A))

# uloha 5
#a = [1,2,3,3,4,5]
#b = [5,4,3,2,1]
#print(uloha5(a,b))
#b = [5,4,2,1]
#print(uloha5(a,b))

# uloha 6
#print(uloha6(3))

# uloha 7
#print(uloha7())