#ifndef _GAMEAPPLICATION_H
#define _GAMEAPPLICATION_H

#include "Common.h"
#include "Shader.h"
#include "Texture.h"
#include "CommandLineParser.h"
#include "XMLOptionsParser.h"
#include "ProgramOptions.h"
#include "utils/NonCopyable.h"
#include "GameObject.h"

/**
*
*
*/

class GameApplication:public NonCopyable
{
public:
	GameApplication();
	virtual ~GameApplication();

	virtual bool Init(int args,char * arg[]);
	virtual bool InitGraphics();
	virtual void InitScene();
	virtual void DestroyScene();
	virtual void Update();
	virtual void OnBeginRender();
	virtual void Render();
	virtual void OnRenderGUI();
	virtual void OnEndRender();
	virtual void Destroy();
	void Run();
	void CreateWindow(const std::string& windowTitle,const unsigned int width, const unsigned int height, const unsigned int windowFlags=0);
	void SetViewport(int width, int height);

protected:
	SDL_Window* m_pWindow;
	SDL_GLContext m_GLcontext;
	bool m_bIsRunning;
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;
	unsigned int m_WindowCreationFlags;
	bool m_isFullScreen = false;
	ProgramOptions m_options;
	void ParseConfig(int args,char * arg[]);
};
#endif
