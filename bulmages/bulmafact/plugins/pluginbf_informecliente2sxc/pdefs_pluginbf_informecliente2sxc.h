#ifndef PDEFS_PLUGINBF_INFORMECLIENTE2SXC_H
#define PDEFS_PLUGINBF_INFORMECLIENTE2SXC_H


#ifdef Q_OS_WIN32

#ifdef PLUGINBF_INFORMECLIENTE2SXC
#define PLUGINBF_INFORMECLIENTE2SXC_EXPORT __declspec(dllexport)
#else
#define PLUGINBF_INFORMECLIENTE2SXC_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBF_INFORMECLIENTE2SXC_EXPORT

#endif


#endif

