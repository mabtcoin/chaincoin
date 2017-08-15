include Makefile.include

AM_CPPFLAGS += -I$(builddir)

noinst_LIBRARIES = \
  libchaincoin_server.a \
  libchaincoin_common.a \
  libchaincoin_cli.a
if ENABLE_WALLET
noinst_LIBRARIES += libchaincoin_wallet.a
endif

bin_PROGRAMS =

if BUILD_BITCOIND
  bin_PROGRAMS += chaincoind
endif

if BUILD_BITCOIN_CLI
  bin_PROGRAMS += chaincoin-cli
endif

SUBDIRS = . $(BUILD_QT) $(BUILD_TEST)
DIST_SUBDIRS = . qt test
.PHONY: FORCE
# chaincoin core #
BITCOIN_CORE_H = \
  activemasternode.h \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bignum.h \
  bloom.h \
  chainparams.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  core.h \
  crypter.h \
  darksend.h \
  darksend-relay.h \
  db.h \
  hash.h \
  init.h \
  instantx.h \
  key.h \
  keepass.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  masternode.h \
  masternode-pos.h \
  masternodeman.h \
  masternodeconfig.h \
  miner.h \
  mruset.h \
  netbase.h \
  net.h \
  noui.h \
  protocol.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script/script.h \
  serialize.h \
  crypto/sph_blake.h \
  crypto/sph_bmw.h \
  crypto/sph_cubehash.h \
  crypto/sph_echo.h \
  crypto/sph_groestl.h \
  crypto/sph_jh.h \
  crypto/sph_keccak.h \
  crypto/sph_luffa.h \
  crypto/sph_shavite.h \
  crypto/sph_simd.h \
  crypto/sph_skein.h \
  crypto/sph_types.h \
  spork.h \
  sync.h \
  threadsafety.h \
  tinyformat.h \
  compat/byteswap.h \
  compat/endian.h \
  torcontrol.h \
  crypto/hmac_sha256.h \
  crypto/sha256.h \
  common.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  walletdb.h \
  wallet.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
version.o: obj/build.h

libchaincoin_server_a_SOURCES = \
  activemasternode.cpp \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  checkpoints.cpp \
  coins.cpp \
  init.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  rpcblockchain.cpp \
  rpcdarksend.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  txdb.cpp \
  txmempool.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

libchaincoin_wallet_a_SOURCES = \
  activemasternode.cpp \
  db.cpp \
  crypter.cpp \
  rpcdump.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  walletdb.cpp \
  keepass.cpp \
  $(BITCOIN_CORE_H)

libchaincoin_common_a_SOURCES = \
  activemasternode.cpp \
  base58.cpp \
  allocators.cpp \
  chainparams.cpp \
  core.cpp \
  darksend.cpp \
  darksend-relay.cpp \
  masternode.cpp \
  masternode-pos.cpp \
  masternodeman.cpp \
  masternodeconfig.cpp \
  torcontrol.cpp \
  crypto/hmac_sha256.cpp \
  crypto/sha256.cpp \
  instantx.cpp \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpcprotocol.cpp \
  script/script.cpp \
  sync.cpp \
  util.cpp \
  random.cpp \
  version.cpp \
  crypto/aes_helper.c \
  crypto/luffa.c \
  crypto/groestl.c \
  crypto/jh.c \
  crypto/echo.c \
  crypto/shavite.c \
  crypto/keccak.c \
  crypto/skein.c \
  spork.cpp \
  crypto/bmw.c \
  crypto/simd.c \
  crypto/cubehash.c \
  crypto/blake.c \
  $(BITCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libchaincoin_common_a_SOURCES += compat/glibc_compat.cpp
libchaincoin_common_a_SOURCES += compat/glibcxx_compat.cpp
endif

libchaincoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BITCOIN_CORE_H)

nodist_libchaincoin_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# chaincoind binary #
chaincoind_LDADD = \
  libchaincoin_server.a \
  libchaincoin_cli.a \
  libchaincoin_common.a \
  $(LIBLEVELDB) \
  $(LIBMEMENV)
if ENABLE_WALLET
chaincoind_LDADD += libchaincoin_wallet.a
endif
chaincoind_SOURCES = chaincoind.cpp
#

if TARGET_WINDOWS
chaincoind_SOURCES += chaincoind-res.rc
endif

AM_CPPFLAGS += $(BDB_CPPFLAGS)
chaincoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# chaincoin-cli binary #
chaincoin_cli_LDADD = \
  libchaincoin_cli.a \
  libchaincoin_common.a \
  $(BOOST_LIBS)
chaincoin_cli_SOURCES = chaincoin-cli.cpp
#

if TARGET_WINDOWS
chaincoin_cli_SOURCES += chaincoin-cli-res.rc
endif

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
leveldb/libleveldb.a: leveldb/libmemenv.a

leveldb/%.a:
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
	  OPT="$(CXXFLAGS) $(CPPFLAGS)"

qt/chaincoinstrings.cpp: $(libchaincoin_server_a_SOURCES) $(libchaincoin_common_a_SOURCES) $(libchaincoin_cli_a_SOURCES)
	@test -n $(XGETTEXT) || echo "xgettext is required for updating translations"
	@cd $(top_srcdir); XGETTEXT=$(XGETTEXT) share/qt/extract_strings_qt.py

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb Makefile.include

clean-local:
	-$(MAKE) -C leveldb clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
