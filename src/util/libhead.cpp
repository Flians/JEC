#include "util/libhead.h"

/* initial */
size_t init_id = 0;

const std::unordered_map<Value, string, EnumClassHash> Const_Str = {
    {L, "1'b0"},
    {H, "1'b1"},
    {X, "1'bx"}};
