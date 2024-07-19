/**
 * @file FactoryPatternDemo.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/07/09 17:46:04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>

#include "ShapeFactory.h"

int main(int argc, char const *argv[])
{
	//获取 Circle 的对象，并调用它的 draw 方法
	Shape *shape1 = shape_factory_get_shape("CIRCLE");
	shape_draw(shape1);
	shape_destory(&shape1);

	//获取 Rectangle 的对象，并调用它的 draw 方法
	Shape *shape2 = shape_factory_get_shape("RECTANGLE");
	shape_draw(shape2);
	shape_destory(&shape2);

	//获取 Square 的对象，并调用它的 draw 方法
	Shape *shape3 = shape_factory_get_shape("SQUARE");
	shape_draw(shape3);
	shape_destory(&shape3);

	return 0;
}
