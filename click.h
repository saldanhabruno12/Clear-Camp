#ifndef CLICK_H
#define CLICK_H

#include <stdbool.h>

typedef struct {
	float x1, x2, y1, y2;
} Retangulo;

bool area_clicavel(float px, float py, Retangulo r);

#endif