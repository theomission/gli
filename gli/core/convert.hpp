///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/convert.hpp
/// @date 2015-10-08 / 2015-10-08
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include "../type.hpp"
#include <limits>

namespace gli{
namespace detail
{
	enum convertMode
	{
		CONVERT_MODE_CAST,
		CONVERT_MODE_NORM,
		CONVERT_MODE_SRGB,
		CONVERT_MODE_RGB9E5,
		CONVERT_MODE_RG11B10F,
		CONVERT_MODE_RGB10A2UNORM,
		CONVERT_MODE_RGB10A2SNORM,
		CONVERT_MODE_RGB10A2UINT,
		CONVERT_MODE_RGB10A2SINT,
	};

	template <typename textureType, typename retType, typename T, precision P, template <typename, precision> class vecType, convertMode mode = CONVERT_MODE_CAST>
	struct convert
	{
		static vecType<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			return vecType<retType, P>(Texture.template load<vecType<T, P> >(TexelCoord, Level));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, vecType<retType, P> const & Texel)
		{
			Texture.template store<vecType<T, P> >(TexelCoord, Level, vecType<T, P>(Texel));
		}
	};

	template <typename textureType, typename retType, typename T, precision P, template <typename, precision> class vecType>
	struct convert<textureType, retType, T, P, vecType, CONVERT_MODE_NORM>
	{
		static vecType<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_NORM requires a float sampler");
			vecType<T, P> const Load(Texture.template load<vecType<T, P> >(TexelCoord, Level));
			return compNormalize<retType>(Load);
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, vecType<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_NORM requires a float sampler");
			vecType<T, P> const Store(compScale<T>(Texel));
			Texture.template store<vecType<T, P> >(TexelCoord, Level, Store);
		}
	};

	template <typename textureType, typename retType, typename T, precision P, template <typename, precision> class vecType>
	struct convert<textureType, retType, T, P, vecType, CONVERT_MODE_SRGB>
	{
		static vecType<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_SRGB requires a float sampler");
			return convertSRGBToLinear(compNormalize<retType>(Texture.template load<vecType<T, P> >(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, vecType<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_SRGB requires a float sampler");
			Texture.template store<vecType<T, P> >(TexelCoord, Level, gli::compScale<T>(convertLinearToSRGB(Texel)));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec3, CONVERT_MODE_RGB9E5>
	{
		static tvec3<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB9E5 requires a float sampler");
			return tvec3<retType, P>(unpackF3x9_E1x5(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec3<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB9E5 requires a float sampler");
			Texture.template store<uint32>(TexelCoord, Level, packF3x9_E1x5(tvec3<float, P>(Texel)));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec3, CONVERT_MODE_RG11B10F>
	{
		static tvec3<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RG11B10F requires a float sampler");
			return tvec3<retType, P>(unpackF2x11_1x10(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec3<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RG11B10F requires a float sampler");
			Texture.template store<uint32>(TexelCoord, Level, packF2x11_1x10(tvec3<float, P>(Texel)));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec4, CONVERT_MODE_RGB10A2UNORM>
	{
		static tvec4<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB10A2UNORM requires a float sampler");
			return tvec4<retType, P>(unpackUnorm3x10_1x2(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec4<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB10A2UNORM requires a float sampler");
			Texture.template store<uint32>(TexelCoord, Level, packUnorm3x10_1x2(tvec4<float, P>(Texel)));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec4, CONVERT_MODE_RGB10A2SNORM>
	{
		static tvec4<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB10A2SNORM requires a float sampler");
			return tvec4<retType, P>(unpackSnorm3x10_1x2(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec4<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_iec559, "CONVERT_MODE_RGB10A2SNORM requires a float sampler");
			Texture.template store<uint32>(TexelCoord, Level, packSnorm3x10_1x2(Texel));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec4, CONVERT_MODE_RGB10A2UINT>
	{
		static tvec4<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_integer, "CONVERT_MODE_RGB10A2UINT requires an integer sampler");
			return tvec4<retType, P>(unpackU3x10_1x2(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec4<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_integer, "CONVERT_MODE_RGB10A2UINT requires an integer sampler");
			Texture.template store<uint32>(TexelCoord, Level, packU3x10_1x2(Texel));
		}
	};

	template <typename textureType, typename retType, typename T, precision P>
	struct convert<textureType, retType, T, P, tvec4, CONVERT_MODE_RGB10A2SINT>
	{
		static tvec4<retType, P> fetch(textureType const & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level)
		{
			static_assert(std::numeric_limits<retType>::is_integer, "CONVERT_MODE_RGB10A2SINT requires an integer sampler");
			return tvec4<retType, P>(unpackI3x10_1x2(Texture.template load<uint32>(TexelCoord, Level)));
		}

		static void write(textureType & Texture, typename textureType::dim_type const & TexelCoord, typename textureType::size_type Level, tvec4<retType, P> const & Texel)
		{
			static_assert(std::numeric_limits<retType>::is_integer, "CONVERT_MODE_RGB10A2SINT requires an integer sampler");
			Texture.template store<uint32>(TexelCoord, Level, packI3x10_1x2(Texel));
		}
	};
}//namespace detail
}//namespace gli
