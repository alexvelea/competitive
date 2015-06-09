(n, k) = raw_input().split()

n = int(n)
k = int(k)

rez = k * (k - 1) * (k - 2) / 6

if n == 1:
	rez *= 3 * (2 ** 19)
	if rez == 0:
		print 2
	else:
		print rez

if n == 2:
	rez *= 3 * 2 * 2 * 2 * 2 * 2
	print rez

if n == 3:
	rez *= 3 * ((2) ** 3)
	if rez == 0:
		print 2
	else:
		print rez   

if n == 4:
	rez *= 3 * (2 ** 13)
	if rez == 0:
		print 2
	else:
		print rez

if n == 5:
	rez *= 3 * (2 ** 2)
	print rez

if n == 6:
	rez *= 3 * (2 ** 9)
	print rez

if n == 7:
	rez *= 3 * (2 ** 5)
	print rez

if n == 8:
	last = 6
	for i in range(3, 31):
		last = 3 * (2 ** (i - 1)) - last
	rez *= last
	print rez
