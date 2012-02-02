//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>



#include <map>
template<typename _KeyId, typename _Value>
class ttt
{
public:
   typedef _KeyId                                        key_type;
   typedef _Value                                        saved_type;
   typedef std::map<key_type,saved_type>  map_type;
   typedef map_type::const_iterator    map_const_iterator; // Ó¯Ë·Í‡: type ëstd::map<_KeyId, _Value, std::less<_Key>, std::allocator<std::pair<const _Key, _Tp> > >í is not derived from type ëttt<_KeyId, _Value>í
};

int main(void) {
    return 0;
}
