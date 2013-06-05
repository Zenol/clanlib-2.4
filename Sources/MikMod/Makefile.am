lib_LTLIBRARIES = libclan24MikMod.la

libclan24MikMod_la_SOURCES =  \
 module_reader.cpp          \
 resourcetype_module.h      \
 module_reader.h	    \
 setupmikmod.cpp            \
 soundprovider_mikmod.cpp   \
 soundprovider_mikmod_session.cpp

libclan24MikMod_la_LIBADD = -lmikmod

libclan24MikMod_la_LDFLAGS = \
  -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) $(LDFLAGS_LT_RELEASE) \
  $(extra_LIBS_MikMod)

libclan24Sound_la_CXXFLAGS=$(MikMod_CXXFLAGS) $(extra_CFLAGS_MikMod)

# EOF #
