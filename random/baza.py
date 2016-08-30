sigma = [chr(ord('0') + i) for i in range(0, 10)] + [chr(ord('a') + i) for i in range(0, 26)]

def convert_to_10(number, base):
    result = 0
    for itr in range(0, len(number)):
        result *= base
        result += ord(number[itr]) - ord('0')
    return result

def convert_from_10(number, base):
    result = ""
    while (number > 0):
        result += sigma[number % base]
        number = int(number / base)
    result = result[::-1]
    return result

def convert(number, baseA, baseB):
    number10 = convert_to_10(number, baseA)
    result = convert_from_10(number10, baseB)
    return result

number = input()
baseA = int(input())
baseB = int(input())

print(convert(number, baseA, baseB)) 
