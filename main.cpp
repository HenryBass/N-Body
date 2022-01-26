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

		float x;
		float y;
		float xvel;
		float yvel;
};

vector2 grav(Body body1, Body body2, int i, int j) {

	float distx = (body1.x - body2.x);
	float disty = (body1.y - body2.y);

	float g = -1;

        struct vector2 gravforce;

	if((distx <= 1 && distx >= -1) || (disty <= 1 && disty >= -1)) {
		gravforce.x = 0;
		gravforce.y = 0;
		return gravforce;
	};


	gravforce.x = g * (1 / distx);

	gravforce.y = g * (1 / disty);

        return gravforce;
};

int main(void)
{

	int n;
	int scale;
	int seed;

	cout << "Bodies (n): ";
	cin >> n;

	cout << "Scale Factor: ";
	cin >> scale;

	cout << "Random Seed: ";
	cin >> seed;

	const int screenWidth = 1200;
	const int screenHeight = 800;

	int i;
	int j;
	int t = 0;

	Body bodies[n];

	for(i=0;i<(n-1);i++) {

		srand(i + seed);

		Body body;

		body.x = (int)rand() % (screenWidth * scale);
		body.y = (int)rand() % (screenHeight * scale);

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

			DrawCircle(body.x / (scale), body.y / (scale), 1, WHITE);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
