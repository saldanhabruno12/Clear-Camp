#include "click.h"

bool area_clicavel(float px, float py, Retangulo r) {
	return (px > r.x1 && px < r.x2 && py > r.y1 && py < r.y2);
}