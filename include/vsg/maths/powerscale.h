#pragma once

/* <editor-fold desc="MIT License">

Copyright(c) 2018 Robert Osfield

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</editor-fold> */

#include <vsg/maths/vec3.h>
#include <vsg/maths/vec4.h>

namespace vsg
{

    template<typename T>
    constexpr t_vec4<T> psc_normalize(const t_vec3<T>& v)
    {
        auto l = length(v);
        if (l==0.0) return t_vec4<T>();
        auto inv_l = 1.0/l;
        return t_vec4<T>(v.x * inv_l, v.y * inv_l, v.z * inv_l, 0.0 - log10(inv_l));
    }

    template<typename T>
    constexpr t_vec4<T> psc_normalize(const t_vec4<T>& v)
    {
        auto l = length(v);
        if (l==0.0) return t_vec4<T>();
        auto inv_l = 1.0/l;
        return t_vec4<T>(v.x * inv_l, v.y * inv_l, v.z * inv_l, v.w - log10(inv_l));
    }

    template<typename T>
    constexpr t_vec4<T> psc_add(const t_vec4<T>& v1, const t_vec4<T>& v2)
    {
        if (v2.w > v1.w)
        {
            auto p = std::pow( 10.0, v1.w - v2.w);
            return t_vec4<T>(v1.x * p + v2.x, v1.y * p + v2.y, v1.z * p + v2.z, v2.w);
        }
        else
        {
            auto p = std::pow( 10.0, v2.w - v1.w);
            return t_vec4<T>(v1.x + v2.x * p, v1.y + v2.y * p, v1.z + v2.z * p, v1.w);
        }
    }

    template<typename T>
    constexpr t_vec3<T> psc_to_linear(const t_vec4<T>& v)
    {
        return v.xyz * pow(10.0, v.w);
    }

} // namespace vsg
