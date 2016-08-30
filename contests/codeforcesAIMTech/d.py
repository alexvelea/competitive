def read_number():
    data = get_chuck()
    try:
        return int(data)
    except ValueError:
        return float(data)

def input_generator():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)     

input_parser = input_generator()
def get_chuck():
    global input_parser
    return next(input_parser)


n = read_number()
chx = []
num_ap = []
inside_chx = []
for i in range(n):
	chx.append(read_number())
	num_ap.append(0)
	inside_chx.append([1, 1])

rez = 0

for index in range(0, 10 ** 3):
	def smaller(a, b):
		return a[0] * b[1] < a[1] * b[0]

	worst_chx = [0, 1]
	chosen_person = -1
	for i in range(n):
		if smaller(worst_chx, inside_chx[i]):
			chosen_person = i
			worst_chx = inside_chx[i]
		elif not smaller(inside_chx[i], worst_chx):
			# equal
			if chx[chosen_person] > chx[i]:
				chosen_person = i
				worst_chx = inside_chx[i]

	finish_chx = [1, 1]
	for i in range(n):
		if i != chosen_person:
			finish_chx[0] *= inside_chx[i][1] - inside_chx[i][0]
			finish_chx[1] *= inside_chx[i][1]

	finish_chx[0] *= inside_chx[chosen_person][0]
	finish_chx[1] *= inside_chx[chosen_person][1]

	finish_chx[0] *= chx[chosen_person]
	finish_chx[1] *= 100

	# print(chosen_person, index, finish_chx[0] / finish_chx[1])
	# print()
	# for j in range(n):
	# 	print(inside_chx[j][0], inside_chx[j][1])
	# print()
	# print()
	# print()


	inside_chx[chosen_person][0] *= 100 - chx[chosen_person]
	inside_chx[chosen_person][1] *= 100
	

	rez += (index + 1) * (finish_chx[0] / finish_chx[1])

print(rez)