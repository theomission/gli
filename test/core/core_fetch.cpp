//////////////////////////////////////////////////////////////////////////////////
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
/// @file gli/core/fetch.cpp
/// @date 2013-11-25 / 2013-11-25
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/vec1.hpp>
#include <glm/gtc/packing.hpp>
#include <glm/gtc/color_space.hpp>

namespace fetch_r8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_R8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec1>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec1(1));
			gli::texel_write<glm::u8vec1>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec1(2));
			gli::texel_write<glm::u8vec1>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec1(3));
			gli::texel_write<glm::u8vec1>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec1(4));
			gli::texel_write<glm::u8vec1>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec1(5));
			gli::save_dds(TextureA, "r8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("r8_unorm_4pixels.dds"));
		{
			glm::u8vec1 A = gli::texel_fetch<glm::u8vec1>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec1(1))) ? 0 : 1;
			glm::u8vec1 B = gli::texel_fetch<glm::u8vec1>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec1(2))) ? 0 : 1;
			glm::u8vec1 C = gli::texel_fetch<glm::u8vec1>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec1(3))) ? 0 : 1;
			glm::u8vec1 D = gli::texel_fetch<glm::u8vec1>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec1(4))) ? 0 : 1;
			glm::u8vec1 E = gli::texel_fetch<glm::u8vec1>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec1(5))) ? 0 : 1;
		}
		{
			glm::u8vec1 A = TextureB.load<glm::u8vec1>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec1(1))) ? 0 : 1;
			glm::u8vec1 B = TextureB.load<glm::u8vec1>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec1(2))) ? 0 : 1;
			glm::u8vec1 C = TextureB.load<glm::u8vec1>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec1(3))) ? 0 : 1;
			glm::u8vec1 D = TextureB.load<glm::u8vec1>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec1(4))) ? 0 : 1;
			glm::u8vec1 E = TextureB.load<glm::u8vec1>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec1(5))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_R8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec1>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec1(1));
			TextureC.store<glm::u8vec1>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec1(2));
			TextureC.store<glm::u8vec1>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec1(3));
			TextureC.store<glm::u8vec1>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec1(4));
			TextureC.store<glm::u8vec1>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec1(5));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_r8_unorm

namespace fetch_rg8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RG8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec2>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec2(1, 2));
			gli::texel_write<glm::u8vec2>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec2(3, 4));
			gli::texel_write<glm::u8vec2>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec2(5, 6));
			gli::texel_write<glm::u8vec2>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec2(7, 8));
			gli::texel_write<glm::u8vec2>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec2(9, 5));
			gli::save_dds(TextureA, "rg8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rg8_unorm_4pixels.dds"));
		{
			glm::u8vec2 A = gli::texel_fetch<glm::u8vec2>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec2(1, 2))) ? 0 : 1;
			glm::u8vec2 B = gli::texel_fetch<glm::u8vec2>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec2(3, 4))) ? 0 : 1;
			glm::u8vec2 C = gli::texel_fetch<glm::u8vec2>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec2(5, 6))) ? 0 : 1;
			glm::u8vec2 D = gli::texel_fetch<glm::u8vec2>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec2(7, 8))) ? 0 : 1;
			glm::u8vec2 E = gli::texel_fetch<glm::u8vec2>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec2(9, 5))) ? 0 : 1;
		}
		{
			glm::u8vec2 A = TextureB.load<glm::u8vec2>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec2(1, 2))) ? 0 : 1;
			glm::u8vec2 B = TextureB.load<glm::u8vec2>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec2(3, 4))) ? 0 : 1;
			glm::u8vec2 C = TextureB.load<glm::u8vec2>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec2(5, 6))) ? 0 : 1;
			glm::u8vec2 D = TextureB.load<glm::u8vec2>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec2(7, 8))) ? 0 : 1;
			glm::u8vec2 E = TextureB.load<glm::u8vec2>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec2(9, 5))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RG8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec2>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec2(1, 2));
			TextureC.store<glm::u8vec2>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec2(3, 4));
			TextureC.store<glm::u8vec2>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec2(5, 6));
			TextureC.store<glm::u8vec2>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec2(7, 8));
			TextureC.store<glm::u8vec2>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec2(9, 5));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rg8_unorm

namespace fetch_rgb8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGB8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(255, 0, 0));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(255, 255, 0));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(0, 255, 0));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(0, 0, 255));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(255, 128, 0));
			gli::save_dds(TextureA, "rgb8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgb8_unorm_4pixels.dds"));
		{
			glm::u8vec3 A = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(255, 0, 0))) ? 0 : 1;
			glm::u8vec3 B = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(255, 255, 0))) ? 0 : 1;
			glm::u8vec3 C = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(0, 255, 0))) ? 0 : 1;
			glm::u8vec3 D = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(0, 0, 255))) ? 0 : 1;
			glm::u8vec3 E = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(255, 128, 0))) ? 0 : 1;
		}
		{
			glm::u8vec3 A = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(255, 0, 0))) ? 0 : 1;
			glm::u8vec3 B = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(255, 255, 0))) ? 0 : 1;
			glm::u8vec3 C = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(0, 255, 0))) ? 0 : 1;
			glm::u8vec3 D = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(0, 0, 255))) ? 0 : 1;
			glm::u8vec3 E = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(255, 128, 0))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(255, 0, 0));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(255, 255, 0));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(0, 255, 0));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(0, 0, 255));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(255, 128, 0));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgb8_unorm

namespace fetch_rgba8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGBA8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(255, 0, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(255, 255, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(0, 0, 255, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(255, 128, 0, 255));
			gli::save_dds(TextureA, "rgba8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgba8_unorm_4pixels.dds"));
		{
			glm::u8vec4 A = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 B = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(255, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 C = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 E = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(255, 128, 0, 255))) ? 0 : 1;
		}
		{
			glm::u8vec4 A = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 B = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(255, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 C = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 E = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(255, 128, 0, 255))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGBA8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(255, 0, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(255, 255, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(0, 0, 255, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(255, 128, 0, 255));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgba8_unorm

namespace fetch_rgb10a2_unorm
{
	int test()
	{
		int Error(0);

		glm::uint32 ColorR = glm::packUnorm3x10_1x2(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		glm::uint32 ColorY = glm::packUnorm3x10_1x2(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		glm::uint32 ColorG = glm::packUnorm3x10_1x2(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		glm::uint32 ColorB = glm::packUnorm3x10_1x2(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		glm::uint32 ColorO = glm::packUnorm3x10_1x2(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));

		gli::texture2D TextureA(gli::FORMAT_RGB10A2_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::uint32>(TextureA, gli::texture2D::dim_type(0, 0), 0, ColorR);
			gli::texel_write<glm::uint32>(TextureA, gli::texture2D::dim_type(1, 0), 0, ColorY);
			gli::texel_write<glm::uint32>(TextureA, gli::texture2D::dim_type(1, 1), 0, ColorG);
			gli::texel_write<glm::uint32>(TextureA, gli::texture2D::dim_type(0, 1), 0, ColorB);
			gli::texel_write<glm::uint32>(TextureA, gli::texture2D::dim_type(0, 0), 1, ColorO);
			gli::save_dds(TextureA, "rgb10a2_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgb10a2_unorm_4pixels.dds"));
		{
			glm::uint32 A = gli::texel_fetch<glm::uint32>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += A == ColorR ? 0 : 1;
			glm::uint32 B = gli::texel_fetch<glm::uint32>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += B == ColorY ? 0 : 1;
			glm::uint32 C = gli::texel_fetch<glm::uint32>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += C == ColorG ? 0 : 1;
			glm::uint32 D = gli::texel_fetch<glm::uint32>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += D == ColorB ? 0 : 1;
			glm::uint32 E = gli::texel_fetch<glm::uint32>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += E == ColorO ? 0 : 1;
		}
		{
			glm::uint32 A = TextureB.load<glm::uint32>(gli::texture2D::dim_type(0, 0), 0);
			Error += A == ColorR ? 0 : 1;
			glm::uint32 B = TextureB.load<glm::uint32>(gli::texture2D::dim_type(1, 0), 0);
			Error += B == ColorY ? 0 : 1;
			glm::uint32 C = TextureB.load<glm::uint32>(gli::texture2D::dim_type(1, 1), 0);
			Error += C == ColorG ? 0 : 1;
			glm::uint32 D = TextureB.load<glm::uint32>(gli::texture2D::dim_type(0, 1), 0);
			Error += D == ColorB ? 0 : 1;
			glm::uint32 E = TextureB.load<glm::uint32>(gli::texture2D::dim_type(0, 0), 1);
			Error += E == ColorO ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB10A2_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::uint32>(gli::texture2D::dim_type(0, 0), 0, ColorR);
			TextureC.store<glm::uint32>(gli::texture2D::dim_type(1, 0), 0, ColorY);
			TextureC.store<glm::uint32>(gli::texture2D::dim_type(1, 1), 0, ColorG);
			TextureC.store<glm::uint32>(gli::texture2D::dim_type(0, 1), 0, ColorB);
			TextureC.store<glm::uint32>(gli::texture2D::dim_type(0, 0), 1, ColorO);
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgb10a2_unorm

namespace fetch_srgb8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGB8_SRGB, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 0, 0))));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 255, 0))));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 255, 0))));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 0, 255))));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 128, 0))));
			gli::save_dds(TextureA, "srgb8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("srgb8_unorm_4pixels.dds"));
		{
			glm::u8vec3 A = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 0, 0))))) ? 0 : 1;
			glm::u8vec3 B = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 255, 0))))) ? 0 : 1;
			glm::u8vec3 C = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 255, 0))))) ? 0 : 1;
			glm::u8vec3 D = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 0, 255))))) ? 0 : 1;
			glm::u8vec3 E = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 128, 0))))) ? 0 : 1;
		}
		{
			glm::u8vec3 A = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 0, 0))))) ? 0 : 1;
			glm::u8vec3 B = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 255, 0))))) ? 0 : 1;
			glm::u8vec3 C = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 255, 0))))) ? 0 : 1;
			glm::u8vec3 D = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 0, 255))))) ? 0 : 1;
			glm::u8vec3 E = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 128, 0))))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB8_SRGB, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 0, 0))));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 255, 0))));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 255, 0))));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(0, 0, 255))));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(glm::convertLinearToSRGB(glm::vec3(255, 128, 0))));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_srgb8_unorm

namespace fetch_srgba8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGBA8_SRGB, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f))));
			gli::save_dds(TextureA, "srgba8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("srgba8_unorm_4pixels.dds"));
		{
			glm::u8vec4 A = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 B = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 C = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 D = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 E = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f))))) ? 0 : 1;
		}
		{
			glm::u8vec4 A = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 B = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 C = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 D = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))))) ? 0 : 1;
			glm::u8vec4 E = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f))))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGBA8_SRGB, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f))));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(glm::convertLinearToSRGB(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f))));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_srgba8_unorm

namespace fetch_bgr8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGB8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(0, 0, 255));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(0, 255, 255));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(0, 255, 0));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(255, 0, 0));
			gli::texel_write<glm::u8vec3>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(0, 128, 255));
			gli::save_dds(TextureA, "rgb8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgb8_unorm_4pixels.dds"));
		{
			glm::u8vec3 A = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(0, 0, 255))) ? 0 : 1;
			glm::u8vec3 B = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(0, 255, 255))) ? 0 : 1;
			glm::u8vec3 C = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(0, 255, 0))) ? 0 : 1;
			glm::u8vec3 D = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(255, 0, 0))) ? 0 : 1;
			glm::u8vec3 E = gli::texel_fetch<glm::u8vec3>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(0, 128, 255))) ? 0 : 1;
		}
		{
			glm::u8vec3 A = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec3(0, 0, 255))) ? 0 : 1;
			glm::u8vec3 B = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec3(0, 255, 255))) ? 0 : 1;
			glm::u8vec3 C = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec3(0, 255, 0))) ? 0 : 1;
			glm::u8vec3 D = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec3(255, 0, 0))) ? 0 : 1;
			glm::u8vec3 E = TextureB.load<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec3(0, 128, 255))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec3(0, 0, 255));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec3(0, 255, 255));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec3(0, 255, 0));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec3(255, 0, 0));
			TextureC.store<glm::u8vec3>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec3(0, 128, 255));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_bgr8_unorm

namespace fetch_bgra8_unorm
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_BGRA8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(0, 0, 255, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(0, 255, 255, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(255, 0, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(0, 128, 255, 255));
			gli::save_dds(TextureA, "bgra8_unorm_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("bgra8_unorm_4pixels.dds"));
		{
			glm::u8vec4 A = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 B = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(0, 255, 255, 255))) ? 0 : 1;
			glm::u8vec4 C = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 E = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(0, 128, 255, 255))) ? 0 : 1;
		}
		{
			glm::u8vec4 A = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 B = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(0, 255, 255, 255))) ? 0 : 1;
			glm::u8vec4 C = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 E = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(0, 128, 255, 255))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_BGRA8_UNORM, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(0, 0, 255, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(0, 255, 255, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(255, 0, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(0, 128, 255, 255));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_bgra8_unorm

namespace fetch_rgba8u
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGBA8_UINT, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(255, 0, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(255, 255, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(0, 0, 255, 255));
			gli::texel_write<glm::u8vec4>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(255, 128, 0, 255));
			gli::save_dds(TextureA, "rgba8u_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgba8u_4pixels.dds"));
		{
			glm::u8vec4 A = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 B = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(255, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 C = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 E = gli::texel_fetch<glm::u8vec4>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(255, 128, 0, 255))) ? 0 : 1;
		}
		{
			glm::u8vec4 A = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::equal(A, glm::u8vec4(255, 0, 0, 255))) ? 0 : 1;
			glm::u8vec4 B = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::equal(B, glm::u8vec4(255, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 C = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::equal(C, glm::u8vec4(0, 255, 0, 255))) ? 0 : 1;
			glm::u8vec4 D = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::equal(D, glm::u8vec4(0, 0, 255, 255))) ? 0 : 1;
			glm::u8vec4 E = TextureB.load<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::equal(E, glm::u8vec4(255, 128, 0, 255))) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGBA8_UINT, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 0, glm::u8vec4(255, 0, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 0), 0, glm::u8vec4(255, 255, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(1, 1), 0, glm::u8vec4(0, 255, 0, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 1), 0, glm::u8vec4(0, 0, 255, 255));
			TextureC.store<glm::u8vec4>(gli::texture2D::dim_type(0, 0), 1, glm::u8vec4(255, 128, 0, 255));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgba8u

namespace fetch_rgba16f
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGBA16_SFLOAT, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::u64>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::packHalf4x16(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
			gli::texel_write<glm::u64>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::packHalf4x16(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
			gli::texel_write<glm::u64>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::packHalf4x16(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
			gli::texel_write<glm::u64>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::packHalf4x16(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
			gli::texel_write<glm::u64>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::packHalf4x16(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)));
			gli::save_dds(TextureA, "rgba16f_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgba16f_4pixels.dds"));
		{
			glm::u64 A = gli::texel_fetch<glm::u64>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::packHalf4x16(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 B = gli::texel_fetch<glm::u64>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::packHalf4x16(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 C = gli::texel_fetch<glm::u64>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += C  == glm::packHalf4x16(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 D = gli::texel_fetch<glm::u64>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += D ==  glm::packHalf4x16(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) ? 0 : 1;
			glm::u64 E = gli::texel_fetch<glm::u64>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::packHalf4x16(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)) ? 0 : 1;
		}
		{
			glm::u64 A = TextureB.load<glm::u64>(gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::packHalf4x16(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 B = TextureB.load<glm::u64>(gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::packHalf4x16(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 C = TextureB.load<glm::u64>(gli::texture2D::dim_type(1, 1), 0);
			Error += C  == glm::packHalf4x16(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::u64 D = TextureB.load<glm::u64>(gli::texture2D::dim_type(0, 1), 0);
			Error += D ==  glm::packHalf4x16(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) ? 0 : 1;
			glm::u64 E = TextureB.load<glm::u64>(gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::packHalf4x16(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGBA16_SFLOAT, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::u64>(gli::texture2D::dim_type(0, 0), 0, glm::packHalf4x16(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
			TextureC.store<glm::u64>(gli::texture2D::dim_type(1, 0), 0, glm::packHalf4x16(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
			TextureC.store<glm::u64>(gli::texture2D::dim_type(1, 1), 0, glm::packHalf4x16(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
			TextureC.store<glm::u64>(gli::texture2D::dim_type(0, 1), 0, glm::packHalf4x16(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
			TextureC.store<glm::u64>(gli::texture2D::dim_type(0, 0), 1, glm::packHalf4x16(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgba16f

namespace fetch_rgb32f
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGB32_SFLOAT, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::vec3>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::vec3(1.0f, 0.0f, 0.0f));
			gli::texel_write<glm::vec3>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::vec3(1.0f, 1.0f, 0.0f));
			gli::texel_write<glm::vec3>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::vec3(0.0f, 1.0f, 0.0f));
			gli::texel_write<glm::vec3>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::vec3(0.0f, 0.0f, 1.0f));
			gli::texel_write<glm::vec3>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::vec3(1.0f, 0.5f, 0.0f));
			gli::save_dds(TextureA, "rgb32f_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgb32f_4pixels.dds"));
		{
			glm::vec3 A = gli::texel_fetch<glm::vec3>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::epsilonEqual(A, glm::vec3(1.0f, 0.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 B = gli::texel_fetch<glm::vec3>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::epsilonEqual(B, glm::vec3(1.0f, 1.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 C = gli::texel_fetch<glm::vec3>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::epsilonEqual(C, glm::vec3(0.0f, 1.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 D = gli::texel_fetch<glm::vec3>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::epsilonEqual(D, glm::vec3(0.0f, 0.0f, 1.0f), 0.001f)) ? 0 : 1;
			glm::vec3 E = gli::texel_fetch<glm::vec3>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::epsilonEqual(E, glm::vec3(1.0f, 0.5f, 0.0f), 0.001f)) ? 0 : 1;
		}
		{
			glm::vec3 A = TextureB.load<glm::vec3>(gli::texture2D::dim_type(0, 0), 0);
			Error += glm::all(glm::epsilonEqual(A, glm::vec3(1.0f, 0.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 B = TextureB.load<glm::vec3>(gli::texture2D::dim_type(1, 0), 0);
			Error += glm::all(glm::epsilonEqual(B, glm::vec3(1.0f, 1.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 C = TextureB.load<glm::vec3>(gli::texture2D::dim_type(1, 1), 0);
			Error += glm::all(glm::epsilonEqual(C, glm::vec3(0.0f, 1.0f, 0.0f), 0.001f)) ? 0 : 1;
			glm::vec3 D = TextureB.load<glm::vec3>(gli::texture2D::dim_type(0, 1), 0);
			Error += glm::all(glm::epsilonEqual(D, glm::vec3(0.0f, 0.0f, 1.0f), 0.001f)) ? 0 : 1;
			glm::vec3 E = TextureB.load<glm::vec3>(gli::texture2D::dim_type(0, 0), 1);
			Error += glm::all(glm::epsilonEqual(E, glm::vec3(1.0f, 0.5f, 0.0f), 0.001f)) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB32_SFLOAT, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::vec3>(gli::texture2D::dim_type(0, 0), 0, glm::vec3(1.0f, 0.0f, 0.0f));
			TextureC.store<glm::vec3>(gli::texture2D::dim_type(1, 0), 0, glm::vec3(1.0f, 1.0f, 0.0f));
			TextureC.store<glm::vec3>(gli::texture2D::dim_type(1, 1), 0, glm::vec3(0.0f, 1.0f, 0.0f));
			TextureC.store<glm::vec3>(gli::texture2D::dim_type(0, 1), 0, glm::vec3(0.0f, 0.0f, 1.0f));
			TextureC.store<glm::vec3>(gli::texture2D::dim_type(0, 0), 1, glm::vec3(1.0f, 0.5f, 0.0f));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgb32f

namespace fetch_rgb9e5
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RGB9E5_UFLOAT, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::uint32_t(1));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::uint32_t(3));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::uint32_t(5));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::uint32_t(7));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::uint32_t(9));
			gli::save_dds(TextureA, "rgb9e5_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rgb9e5_4pixels.dds"));
		{
			glm::uint32_t A = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::uint32_t(1) ? 0 : 1;
			glm::uint32_t B = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::uint32_t(3) ? 0 : 1;
			glm::uint32_t C = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += C == glm::uint32_t(5) ? 0 : 1;
			glm::uint32_t D = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += D == glm::uint32_t(7) ? 0 : 1;
			glm::uint32_t E = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::uint32_t(9) ? 0 : 1;
		}
		{
			glm::uint32_t A = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::uint32_t(1) ? 0 : 1;
			glm::uint32_t B = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::uint32_t(3) ? 0 : 1;
			glm::uint32_t C = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(1, 1), 0);
			Error += C == glm::uint32_t(5) ? 0 : 1;
			glm::uint32_t D = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 1), 0);
			Error += D == glm::uint32_t(7) ? 0 : 1;
			glm::uint32_t E = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::uint32_t(9) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RGB9E5_UFLOAT, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 0, glm::uint32_t(1));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(1, 0), 0, glm::uint32_t(3));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(1, 1), 0, glm::uint32_t(5));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 1), 0, glm::uint32_t(7));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 1, glm::uint32_t(9));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rgb9e5

namespace fetch_rg11b10f
{
	int test()
	{
		int Error(0);

		gli::texture2D TextureA(gli::FORMAT_RG11B10_UFLOAT, gli::texture2D::dim_type(2, 2));
		{
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 0), 0, glm::packF2x11_1x10(glm::vec3(1.0f, 0.0f, 0.0f)));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(1, 0), 0, glm::packF2x11_1x10(glm::vec3(1.0f, 1.0f, 0.0f)));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(1, 1), 0, glm::packF2x11_1x10(glm::vec3(0.0f, 1.0f, 0.0f)));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 1), 0, glm::packF2x11_1x10(glm::vec3(0.0f, 0.0f, 1.0f)));
			gli::texel_write<glm::uint32_t>(TextureA, gli::texture2D::dim_type(0, 0), 1, glm::packF2x11_1x10(glm::vec3(1.0f, 0.5f, 0.0f)));
			gli::save_dds(TextureA, "rg11b10f_4pixels.dds");
		}

		gli::texture2D TextureB(gli::load_dds("rg11b10f_4pixels.dds"));
		{
			glm::uint32_t A = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::packF2x11_1x10(glm::vec3(1.0f, 0.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t B = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::packF2x11_1x10(glm::vec3(1.0f, 1.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t C = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(1, 1), 0);
			Error += C == glm::packF2x11_1x10(glm::vec3(0.0f, 1.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t D = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 1), 0);
			Error += D == glm::packF2x11_1x10(glm::vec3(0.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::uint32_t E = gli::texel_fetch<glm::uint32_t>(TextureB, gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::packF2x11_1x10(glm::vec3(1.0f, 0.5f, 0.0f)) ? 0 : 1;
		}
		{
			glm::uint32_t A = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 0);
			Error += A == glm::packF2x11_1x10(glm::vec3(1.0f, 0.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t B = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(1, 0), 0);
			Error += B == glm::packF2x11_1x10(glm::vec3(1.0f, 1.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t C = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(1, 1), 0);
			Error += C == glm::packF2x11_1x10(glm::vec3(0.0f, 1.0f, 0.0f)) ? 0 : 1;
			glm::uint32_t D = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 1), 0);
			Error += D == glm::packF2x11_1x10(glm::vec3(0.0f, 0.0f, 1.0f)) ? 0 : 1;
			glm::uint32_t E = TextureB.load<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 1);
			Error += E == glm::packF2x11_1x10(glm::vec3(1.0f, 0.5f, 0.0f)) ? 0 : 1;
		}

		gli::texture2D TextureC(gli::FORMAT_RG11B10_UFLOAT, gli::texture2D::dim_type(2, 2));
		{
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 0, glm::packF2x11_1x10(glm::vec3(1.0f, 0.0f, 0.0f)));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(1, 0), 0, glm::packF2x11_1x10(glm::vec3(1.0f, 1.0f, 0.0f)));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(1, 1), 0, glm::packF2x11_1x10(glm::vec3(0.0f, 1.0f, 0.0f)));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 1), 0, glm::packF2x11_1x10(glm::vec3(0.0f, 0.0f, 1.0f)));
			TextureC.store<glm::uint32_t>(gli::texture2D::dim_type(0, 0), 1, glm::packF2x11_1x10(glm::vec3(1.0f, 0.5f, 0.0f)));
		}

		Error += TextureA == TextureB ? 0 : 1;
		Error += TextureA == TextureC ? 0 : 1;

		return Error;
	}
}//namespace fetch_rg11b10f

int main()
{
	int Error(0);

	Error += fetch_r8_unorm::test();
	Error += fetch_rg8_unorm::test();
	Error += fetch_rgb8_unorm::test();
	Error += fetch_rgba8_unorm::test();
	Error += fetch_rgb10a2_unorm::test();
	Error += fetch_srgb8_unorm::test();
	Error += fetch_srgba8_unorm::test();
	Error += fetch_bgr8_unorm::test();
	Error += fetch_bgra8_unorm::test();
	Error += fetch_rgba8u::test();
	Error += fetch_rgba16f::test();
	Error += fetch_rgb32f::test();
	Error += fetch_rgb9e5::test();
	Error += fetch_rg11b10f::test();

	return Error;
}
