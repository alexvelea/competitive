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

n, m = range(1, 10)
print(n, m)
