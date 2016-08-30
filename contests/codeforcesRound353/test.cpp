#include <unordered_map>
#include <iostream>
using namespace std;


namespace {
template<class _Key, class _Tp,
	   class _Hash = hash<_Key>,
	   class _Pred = std::equal_to<_Key>,
	   class _Alloc = std::allocator<std::pair<const _Key, _Tp> >,
	   bool __cache_hash_code = false>
           class x : public unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc, __cache_hash_code> {
                x(size_type __n = 10,
		    const hasher& __hf = hasher(),
		    const key_equal& __eql = key_equal(),
		    const allocator_type& __a = allocator_type())
           }
}

int main() {
    unordered_map<int, int> x;
}
