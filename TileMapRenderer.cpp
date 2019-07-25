#include "DXUT.h"
#include "TileMapRenderer.h"
#include <fstream>

TileMapRenderer& TileMapRenderer::LoadFromFile(const string& path)
{
	Parse(path);
	return *this;
}

void TileMapRenderer::Init()
{
	__super::Init();

	tileMap = new vector<TileInfo*>();
	meshTypeContainer = new vector<Mesh*>();
}

void TileMapRenderer::Update()
{

}

void TileMapRenderer::Destroy()
{
	for each (auto iter in *tileMap)
	{
		SAFE_DELETE(iter);
	}

	tileMap->clear();
	meshTypeContainer->clear();

	SAFE_DELETE(tileMap);
	SAFE_DELETE(meshTypeContainer);

	__super::Destroy();
}

void TileMapRenderer::Render()
{
	for (auto tile : *tileMap)
	{
		if (tile->rotation < 0 ||
			tile->tileNumber < 0 ||
			tile->x < 0 ||
			tile->y < 0)
			continue;

		mesh = meshTypeContainer->at(tile->tileNumber);

		if (mesh != nullptr)
		{
			Matrix world;

			Matrix R = Matrix::RotationY(tile->rotation);
			Matrix T = Matrix::Translation(
				(float)tile->x * tileWidth - (float)mapWidthIndex * tileWidth * 0.5f,
				0,
				(float)tile->y * tileHeight - (float)mapHeightIndex * tileHeight * 0.5f);

			world = R * T;
			world = world * gameObject->transform->World;

			if (shader == nullptr)
				NormalRender(world);
			else
				ShaderRender(world);
		}
	}
}

float TileMapRenderer::GetWidth()
{
	return mapWidthIndex * tileWidth;
}

float TileMapRenderer::GetHeight()
{
	return mapHeightIndex * tileHeight;
}

bool TileMapRenderer::ParseLine(ifstream& stream)
{
	char line[256] = { 0 };

	stream >> line;

	if (!stream)
		return false;

	if (0 == strcmp(line, "#"))
	{

	}
	else if (0 == strcmp(line, "size"))
	{
		int width, height;

		stream >> width >> height;

		tileMap->reserve(width * height + 1);
	}
	else if (0 == strcmp(line, "tile"))
	{
		TileInfo* info = new TileInfo();

		int rot;

		stream >> info->x >> info->y >> rot >> info->tileNumber;

		info->rotation = D3DXToRadian(rot);

		if (info->y > mapHeightIndex)
			mapHeightIndex = info->y;
		
		if (info->x > mapWidthIndex)
			mapWidthIndex = info->x;

		tileMap->push_back(info);
	}
	else if (0 == strcmp(line, "mesh"))
	{
		string path;
		stream >> path;

		auto mesh = RESOURCE.Load<Mesh>(path, path);

		meshTypeContainer->push_back(mesh);
	}
	else if (0 == strcmp(line, "tile_size"))
	{
		stream >> tileWidth >> tileHeight;
	}

	stream.ignore(1000, '\n');

	return true;
}

void TileMapRenderer::Parse(const string& fileName)
{
	ifstream InFile(fileName);

	if (!InFile)
		throw exception("ifstream::open - error");

	while (true)
	{
		if (ParseLine(InFile) == false)
			break;
	}

	InFile.close();
}
