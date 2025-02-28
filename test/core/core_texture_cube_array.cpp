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
/// @file gli/core/texture_cube_array.cpp
/// @date 2011-01-10 / 2013-11-25
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

	std::vector<gli::textureCubeArray::dim_type::value_type> Sizes;
	Sizes.push_back(16);
	Sizes.push_back(32);
	Sizes.push_back(15);
	Sizes.push_back(17);
	Sizes.push_back(1);

	for(std::size_t FormatIndex = 0; FormatIndex < Formats.size(); ++FormatIndex)
	for(std::size_t SizeIndex = 0; SizeIndex < Sizes.size(); ++SizeIndex)
	{
		gli::textureCubeArray::dim_type Size(Sizes[SizeIndex]);

		gli::textureCubeArray TextureA(Formats[FormatIndex], Size, 2, gli::levels(Size));
		gli::textureCubeArray TextureB(Formats[FormatIndex], Size, 2);

		Error += TextureA == TextureB ? 0 : 1;
	}

	return Error;
}

int test_textureCubeArray_query()
{
	int Error(0);

	{
		gli::textureCubeArray Texture(gli::FORMAT_RGBA8_UINT, gli::textureCubeArray::dim_type(2), 1);

		Error += Texture.size() == sizeof(glm::u8vec4) * 5 * 6 ? 0 : 1;
		Error += Texture.format() == gli::FORMAT_RGBA8_UINT ? 0 : 1;
		Error += Texture.levels() == 2 ? 0 : 1;
		Error += !Texture.empty() ? 0 : 1;
		Error += Texture.dimensions().x == 2 ? 0 : 1;
		Error += Texture.dimensions().y == 2 ? 0 : 1;
	}

	{
		gli::textureCubeArray Texture(gli::FORMAT_RGBA8_UINT, gli::textureCubeArray::dim_type(2), 4);

		Error += Texture.size() == sizeof(glm::u8vec4) * 5 * 6 * 4 ? 0 : 1;
		Error += Texture.format() == gli::FORMAT_RGBA8_UINT ? 0 : 1;
		Error += Texture.levels() == 2 ? 0 : 1;
		Error += !Texture.empty() ? 0 : 1;
		Error += Texture.dimensions().x == 2 ? 0 : 1;
		Error += Texture.dimensions().y == 2 ? 0 : 1;
	}

	return Error;
}

int test_textureCubeArray_textureCube_access()
{
	int Error(0);

	{
		gli::textureCubeArray TextureCubeArray(gli::FORMAT_RGBA8_UINT, gli::textureCubeArray::dim_type(2), 2, 1);
		assert(!TextureCubeArray.empty());

		std::vector<glm::u8vec4> Colors;
		Colors.push_back(glm::u8vec4(255,   0,   0, 255));
		Colors.push_back(glm::u8vec4(  0,   0, 255, 255));

		gli::textureCube TextureCube = TextureCubeArray[1];
		glm::u8vec4* PointerA = TextureCube.data<glm::u8vec4>();
		glm::u8vec4* PointerB = TextureCubeArray.data<glm::u8vec4>() + TextureCube.size() / sizeof(glm::u8vec4);
		Error += PointerA == PointerB ? 0 : 1;
	}

	{
		gli::textureCube TextureCube(gli::FORMAT_RGBA8_UINT, gli::textureCube::dim_type(2), 2);
		assert(!TextureCube.empty());

		gli::texture2D TextureA = TextureCube[0];
		gli::texture2D TextureB = TextureCube[1];
		
		std::size_t Size0 = TextureA.size();
		std::size_t Size1 = TextureB.size();

		Error += Size0 == sizeof(glm::u8vec4) * 5 ? 0 : 1;
		Error += Size1 == sizeof(glm::u8vec4) * 5 ? 0 : 1;

		*TextureA.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);
		*TextureB.data<glm::u8vec4>() = glm::u8vec4(0, 127, 255, 255);

		glm::u8vec4 * PointerA = TextureA.data<glm::u8vec4>();
		glm::u8vec4 * PointerB = TextureB.data<glm::u8vec4>();

		glm::u8vec4 * Pointer0 = TextureCube.data<glm::u8vec4>() + 0;
		glm::u8vec4 * Pointer1 = TextureCube.data<glm::u8vec4>() + 5;

		Error += PointerA == Pointer0 ? 0 : 1;
		Error += PointerB == Pointer1 ? 0 : 1;

		glm::u8vec4 ColorA = *TextureA.data<glm::u8vec4>();
		glm::u8vec4 ColorB = *TextureB.data<glm::u8vec4>();

		glm::u8vec4 Color0 = *Pointer0;
		glm::u8vec4 Color1 = *Pointer1;

		Error += ColorA == Color0 ? 0 : 1;
		Error += ColorB == Color1 ? 0 : 1;

		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color1, glm::u8vec4(0, 127, 255, 255))) ? 0 : 1;
	}

	{
		gli::textureCube TextureCube(gli::FORMAT_RGBA8_UINT, gli::textureCube::dim_type(2), 1);

		std::size_t SizeA = TextureCube.size();
		Error += SizeA == sizeof(glm::u8vec4) * 4 * 6 ? 0 : 1;

		gli::texture2D Texture2D = TextureCube[0];
		
		std::size_t Size0 = Texture2D.size();
		Error += Size0 == sizeof(glm::u8vec4) * 4 ? 0 : 1;

		*Texture2D.data<glm::u8vec4>() = glm::u8vec4(255, 127, 0, 255);

		glm::u8vec4 * PointerA = Texture2D.data<glm::u8vec4>();
		glm::u8vec4 * Pointer0 = TextureCube.data<glm::u8vec4>();
		Error += PointerA == Pointer0 ? 0 : 1;

		glm::u8vec4 ColorA = *PointerA;
		glm::u8vec4 Color0 = *Pointer0;
		Error += glm::all(glm::equal(ColorA, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
		Error += glm::all(glm::equal(Color0, glm::u8vec4(255, 127, 0, 255))) ? 0 : 1;
	}

	return Error;
}

struct test
{
	test(
		gli::format const & Format,
		gli::textureCube::dim_type const & Dimensions,
		gli::textureCube::size_type const & Size) :
		Format(Format),
		Dimensions(Dimensions),
		Size(Size)
	{}

	gli::format Format;
	gli::textureCube::dim_type Dimensions;
	gli::textureCube::size_type Size;
};

int test_textureCubeArray_textureCube_size()
{
	int Error(0);

	std::vector<test> Tests;
	Tests.push_back(test(gli::FORMAT_RGBA8_UINT, gli::textureCube::dim_type(4), 384 * 4));
	Tests.push_back(test(gli::FORMAT_R8_UINT, gli::textureCube::dim_type(4), 96 * 4));
	Tests.push_back(test(gli::FORMAT_RGBA_DXT1_UNORM, gli::textureCube::dim_type(4), 48 * 4));
	Tests.push_back(test(gli::FORMAT_RGBA_DXT1_UNORM, gli::textureCube::dim_type(2), 48 * 4));
	Tests.push_back(test(gli::FORMAT_RGBA_DXT1_UNORM, gli::textureCube::dim_type(1), 48 * 4));
	Tests.push_back(test(gli::FORMAT_RGBA_DXT5_UNORM, gli::textureCube::dim_type(4), 96 * 4));

	for(std::size_t i = 0; i < Tests.size(); ++i)
	{
		gli::textureCubeArray Texture(
			Tests[i].Format,
			gli::textureCube::dim_type(4),
			4,
			1);

		gli::textureCubeArray::size_type Size = Texture.size();
		Error += Size == Tests[i].Size ? 0 : 1;
		assert(!Error);
	}

	return Error;
}

namespace clear
{
	int run()
	{
		int Error(0);

		glm::u8vec4 const Orange(255, 127, 0, 255);

		gli::textureCubeArray Texture(
			gli::FORMAT_RGBA8_UINT,
			gli::textureCubeArray::dim_type(4),
			4,
			1);

		Texture.clear<glm::u8vec4>(Orange);

		return Error;
	}
}//namespace

namespace load
{
	int run()
	{
		int Error(0);

		glm::u8vec4 const Color[][6] =
		{
			{
				glm::u8vec4(255,   0,   0, 255),
				glm::u8vec4(255, 127,   0, 255),
				glm::u8vec4(255, 255,   0, 255),
				glm::u8vec4(  0, 255,   0, 255),
				glm::u8vec4(  0, 255, 255, 255),
				glm::u8vec4(  0,   0, 255, 255)
			},
			{
				glm::u8vec4(255, 127, 127, 255),
				glm::u8vec4(255, 191, 127, 255),
				glm::u8vec4(255, 255, 127, 255),
				glm::u8vec4(127, 255, 127, 255),
				glm::u8vec4(127, 255, 255, 255),
				glm::u8vec4(127, 127, 255, 255)
			}
		};


		gli::textureCubeArray Texture(gli::FORMAT_RGBA8_UNORM, gli::textureCubeArray::dim_type(1), 2);

		for(std::size_t Layer = 0; Layer < Texture.layers(); ++Layer)
		for(std::size_t Face = 0; Face < Texture.faces(); ++Face)
			Texture[Layer][Face].clear<glm::u8vec4>(Color[Layer][Face]);

		gli::save(Texture, "cube_rgba8_unorm.ktx");
		gli::save(Texture, "cube_rgba8_unorm.dds");

		gli::texture TextureKTX(gli::load("cube_rgba8_unorm.ktx"));
		gli::texture TextureDDS(gli::load("cube_rgba8_unorm.dds"));

		Error += TextureKTX == Texture ? 0 : 1;
		Error += TextureDDS == Texture ? 0 : 1;

		return Error;
	}
}//namespace load

namespace load_store
{
	template <typename genType>
	int run(gli::format Format, std::array<genType, 6> const & TestSamples)
	{
		int Error = 0;

		gli::textureCubeArray::dim_type const Dimensions(2, 2);
		gli::textureCubeArray::size_type const Layer(1);
		gli::textureCubeArray::size_type const Level(1);

		gli::textureCubeArray TextureA(Format, Dimensions, 3);
		TextureA.clear();
		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			*TextureA.data<genType>(Layer, FaceIndex, Level) = TestSamples[FaceIndex];

		gli::textureCubeArray TextureB(Format, Dimensions, 3);
		TextureB.clear();
		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			TextureB.store(gli::textureCube::dim_type(0, 0), Layer, FaceIndex, Level, TestSamples[FaceIndex]);

		std::array<genType, 6> LoadedSamplesA;
		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			LoadedSamplesA[FaceIndex] = TextureA.load<genType>(gli::textureCubeArray::dim_type(0), Layer, FaceIndex, Level);

		std::array<genType, 6> LoadedSamplesB;
		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			LoadedSamplesB[FaceIndex] = TextureB.load<genType>(gli::textureCubeArray::dim_type(0), Layer, FaceIndex, Level);

		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			Error += LoadedSamplesA[FaceIndex] == TestSamples[FaceIndex] ? 0 : 1;

		for (std::size_t FaceIndex = 0, FaceCount = 6; FaceIndex < FaceCount; ++FaceIndex)
			Error += LoadedSamplesB[FaceIndex] == TestSamples[FaceIndex] ? 0 : 1;

		Error += TextureA == TextureB ? 0 : 1;

		gli::textureCubeArray TextureC(TextureA, Layer, Layer, 0, 5, Level, Level);
		gli::textureCubeArray TextureD(TextureB, Layer, Layer, 0, 5, Level, Level);

		Error += TextureC == TextureD ? 0 : 1;

		return Error;
	}

	int test()
	{
		int Error = 0;

		{
			std::array<glm::f32vec1, 6> TestSamples{
			{
				glm::f32vec1(0.0f),
				glm::f32vec1(1.0f),
				glm::f32vec1(-1.0f),
				glm::f32vec1(0.5f),
				glm::f32vec1(-0.5f),
				glm::f32vec1(0.2f)
			}};

			Error += run(gli::FORMAT_R32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec2, 6> TestSamples{
			{
				glm::f32vec2(-1.0f,-1.0f),
				glm::f32vec2(-0.5f,-0.5f),
				glm::f32vec2(0.0f, 0.0f),
				glm::f32vec2(0.5f, 0.5f),
				glm::f32vec2(1.0f, 1.0f),
				glm::f32vec2(-1.0f, 1.0f)
			}};

			Error += run(gli::FORMAT_RG32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec3, 6> TestSamples{
			{
				glm::f32vec3(-1.0f, 0.0f, 1.0f),
				glm::f32vec3(-0.5f, 0.0f, 0.5f),
				glm::f32vec3(-0.2f, 0.0f, 0.2f),
				glm::f32vec3(-0.0f, 0.0f, 0.0f),
				glm::f32vec3(0.1f, 0.2f, 0.3f),
				glm::f32vec3(-0.1f,-0.2f,-0.3f)
			}};

			Error += run(gli::FORMAT_RGB32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::f32vec4, 6> TestSamples{
			{
				glm::f32vec4(-1.0f, 0.0f, 1.0f, 1.0f),
				glm::f32vec4(-0.5f, 0.0f, 0.5f, 1.0f),
				glm::f32vec4(-0.2f, 0.0f, 0.2f, 1.0f),
				glm::f32vec4(-0.0f, 0.0f, 0.0f, 1.0f),
				glm::f32vec4(0.1f, 0.2f, 0.3f, 1.0f),
				glm::f32vec4(-0.1f,-0.2f,-0.3f, 1.0f)
			}};

			Error += run(gli::FORMAT_RGBA32_SFLOAT, TestSamples);
		}

		{
			std::array<glm::i8vec1, 6> TestSamples{
			{
				glm::i8vec1(-128),
				glm::i8vec1(-127),
				glm::i8vec1(127),
				glm::i8vec1(64),
				glm::i8vec1(-64),
				glm::i8vec1(1)
			}};

			Error += run(gli::FORMAT_R8_SINT, TestSamples);
			Error += run(gli::FORMAT_R8_SNORM, TestSamples);
		}

		{
			std::array<glm::i8vec2, 6> TestSamples{
			{
				glm::i8vec2(-128, -96),
				glm::i8vec2(-64,  96),
				glm::i8vec2(-128,  64),
				glm::i8vec2(127,  32),
				glm::i8vec2(0, 126),
				glm::i8vec2(-48,  48)
			}};

			Error += run(gli::FORMAT_RG8_UINT, TestSamples);
			Error += run(gli::FORMAT_RG8_UNORM, TestSamples);
		}

		{
			std::array<glm::i8vec3, 6> TestSamples{
			{
				glm::i8vec3(-128,   0,   0),
				glm::i8vec3(-128, 127,   0),
				glm::i8vec3(-128, -96,   0),
				glm::i8vec3(127,-128,   0),
				glm::i8vec3(0, 127,   0),
				glm::i8vec3(0, 127,-127)
			}};

			Error += run(gli::FORMAT_RGB8_SINT, TestSamples);
			Error += run(gli::FORMAT_RGB8_SNORM, TestSamples);
		}

		{
			std::array<glm::i8vec4, 6> TestSamples{
			{
				glm::i8vec4(-127,   0,   0, 127),
				glm::i8vec4(-128,  96,   0,-128),
				glm::i8vec4(127,  64,   0,   1),
				glm::i8vec4(0, -64,   0,   2),
				glm::i8vec4(-95,  32,   0,   3),
				glm::i8vec4(95, -32, 127,   4)
			}};

			Error += run(gli::FORMAT_RGBA8_SINT, TestSamples);
			Error += run(gli::FORMAT_RGBA8_SNORM, TestSamples);
		}

		{
			std::array<glm::u8vec1, 6> TestSamples{
			{
				glm::u8vec1(255),
				glm::u8vec1(224),
				glm::u8vec1(192),
				glm::u8vec1(128),
				glm::u8vec1(64),
				glm::u8vec1(32)
			}};

			Error += run(gli::FORMAT_R8_UINT, TestSamples);
			Error += run(gli::FORMAT_R8_UNORM, TestSamples);
			Error += run(gli::FORMAT_R8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec2, 6> TestSamples{
			{
				glm::u8vec2(255,   0),
				glm::u8vec2(255, 128),
				glm::u8vec2(255, 255),
				glm::u8vec2(128, 255),
				glm::u8vec2(0, 255),
				glm::u8vec2(0, 255)
			}};

			Error += run(gli::FORMAT_RG8_UINT, TestSamples);
			Error += run(gli::FORMAT_RG8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RG8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec3, 6> TestSamples{
			{
				glm::u8vec3(255,   0,   0),
				glm::u8vec3(255, 128,   0),
				glm::u8vec3(255, 255,   0),
				glm::u8vec3(128, 255,   0),
				glm::u8vec3(0, 255,   0),
				glm::u8vec3(0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGB8_UINT, TestSamples);
			Error += run(gli::FORMAT_RGB8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RGB8_SRGB, TestSamples);
		}

		{
			std::array<glm::u8vec4, 6> TestSamples{
			{
				glm::u8vec4(255,   0,   0, 255),
				glm::u8vec4(255, 128,   0, 255),
				glm::u8vec4(255, 255,   0, 255),
				glm::u8vec4(128, 255,   0, 255),
				glm::u8vec4(0, 255,   0, 255),
				glm::u8vec4(0, 255, 255, 255)
			}};

			Error += run(gli::FORMAT_RGBA8_UINT, TestSamples);
			Error += run(gli::FORMAT_RGBA8_UNORM, TestSamples);
			Error += run(gli::FORMAT_RGBA8_SRGB, TestSamples);
		}

		{
			std::array<glm::u16vec1, 6> TestSamples{
			{
				glm::u16vec1(65535),
				glm::u16vec1(32767),
				glm::u16vec1(192),
				glm::u16vec1(128),
				glm::u16vec1(64),
				glm::u16vec1(32)
			}};

			Error += run(gli::FORMAT_R16_UINT, TestSamples);
			Error += run(gli::FORMAT_R16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec2, 6> TestSamples{
			{
				glm::u16vec2(255,   0),
				glm::u16vec2(255, 128),
				glm::u16vec2(255, 255),
				glm::u16vec2(128, 255),
				glm::u16vec2(0, 255),
				glm::u16vec2(0, 255)
			}};

			Error += run(gli::FORMAT_RG16_UINT, TestSamples);
			Error += run(gli::FORMAT_RG16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec3, 6> TestSamples{
			{
				glm::u16vec3(255,   0,   0),
				glm::u16vec3(255, 128,   0),
				glm::u16vec3(255, 255,   0),
				glm::u16vec3(128, 255,   0),
				glm::u16vec3(0, 255,   0),
				glm::u16vec3(0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGB16_UINT, TestSamples);
			Error += run(gli::FORMAT_RGB16_UNORM, TestSamples);
		}

		{
			std::array<glm::u16vec4, 6> TestSamples{
			{
				glm::u16vec4(255,   0,   0, 255),
				glm::u16vec4(255, 128,   0, 255),
				glm::u16vec4(255, 255,   0, 255),
				glm::u16vec4(128, 255,   0, 255),
				glm::u16vec4(0, 255,   0, 255),
				glm::u16vec4(0, 255, 255, 255)
			}};

			Error += run(gli::FORMAT_RGBA16_UINT, TestSamples);
			Error += run(gli::FORMAT_RGBA16_UNORM, TestSamples);
		}

		{
			std::array<glm::u32vec1, 6> TestSamples{
			{
				glm::u32vec1(65535),
				glm::u32vec1(32767),
				glm::u32vec1(192),
				glm::u32vec1(128),
				glm::u32vec1(64),
				glm::u32vec1(32)
			}};

			Error += run(gli::FORMAT_R32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec2, 6> TestSamples{
			{
				glm::u32vec2(255,   0),
				glm::u32vec2(255, 128),
				glm::u32vec2(255, 255),
				glm::u32vec2(128, 255),
				glm::u32vec2(0, 255),
				glm::u32vec2(0, 255)
			}};

			Error += run(gli::FORMAT_RG32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec3, 6> TestSamples{
			{
				glm::u32vec3(255,   0,   0),
				glm::u32vec3(255, 128,   0),
				glm::u32vec3(255, 255,   0),
				glm::u32vec3(128, 255,   0),
				glm::u32vec3(0, 255,   0),
				glm::u32vec3(0, 255, 255)
			}};

			Error += run(gli::FORMAT_RGB32_UINT, TestSamples);
		}

		{
			std::array<glm::u32vec4, 6> TestSamples{
			{
				glm::u32vec4(255,   0,   0, 255),
				glm::u32vec4(255, 128,   0, 255),
				glm::u32vec4(255, 255,   0, 255),
				glm::u32vec4(128, 255,   0, 255),
				glm::u32vec4(0, 255,   0, 255),
				glm::u32vec4(0, 255, 255, 255)
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
	Error += test_textureCubeArray_textureCube_size();
	Error += test_textureCubeArray_query();
	Error += test_textureCubeArray_textureCube_access();
	Error += clear::run();
	Error += load::run();
	Error += load_store::test();

	return Error;
}

