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
/// @file test/core/texture_1d.cpp
/// @date 2013-01-12 / 2013-01-12
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>

int test_alloc()
{
	int Error(0);

	std::vector<gli::format> Formats;
	Formats.push_back(gli::FORMAT_RGBA8_UNORM);
	Formats.push_back(gli::FORMAT_RGB8_UNORM);
	Formats.push_back(gli::FORMAT_R8_SNORM);
	Formats.push_back(gli::FORMAT_RGB_DXT1_UNORM);
	Formats.push_back(gli::FORMAT_RGBA_BP_UNORM);
	Formats.push_back(gli::FORMAT_RGBA32_SFLOAT);

	std::vector<std::size_t> Sizes;
	Sizes.push_back(16);
	Sizes.push_back(32);
	Sizes.push_back(15);
	Sizes.push_back(17);
	Sizes.push_back(1);

	for(std::size_t FormatIndex = 0; FormatIndex < Formats.size(); ++FormatIndex)
	for(std::size_t SizeIndex = 0; SizeIndex < Sizes.size(); ++SizeIndex)
	{
		gli::texture1D::dim_type Size(Sizes[SizeIndex]);

		gli::texture1D TextureA(Formats[FormatIndex], Size, gli::levels(Size));
		gli::texture1D TextureB(Formats[FormatIndex], Size);

		Error += TextureA == TextureB ? 0 : 1;
	}

	return Error;
}

namespace clear
{
	int run()
	{
		int Error(0);

		glm::u8vec4 const Orange(255, 127, 0, 255);

		gli::texture1D::dim_type Size(16u);
		gli::texture1D Texture(gli::FORMAT_RGBA8_UINT, Size, gli::levels(Size));

		Texture.clear<glm::u8vec4>(Orange);

		return Error;
	}
}//namespace

namespace query
{
	int run()
	{
		int Error(0);

		gli::texture1D Texture(gli::FORMAT_RGBA8_UINT, gli::texture1D::dim_type(2), 2);

		Error += Texture.size() == sizeof(glm::u8vec4) * 3 ? 0 : 1;
		Error += Texture.format() == gli::FORMAT_RGBA8_UINT ? 0 : 1;
		Error += Texture.levels() == 2 ? 0 : 1;
		Error += !Texture.empty() ? 0 : 1;
		Error += Texture.dimensions() == static_cast<gli::dim1_t>(2) ? 0 : 1;

		return Error;
	}
}//namespace

namespace tex_access
{
	int run()
	{
		int Error(0);

		{
			gli::texture1D Texture(gli::FORMAT_RGBA8_UINT, gli::texture1D::dim_type(2), 2);
			assert(!Texture.empty());

			gli::image Image0 = Texture[0];
			gli::image Image1 = Texture[1];

			std::size_t Size0 = Image0.size();
			std::size_t Size1 = Image1.size();

			Error += Size0 == sizeof(glm::u8vec4) * 2 ? 0 : 1;
			Error += Size1 == sizeof(glm::u8vec4) * 1 ? 0 : 1;

			*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
			*Image1.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

			glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
			glm::u8vec4 * PointerB = Image1.data<glm::u8vec4>();

			glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
			glm::u8vec4 * Pointer1 = Texture.data<glm::u8vec4>() + 2;

			Error += PointerA == Pointer0 ? 0 : 1;
			Error += PointerB == Pointer1 ? 0 : 1;

			glm::u8vec4 ColorA = *Image0.data<glm::u8vec4>();
			glm::u8vec4 ColorB = *Image1.data<glm::u8vec4>();

			glm::u8vec4 Color0 = *Pointer0;
			glm::u8vec4 Color1 = *Pointer1;

			Error += ColorA == Color0 ? 0 : 1;
			Error += ColorB == Color1 ? 0 : 1;

			Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
			Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
		}

		{
			gli::texture1D Texture(gli::FORMAT_RGBA8_UINT, gli::texture1D::dim_type(2), 1);

			std::size_t SizeA = Texture.size();
			Error += SizeA == sizeof(glm::u8vec4) * 2 ? 0 : 1;

			gli::image Image0 = Texture[0];

			std::size_t Size0 = Image0.size();
			Error += Size0 == sizeof(glm::u8vec4) * 2 ? 0 : 1;

			*Image0.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

			glm::u8vec4 * PointerA = Image0.data<glm::u8vec4>();
			glm::u8vec4 * Pointer0 = Texture.data<glm::u8vec4>() + 0;
			Error += PointerA == Pointer0 ? 0 : 1;

			glm::u8vec4 ColorA = *PointerA;
			glm::u8vec4 Color0 = *Pointer0;

			Error += Color0 == ColorA ? 0 : 1;
			Error += Color0 == glm::u8vec4(255, 127, 0, 255) ? 0 : 1;
		}

		return Error;
	}
}//namespace

namespace size
{
	struct test
	{
		test(
			gli::format const & Format,
			gli::texture1D::dim_type const & Dimensions,
			gli::texture1D::size_type const & Size) :
			Format(Format),
			Dimensions(Dimensions),
			Size(Size)
		{}

		gli::format Format;
		gli::texture1D::dim_type Dimensions;
		gli::texture1D::size_type Size;
	};

	int run()
	{
		int Error(0);

		std::vector<test> Tests;
		Tests.push_back(test(gli::FORMAT_RGBA8_UINT, gli::texture1D::dim_type(4), 16));
		Tests.push_back(test(gli::FORMAT_R8_UINT, gli::texture1D::dim_type(4), 4));

		for(std::size_t i = 0; i < Tests.size(); ++i)
		{
			gli::texture1D Texture(
				Tests[i].Format,
				gli::texture1D::dim_type(4),
				1);

			gli::image Image = Texture[0];

			Error += Image.size() == Tests[i].Size ? 0 : 1;
			Error += Texture.size() == Tests[i].Size ? 0 : 1;
			assert(!Error);
		}

		return Error;
	}
}//namespace size

namespace load_store
{
	template <typename genType>
	int run(gli::format Format, std::array<genType, 8> const & TestSamples)
	{
		int Error = 0;

		gli::texture1D::dim_type const Dimensions(16);

		gli::texture1D TextureA(Format, Dimensions);
		TextureA.clear();
		for (std::size_t i = 0, n = 8; i < n; ++i)
			*(TextureA.data<genType>(0, 0, 1) + i) = TestSamples[i];

		gli::texture1D TextureB(Format, Dimensions);
		TextureB.clear();
		for (std::size_t i = 0, n = 8; i < n; ++i)
			TextureB.store(gli::texture1D::dim_type(i), 1, TestSamples[i]);

		std::array<genType, 16> LoadedSamplesA;
		for (std::size_t i = 0, n = 8; i < n; ++i)
			LoadedSamplesA[i] = TextureA.load<genType>(gli::texture1D::dim_type(i), 1);

		std::array<genType, 16> LoadedSamplesB;
		for (std::size_t i = 0, n = 8; i < n; ++i)
			LoadedSamplesB[i] = TextureB.load<genType>(gli::texture1D::dim_type(i), 1);

		for (std::size_t i = 0, n = 8; i < n; ++i)
			Error += LoadedSamplesA[i] == TestSamples[i] ? 0 : 1;

		for (std::size_t i = 0, n = 8; i < n; ++i)
			Error += LoadedSamplesB[i] == TestSamples[i] ? 0 : 1;

		Error += TextureA == TextureB ? 0 : 1;

		gli::texture1D TextureC(TextureA, 1, 1);
		gli::texture1D TextureD(TextureB, 1, 1);

		Error += TextureC == TextureD ? 0 : 1;

		return Error;
	}

	int test()
	{
		int Error = 0;

		{
			std::array<glm::f32vec1, 8> TestSamples{
			{
				glm::f32vec1(0.0f),
				glm::f32vec1(1.0f),
				glm::f32vec1(-1.0f),
				glm::f32vec1(0.5f),
				glm::f32vec1(-0.5f),
				glm::f32vec1(0.2f),
				glm::f32vec1(-0.2f),
				glm::f32vec1(0.9f)
			}};

			Error += run(gli::FORMAT_R32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec2, 8> TestSamples{
			{
				glm::f32vec2(-1.0f,-1.0f),
				glm::f32vec2(-0.5f,-0.5f),
				glm::f32vec2(0.0f, 0.0f),
				glm::f32vec2(0.5f, 0.5f),
				glm::f32vec2(1.0f, 1.0f),
				glm::f32vec2(-1.0f, 1.0f),
				glm::f32vec2(-0.5f, 0.5f),
				glm::f32vec2(0.0f, 0.0f)
			}};

			Error += run(gli::FORMAT_RG32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec3, 8> TestSamples{
			{
				glm::f32vec3(-1.0f, 0.0f, 1.0f),
				glm::f32vec3(-0.5f, 0.0f, 0.5f),
				glm::f32vec3(-0.2f, 0.0f, 0.2f),
				glm::f32vec3(-0.0f, 0.0f, 0.0f),
				glm::f32vec3(0.1f, 0.2f, 0.3f),
				glm::f32vec3(-0.1f,-0.2f,-0.3f),
				glm::f32vec3(0.7f, 0.8f, 0.9f),
				glm::f32vec3(-0.7f,-0.8f,-0.9f)
			}};

			Error += run(gli::FORMAT_RGB32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec4, 8> TestSamples{
			{
				glm::f32vec4(-1.0f, 0.0f, 1.0f, 1.0f),
				glm::f32vec4(-0.5f, 0.0f, 0.5f, 1.0f),
				glm::f32vec4(-0.2f, 0.0f, 0.2f, 1.0f),
				glm::f32vec4(-0.0f, 0.0f, 0.0f, 1.0f),
				glm::f32vec4(0.1f, 0.2f, 0.3f, 1.0f),
				glm::f32vec4(-0.1f,-0.2f,-0.3f, 1.0f),
				glm::f32vec4(0.7f, 0.8f, 0.9f, 1.0f),
				glm::f32vec4(-0.7f,-0.8f,-0.9f, 1.0f)
			}};

			Error += run(gli::FORMAT_RGBA32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::i8vec1, 8> TestSamples{
			{
				glm::i8vec1(-128),
				glm::i8vec1(-127),
				glm::i8vec1(127),
				glm::i8vec1(64),
				glm::i8vec1(-64),
				glm::i8vec1(1),
				glm::i8vec1(-1),
				glm::i8vec1(0)
			}};

			Error += run(gli::FORMAT_R8_SINT, TestSamples);
			Error += run(gli::FORMAT_R8_SNORM, TestSamples);
		}

		{
			std::array<glm::i8vec2, 8> TestSamples{
			{
				glm::i8vec2(-128, -96),
				glm::i8vec2( -64,  96),
				glm::i8vec2(-128,  64),
				glm::i8vec2( 127,  32),
				glm::i8vec2(   0, 126),
				glm::i8vec2( -48,  48),
				glm::i8vec2(-127, 127),
				glm::i8vec2(  64,   0)
			}};

			Error += run(gli::FORMAT_RG8_UINT, TestSamples);
			Error += run(gli::FORMAT_RG8_UNORM, TestSamples);
		}

		{
			std::array<glm::i8vec3, 8> TestSamples{
			{
				glm::i8vec3(-128,   0,   0),
				glm::i8vec3(-128, 127,   0),
				glm::i8vec3(-128, -96,   0),
				glm::i8vec3(127,-128,   0),
				glm::i8vec3(0, 127,   0),
				glm::i8vec3(0, 127,-127),
				glm::i8vec3(0,  64, -64),
				glm::i8vec3(-32,  32,  96)
			}};

			Error += run(gli::FORMAT_RGB8_SINT, TestSamples);
			Error += run(gli::FORMAT_RGB8_SNORM, TestSamples);
		}

		{
			std::array<glm::i8vec4, 8> TestSamples{
			{
				glm::i8vec4(-127,   0,   0, 127),
				glm::i8vec4(-128,  96,   0,-128),
				glm::i8vec4(127,  64,   0,   1),
				glm::i8vec4(0, -64,   0,   2),
				glm::i8vec4(-95,  32,   0,   3),
				glm::i8vec4(95, -32, 127,   4),
				glm::i8vec4(-63,  16,-128,  -1),
				glm::i8vec4(63, -16,-127,  -2)
			}};

			Error += run(gli::FORMAT_RGBA8_SINT, TestSamples);
			Error += run(gli::FORMAT_RGBA8_SNORM, TestSamples);
		}

		{
			std::array<glm::u8vec1, 8> TestSamples{
			{
				glm::u8vec1(255),
				glm::u8vec1(224),
				glm::u8vec1(192),
				glm::u8vec1(128),
				glm::u8vec1(64),
				glm::u8vec1(32),
				glm::u8vec1(16),
				glm::u8vec1(0)
			}};

			Error += run(gli::FORMAT_R8_UINT, TestSamples);
			Error += run(gli::FORMAT_R8_UNORM, TestSamples);
			Error += run(gli::FORMAT_R8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec2, 8> TestSamples{
			{
				glm::u8vec2(255,   0),
				glm::u8vec2(255, 128),
				glm::u8vec2(255, 255),
				glm::u8vec2(128, 255),
				glm::u8vec2(0, 255),
				glm::u8vec2(0, 255),
				glm::u8vec2(0,   0),
				glm::u8vec2(255,   0)
			}};

			Error += run(gli::FORMAT_RG8_UINT, TestSamples);
			Error += run(gli::FORMAT_RG8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RG8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec3, 8> TestSamples{
			{
				glm::u8vec3(255,   0,   0),
				glm::u8vec3(255, 128,   0),
				glm::u8vec3(255, 255,   0),
				glm::u8vec3(128, 255,   0),
				glm::u8vec3(0, 255,   0),
				glm::u8vec3(0, 255, 255),
				glm::u8vec3(0,   0, 255),
				glm::u8vec3(255,   0, 255)
			}};

			Error += run(gli::FORMAT_RGB8_UINT, TestSamples);
			Error += run(gli::FORMAT_RGB8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RGB8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec4, 8> TestSamples{
			{
				glm::u8vec4(255,   0,   0, 255),
				glm::u8vec4(255, 128,   0, 255),
				glm::u8vec4(255, 255,   0, 255),
				glm::u8vec4(128, 255,   0, 255),
				glm::u8vec4(0, 255,   0, 255),
				glm::u8vec4(0, 255, 255, 255),
				glm::u8vec4(0,   0, 255, 255),
				glm::u8vec4(255,   0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGBA8_UINT, TestSamples);
			Error += run(gli::FORMAT_RGBA8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RGBA8_SRGB, TestSamples);
		}

		{
			std::array<glm::u16vec1, 8> TestSamples{
			{
				glm::u16vec1(65535),
				glm::u16vec1(32767),
				glm::u16vec1(192),
				glm::u16vec1(128),
				glm::u16vec1(64),
				glm::u16vec1(32),
				glm::u16vec1(16),
				glm::u16vec1(0)
			}};

			Error += run(gli::FORMAT_R16_UINT, TestSamples);
			Error += run(gli::FORMAT_R16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec2, 8> TestSamples{
			{
				glm::u16vec2(255,   0),
				glm::u16vec2(255, 128),
				glm::u16vec2(255, 255),
				glm::u16vec2(128, 255),
				glm::u16vec2(0, 255),
				glm::u16vec2(0, 255),
				glm::u16vec2(0,   0),
				glm::u16vec2(255,   0)
			}};

			Error += run(gli::FORMAT_RG16_UINT, TestSamples);
			Error += run(gli::FORMAT_RG16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec3, 8> TestSamples{
			{
				glm::u16vec3(255,   0,   0),
				glm::u16vec3(255, 128,   0),
				glm::u16vec3(255, 255,   0),
				glm::u16vec3(128, 255,   0),
				glm::u16vec3(0, 255,   0),
				glm::u16vec3(0, 255, 255),
				glm::u16vec3(0,   0, 255),
				glm::u16vec3(255,   0, 255)
			}};

			Error += run(gli::FORMAT_RGB16_UINT, TestSamples);
			Error += run(gli::FORMAT_RGB16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec4, 8> TestSamples{
			{
				glm::u16vec4(255,   0,   0, 255),
				glm::u16vec4(255, 128,   0, 255),
				glm::u16vec4(255, 255,   0, 255),
				glm::u16vec4(128, 255,   0, 255),
				glm::u16vec4(0, 255,   0, 255),
				glm::u16vec4(0, 255, 255, 255),
				glm::u16vec4(0,   0, 255, 255),
				glm::u16vec4(255,   0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGBA16_UINT, TestSamples);
			Error += run(gli::FORMAT_RGBA16_UNORM, TestSamples);
		}

		{
			std::array<glm::u32vec1, 8> TestSamples{
			{
				glm::u32vec1(65535),
				glm::u32vec1(32767),
				glm::u32vec1(192),
				glm::u32vec1(128),
				glm::u32vec1(64),
				glm::u32vec1(32),
				glm::u32vec1(16),
				glm::u32vec1(0)
			}};

			Error += run(gli::FORMAT_R32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec2, 8> TestSamples{
			{
				glm::u32vec2(255,   0),
				glm::u32vec2(255, 128),
				glm::u32vec2(255, 255),
				glm::u32vec2(128, 255),
				glm::u32vec2(0, 255),
				glm::u32vec2(0, 255),
				glm::u32vec2(0,   0),
				glm::u32vec2(255,   0)
			}};

			Error += run(gli::FORMAT_RG32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec3, 8> TestSamples{
			{
				glm::u32vec3(255,   0,   0),
				glm::u32vec3(255, 128,   0),
				glm::u32vec3(255, 255,   0),
				glm::u32vec3(128, 255,   0),
				glm::u32vec3(0, 255,   0),
				glm::u32vec3(0, 255, 255),
				glm::u32vec3(0,   0, 255),
				glm::u32vec3(255,   0, 255)
			}};

			Error += run(gli::FORMAT_RGB32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec4, 8> TestSamples{
			{
				glm::u32vec4(255,   0,   0, 255),
				glm::u32vec4(255, 128,   0, 255),
				glm::u32vec4(255, 255,   0, 255),
				glm::u32vec4(128, 255,   0, 255),
				glm::u32vec4(0, 255,   0, 255),
				glm::u32vec4(0, 255, 255, 255),
				glm::u32vec4(0,   0, 255, 255),
				glm::u32vec4(255,   0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGBA32_UINT, TestSamples);
		}

		return Error;
	}
}//namespace load_store

int main()
{
	int Error(0);

	Error += test_alloc();
	Error += size::run();
	Error += query::run();
	Error += clear::run();
	Error += tex_access::run();
	Error += load_store::test();

	return Error;
}

