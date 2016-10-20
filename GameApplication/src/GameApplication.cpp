#include "GameApplication.h"
#include "utils/Log.h"

GameApplication::GameApplication()
{
 	m_pWindow=nullptr;
	m_WindowWidth=640;
	m_WindowHeight=480;
	m_WindowCreationFlags=SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
  CREATELOG("log.txt");
}

GameApplication::~GameApplication()
{
  CLOSELOG();
	Destroy();
}

void GameApplication::CreateWindow(const std::string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags)
{
  LOG(INFO,"Window Created %s Width -%d Height -%d",windowTitle.c_str(),width,height);
	//Create a window
	m_pWindow = SDL_CreateWindow(
		windowTitle.c_str(),             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		width,                        // width, in pixels
		height,                        // height, in pixels
		windowFlags           // flags
		);

		m_WindowWidth=width;
		m_WindowHeight=height;
}

void GameApplication::ParseConfig(int args,char * arg[])
{
  std::stringstream ss;
  //parse config file
  XMLOptionsParser xmlParser=XMLOptionsParser("settings.xml");
  xmlParser.parse(m_options);
  ss<<m_options;
  LOG(INFO,"Settings Parsed\n%s",ss.str().c_str());
  ss.str( std::string());
  ss.clear();
	//parse command line arguments into keyvalue pairs, this should
	//overide options in config files
  CommandLineParser commandLineParser=CommandLineParser(args,arg);
  commandLineParser.parse(m_options);
  ss<<m_options;
  LOG(INFO,"Command Line Parsed\n%s",ss.str().c_str());
}


bool GameApplication::Init(int args, char * arg[])
{
	ParseConfig(args, arg);
	//ChangeWorkingDirectory();
	m_bIsRunning = true;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		//std::std::cout << "ERROR SDL_Init " << SDL_GetError() << std::std::endl;
		LOG(ERROR, "SDL can't be initialised %s", SDL_GetError());
		return false;
	}

	//Initialise SDL Image
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags) {
		LOG(ERROR, "SDL Image Can't be Initialised %s", IMG_GetError());
		return false;
	}

	//Initialise SDL TTF
	if (TTF_Init() == -1) {
		LOG(ERROR, "SDL TTF Can't be Initialised %s", TTF_GetError());
		return false;
	}
	m_WindowWidth = m_options.getOptionAsInt("WindowWidth");
	m_WindowHeight = m_options.getOptionAsInt("WindowHeight");
	
	//creating window
	CreateWindow(m_options.getOption("WindowTitle"), m_WindowWidth, m_WindowHeight, m_WindowCreationFlags);
	//creating OPENGL window context and binding it to the window
	InitGraphics();

	//Init Scene
	InitScene();
	return true;
}

bool GameApplication::InitGraphics()
{
	//OpenGl Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	m_GLcontext = SDL_GL_CreateContext(m_pWindow);

	//GLEW
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		LOG(ERROR, "Error: %s", glewGetErrorString(err));
		return false;
	}

	//OpenGL States
	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to use
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	SetViewport((int)m_WindowWidth, (int)m_WindowHeight);

	return true;
}

//Function to set/reset viewport
void GameApplication::SetViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;

	//make sure height is always above 1
	if (height == 0) {
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	////Change to projection matrix mode
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	////Calculate perspective matrix, using gLM
	//glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), ratio,
	//	0.1f, 100.0f);
	//glLoadMatrixf(&projectionMatrix[0][0]);

	////Switch to ModelView
	//glMatrixMode(GL_MODELVIEW);

	////Reset using the Identity Matrix
	//glLoadIdentity();
}


void GameApplication::InitScene()
{
}

void GameApplication::DestroyScene()
{
}

void GameApplication::Update()
{

}

void GameApplication::OnBeginRender()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameApplication::OnEndRender()
{
	SDL_GL_SwapWindow(m_pWindow);
}

void GameApplication::Render()
{
	////Switch to ModelView
	//glMatrixMode(GL_MODELVIEW);
	////Reset using the Identity Matrix
	//glLoadIdentity();
	////Translate to -5.0f on z-axis
	//glTranslatef(0.0f, 0.0f, -5.0f);
	////Begin drawing triangles
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f); //Colour of the vertices
	//glVertex3f(0.0f, 1.0f, 0.0f); // Top
	//glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
	//glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
	//glEnd();
}

void GameApplication::OnRenderGUI()
{

}

void GameApplication::Destroy()
{
	// clean up, reverse order!!!
	DestroyScene();
	SDL_GL_DeleteContext(m_GLcontext);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameApplication::Run()
{
	SDL_Event event;
	//Game Loop
	while (m_bIsRunning)
	{
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {
			//Get event type
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
						m_bIsRunning = false;
					break;

					case SDL_WINDOWEVENT_MINIMIZED:
						LOG(INFO, "window minimised");
					break;

					case SDL_WINDOWEVENT_MAXIMIZED:
						LOG(INFO, "window maximised");
						SetViewport(event.window.data1, event.window.data2);
					break;

					case SDL_WINDOWEVENT_RESTORED:
						LOG(INFO, "window restored from tray");
						SetViewport(event.window.data1, event.window.data2);
					break;

					case SDL_WINDOWEVENT_RESIZED:
						LOG(INFO, "window resized to: %d x %d", event.window.data1, event.window.data2);
						SetViewport(event.window.data1, event.window.data2);
					break;

					case SDL_WINDOWEVENT_SIZE_CHANGED:
						SDL_Log("Window %d size changed to %dx%d", event.window.windowID, event.window.data1, event.window.data2);
						SetViewport(event.window.data1, event.window.data2);
					break;
				}
			}
			else switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE:
							m_bIsRunning = false;
						break;

						case SDL_SCANCODE_F4:
							if (m_isFullScreen)
							{
								//we get our previous dimensions for the window
								SDL_SetWindowFullscreen(m_pWindow, 0);
								SDL_SetWindowSize(m_pWindow, m_WindowWidth, m_WindowHeight);
								SetViewport(m_WindowWidth, m_WindowHeight);
							}
							else
							{
								//we need to get the native desktop resolution and scale/resize the window
								SDL_DisplayMode current;
								SDL_GetDesktopDisplayMode(0, &current);
								SDL_SetWindowSize(m_pWindow, current.w, current.h);
								SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
								SetViewport(current.w, current.h);
							}

							m_isFullScreen = !m_isFullScreen;
						break;
					}

				break;

				case SDL_QUIT:
					m_bIsRunning = false;
				break;
			}
		}
		//init Scene
		Update();
		//render
		OnBeginRender();
		Render();
		OnEndRender();
		//Call swap so that our GL back buffer is displayed

	}
}
