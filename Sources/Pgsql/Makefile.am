lib_LTLIBRARIES = libclan24Pgsql.la

libclan24Pgsql_la_SOURCES = \
precomp.cpp \
pgsql_connection.cpp \
pgsql_connection_provider.cpp \
pgsql_command_provider.cpp \
pgsql_reader_provider.cpp \
pgsql_transaction_provider.cpp

libclan24Pgsql_la_LIBADD = -lpq

libclan24Pgsql_la_LDFLAGS = \
  -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) $(LDFLAGS_LT_RELEASE) \
  $(extra_LIBS_Pgsql)

libclan24Sound_la_CXXFLAGS=$(Pgsql_CXXFLAGS) $(extra_CFLAGS_Pgsql)

# EOF #
