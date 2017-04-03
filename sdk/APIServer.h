#ifndef __APISERVER_H__
#	define __APISERVER_H__

EXTERN_C namespace API
{
	class Server
	{
	public:
		DLL_PUBLIC_I static void PrintMessage(const std::wstring  message);
	};
}
#endif
