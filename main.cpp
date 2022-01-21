#include "raylib.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

struct vector2 {
	float x;
	float y;
};

class Body {
	public:
		float mass;
		float x;
		float y;
		float xvel;
		float yvel;
};

vector2 grav(Body body1, Body body2, int i, int j) {

	int distx = body1.x - body2.x;
	int disty = body1.y - body2.y;

	float g = 1;
	float s = 1;

        struct vector2 gravforce;

	if(distx <= 1 || disty <= 1) {
		gravforce.x = 0;
		gravforce.y = 0;
		return gravforce;
	};


	cout << "\n\nXDist:\n" << distx << "\nYDist:\n" << disty;

	gravforce.x = (g / distx);

	gravforce.y = (g / disty);

	//cout << "\n\nXForce:\n" << gravforce.x << "\nYForce:\n" << gravforce.y;

        return gravforce;
};

int main(void)
{

	const int screenWidth = 1000;
	const int screenHeight = 800;
	const int n = 100;
	const int velmult = 3;
	int i;
	int j;
	int t = 0;

	Body bodies[n];

	for(i=0;i<(n-1);i++) {

		srand(i);

		Body body;

		body.x = (int)rand() % screenWidth;
		body.y = (int)rand() % screenHeight;
		body.mass = 3;

		body.yvel = 0;
		body.xvel = 0;

		bodies[i] = body;
	}

	InitWindow(screenWidth, screenHeight, "N-Body Sim");

	SetTargetFPS(30);

	Body body;

	while (!WindowShouldClose())
	{
		int fps = GetFPS();

		t+=1;

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(TextFormat("NBody Sim | n = %d | fps = %d | O(n^2) | t = %d | Complexity: %d", n, fps, t, (n * n)), 10, 10, 30, RED);

		for(i = 0; i < n; i++)
		{
			body = bodies[i];
			//bodies[i].xvel = 0;
			//bodies[i].yvel = 0;

			for (j = 0; j < n; j++) {

				if(i != j) {
					struct vector2 force;
					force = grav(bodies[i], bodies[j], i, j);
					bodies[i].xvel += force.x;
					bodies[i].yvel += force.y;

				}
			}

			bodies[i].x += body.xvel;
			bodies[i].y += body.yvel;

			//DrawPixel(body.x, body.y, WHITE);
			DrawCircle(body.x, body.y, 1, WHITE);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
