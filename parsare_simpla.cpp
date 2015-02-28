#define kMaxChar 1000000
#define verf ((++BufferChar >= kMaxChar) ? (in.read(Buffer, kMaxChar), BufferChar = 0) : (1))

int BufferChar = kMaxChar;
char Buffer[kMaxChar];

void cit (int &a) {
    if (BufferChar >= kMaxChar)
        verf;
    bool minus = false;
    for ( ;!((Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9') || (Buffer [BufferChar] == '-')); verf)
        ;
    if (Buffer[BufferChar] == '-') {
        verf;
        minus = true;
    }
    for (a = 0; (Buffer[BufferChar] >= '0' && Buffer[BufferChar] <= '9'); a *= 10,a += (Buffer[BufferChar] - '0'), verf)
        ;
    if (minus)
        a *= -1;
    return ;
}
