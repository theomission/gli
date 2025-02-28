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
/// @file gli/core/save_kmg.inl
/// @date 2015-08-05 / 2015-08-05
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <glm/gtc/round.hpp>
#include "../load_kmg.hpp"
#include "../filter.hpp"

namespace gli
{
	inline bool save_kmg(texture const & Texture, std::vector<char> & Memory)
	{
		if(Texture.empty())
			return false;

		Memory.resize(sizeof(detail::FOURCC_KMG100) + sizeof(detail::kmgHeader10) + Texture.size());

		std::memcpy(&Memory[0], detail::FOURCC_KMG100, sizeof(detail::FOURCC_KMG100));

		std::size_t Offset = sizeof(detail::FOURCC_KMG100);

		texture::swizzles_type Swizzle = Texture.swizzles();

		detail::kmgHeader10 & Header = *reinterpret_cast<detail::kmgHeader10*>(&Memory[0] + Offset);
		Header.Endianness = 0x04030201;
		Header.Format = Texture.format();
		Header.Target = Texture.target();
		Header.SwizzleRed = Swizzle[0];
		Header.SwizzleGreen = Swizzle[1];
		Header.SwizzleBlue = Swizzle[2];
		Header.SwizzleAlpha = Swizzle[3];
		Header.PixelWidth = static_cast<std::uint32_t>(Texture.dimensions().x);
		Header.PixelHeight = static_cast<std::uint32_t>(Texture.dimensions().y);
		Header.PixelDepth = static_cast<std::uint32_t>(Texture.dimensions().z);
		Header.Layers = static_cast<std::uint32_t>(Texture.layers());
		Header.Levels = static_cast<std::uint32_t>(Texture.levels());
		Header.Faces = static_cast<std::uint32_t>(Texture.faces());
		Header.GenerateMipmaps = FILTER_NONE;
		Header.BaseLevel = static_cast<std::uint32_t>(Texture.base_level());
		Header.MaxLevel = static_cast<std::uint32_t>(Texture.max_level());

		Offset += sizeof(detail::kmgHeader10);

		for(std::size_t Layer = 0, Layers = Texture.layers(); Layer < Layers; ++Layer)
		for(std::size_t Level = 0, Levels = Texture.levels(); Level < Levels; ++Level)
		{
			std::uint32_t const FaceSize = static_cast<std::uint32_t>(Texture.size(Level));
			for(std::size_t Face = 0, Faces = Texture.faces(); Face < Faces; ++Face)
			{
				std::memcpy(&Memory[0] + Offset, Texture.data(Layer, Face, Level), FaceSize);

				Offset += FaceSize;
				assert(Offset <= Memory.size());
			}
		}

		return true;
	}

	inline bool save_kmg(texture const & Texture, char const * Filename)
	{
		if(Texture.empty())
			return false;

		FILE* File = std::fopen(Filename, "wb");
		if(!File)
			return false;

		std::vector<char> Memory;
		bool const Result = save_kmg(Texture, Memory);

		std::fwrite(&Memory[0], 1, Memory.size(), File);
		std::fclose(File);

		return Result;
	}

	inline bool save_kmg(texture const & Texture, std::string const & Filename)
	{
		return save_kmg(Texture, Filename.c_str());
	}
}//namespace gli
