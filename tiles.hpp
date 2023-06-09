#include "imgui.h"

class Tiles
{
	ImVec2 windowpos;
	ImVec2 windowsize;
	ImVec2 grids;
	ImVec2 curpos;
	ImVec2 cursize;
	float spacing = 5.0f;
	float thick = 0.0f;
	float curve = 0.0f;
public:
	Tiles();
	Tiles(ImVec2 _windowpos, ImVec2 _windowsize, ImVec2 _grids = ImVec2(1, 1), float _spacing = 5.0f, float _sick = 0.0f, float _curve = 0.0f);
	void addTile(char* str_id, ImVec2 tilepos, ImVec2 tilesize, ImU32 color);
	void endTile();
	void setSpacing();
	ImVec2 curPos();
	ImVec2 curSize();
	ImVec2 curThick() { return { thick, thick }; }
	ImVec2 curCurve() { return { curve, curve }; }
};