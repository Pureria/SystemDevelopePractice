#include	"GameApp.h"

int WINAPI _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.pApplication = new CGameApp();
	Info.WindowCreateInfo.Width = 1920;
	Info.WindowCreateInfo.Height = 1080;
	Info.GraphicsCreateInfo.bWindowed = FALSE;//起動時にフルスクリーン*/
	if ( pFrame->Initialize(&Info) )
	{
		pFrame->Run();
	}
	MOF_SAFE_DELETE(pFrame);
	return 0;
}