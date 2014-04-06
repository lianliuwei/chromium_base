#pragma once

#include "ui/gfx/transform.h"

int TransformX(const ui::Transform transform, int x);
int TransformX(const ui::Transform transform, double x);

int TransformReverseX(const ui::Transform transform, int x);

int TransformY(const ui::Transform transform, double y);

int TransformReverseY(const ui::Transform tranform, int y);