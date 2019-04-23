#ifndef PCH_H
#define PCH_H

void FatalError(const char* file, int line, const char* message);
void FatalError(const char* file, int line, const char* message, const char* context);

#define FATALERROR(m) FatalError( __FILE__, __LINE__, m )
#define ERRORMESSAGE(m,c) FatalError( __FILE__, __LINE__, m, c )
#define CHECKCL(r) CheckCL( r, __FILE__, __LINE__ )

#endif //PCH_H
