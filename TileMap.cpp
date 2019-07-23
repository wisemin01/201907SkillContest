#include "DXUT.h"
#include "TileMap.h"
#include <fstream>

void TileMapRenderer::LoadFromFile(const string& path)
{
	Parse(path);

	for (auto iter : tileMap)
	{
		for (int i = 0; i < tileMapWidth; i++)
		{
			auto tile = iter[i];

			switch (tile.tileNumber)
			{
			case 0:
				printf("A");

				break;

			case 1:
				printf("B");

				break;

			case 2:
				printf("C");

				break;
			}
		}

		printf("\n");
	}
}

void TileMapRenderer::Init()
{
}

void TileMapRenderer::Update()
{
	for (auto iter : tileMap)
	{
		SAFE_DELETE_ARRAY(iter);
	}

	tileMap.clear();
}

void TileMapRenderer::Destroy()
{
}

void TileMapRenderer::Render()
{
	for (auto width_line : tileMap)
	{
		for (int i = 0; i < tileMapWidth; i++)
		{
			auto tile = width_line[i];

			auto mesh = meshTypeContainer[tile.tileNumber];

			if (mesh != nullptr)
			{
				Matrix world = Matrix::Translation(tile.x * tileWidth, tile.y * tileHeight, 0);
				world *= Matrix::RotationY(tile.rotation);

				world *= gameObject->transform->World;

				CustomRender(mesh, shader, world);
			}
		}
	}
}

bool TileMapRenderer::ParseLine(ifstream& stream)
{
	char line[256] = { 0 };

	stream >> line;

	if (!stream)
		return false;

	if (0 == strcmp(line, "#"))
	{
		return true;
	}
	else if (0 == strcmp(line, "size"))
	{
		int width, height;

		stream >> width >> height;

		tileMap.resize(height, new TileInfo[width]());

		tileMapWidth = width;
		tileMapHeight = height;
	}
	else if (0 == strcmp(line, "tile"))
	{
		TileInfo info;

		stream >> info.x >> info.y >> info.rotation >> info.tileNumber;

		tileMap[info.y][info.x] = info;
	}
	else if (0 == strcmp(line, "tile_width"))
	{
		stream >> tileWidth;
	}
	else if (0 == strcmp(line, "tile_height"))
	{
		stream >> tileHeight;
	}

	stream.ignore(1000, '\n');

	return true;
}

void TileMapRenderer::Parse(const string& fileName)
{
	ifstream InFile(fileName);

	if (!InFile)
		throw exception("wifstream::open");

	while (true)
	{
		if (ParseLine(InFile) == false)
			break;
	}
}
