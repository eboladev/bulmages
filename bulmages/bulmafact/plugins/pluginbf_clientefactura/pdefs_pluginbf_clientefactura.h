#ifndef PDEFS_PLUGINBF_CLIENTEFACTURA_H
#define PDEFS_PLUGINBF_CLIENTEFACTURA_H


#ifdef WIN32

#ifdef PLUGINBF_CLIENTEFACTURA
#define PLUGINBF_CLIENTEFACTURA_EXPORT __declspec(dllexport)
#else
#define PLUGINBF_CLIENTEFACTURA_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBF_CLIENTEFACTURA_EXPORT

#endif


#endif
