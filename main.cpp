#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "GameEngine.h"
#include "Logging.h"
#include "GameFactory.h"
#include "GameManagerSystem.h"
#include "WindowsConsole.h"

// Wraps the message loop code.
int Run();

bool GameRunning() 
{
	return true;
}

// Windows equivalant to main()
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR pCmdLine, int nShowCmd)
{
	Window * window = new Window(hInstance, nShowCmd, 800.0f, 600.0f);
	GameEngine gameEngine;
	gameEngine.AddSystem(window);
	gameEngine.AddSystem(new Renderer(window));
#ifdef DEBUG
	 gameEngine.AddSystem(new WindowsConsole());
#endif // DEBUG

	gameEngine.AddSystem(new GameFactory());
	gameEngine.AddSystem(new GameManagerSystem());// it need to move the character 
	gameEngine.AddSystem(new InputSystem()); // process the message in its update
	gameEngine.AddSystem(new PhysicsSystem());
	gameEngine.AddSystem(new WindowsConsole());
	
	gameEngine.Initialize();
	gameEngine.GameLoop();
	gameEngine.ShutDown();
		
	//return (int)msg.wParam;
	return 0;
}
