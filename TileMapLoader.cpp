#include "DXUT.h"
#include "TileMapLoader.h"
#include <fstream>

#include "Tile.h"
#include "Mesh.h"

TileMapLoader::TileMapLoader()
{
	tileMap = new vector<TileInfo*>();
	meshTypeContainer = new vector<pair<Mesh*, float>>();
}

TileMapLoader::~TileMapLoader()
{
	for each (auto iter in *tileMap)
	{
		SAFE_DELETE(iter);
	}

	tileMap->clear();
	meshTypeContainer->clear();

	SAFE_DELETE(tileMap);
	SAFE_DELETE(meshTypeContainer);
}

void TileMapLoader::LoadFromFile(const string& path)
{
	Parse(path);
}

void TileMapLoader::Spawn(GameObject* baseTileMap)
{
	if (baseTileMap->transform == nullptr)
		throw std::exception("baseTileMap->transform is nullptr");

	for (auto tile : *tileMap)
	{
		if (tile->rotation < 0 ||
			tile->tileNumber < 0 ||
			tile->x < 0 ||
			tile->y < 0)
			continue;

		auto mesh_info = meshTypeContainer->at(tile->tileNumber);

		if (mesh_info.first != nullptr)
		{
			Vector3 pos = Vector3((float)tile->x * tileWidth - (float)mapWidthIndex * tileWidth * 0.5f,
				0,
				(float)tile->y * tileHeight - (float)mapHeightIndex * tileHeight * 0.5f);

			Tile& t = *Instance(Tile);

			t.SetMesh(mesh_info.first)
				.SetShader(shader)
				.SetPosition(pos)
				.SetRotation(Vector3(0, tile->rotation, 0))
				.SetCollider(tileWidth, mesh_info.second, tileHeight);

			baseTileMap->transform->AddChild(t.transform);
		}
	}
}

float TileMapLoader::GetWidth()
{
	return mapWidthIndex * tileWidth;
}

float TileMapLoader::GetHeight()
{
	return mapHeightIndex * tileHeight;
}

bool TileMapLoader::ParseLine(ifstream& stream)
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

		info->rotation = rot;

		if (info->y > mapHeightIndex)
			mapHeightIndex = info->y;
		
		if (info->x > mapWidthIndex)
			mapWidthIndex = info->x;

		tileMap->push_back(info);
	}
	else if (0 == strcmp(line, "mesh"))
	{
		string path;
		float height = 0;
		stream >> path >> height;

		auto mesh = RESOURCE.Load<Mesh>(path, path);

		meshTypeContainer->push_back(make_pair(mesh, height));
	}
	else if (0 == strcmp(line, "tile_size"))
	{
		stream >> tileWidth >> tileHeight;
	}

	stream.ignore(1000, '\n');

	return true;
}

void TileMapLoader::Parse(const string& fileName)
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
