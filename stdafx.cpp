#include "DXUT.h"

ostream& operator<<(ostream& os, Vector2 _Val) {
	os << _Val.x << ", " << _Val.y;
	return os;
}

ostream& operator<<(ostream& os, Vector3 _Val) {
	os << _Val.x << ", " << _Val.y << ", " << _Val.z;
	return os;
}

ostream& operator<<(ostream& os, Vector4 _Val) {
	os << _Val.x << ", " << _Val.y << ", " << _Val.z << ", " << _Val.w;
	return os;
}
