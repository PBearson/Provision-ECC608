cmake_minimum_required(VERSION 3.5)

file(GLOB lib_c lib/*.c)
file(GLOB basic_c lib/basic/*.c)
file(GLOB hal_c lib/hal/*.c)
file(GLOB atcacert_c lib/atcacert/*.c)
file(GLOB crypto_c lib/crypto/*.c)
file(GLOB hashes_c lib/crypto/hashes/*.c)

set(
	srcs
	${lib_c}
	${basic_c}
	${hal_c}
	${atcacert_c}
	${crypto_c}
	${hashes_c})
set(
	dirs
	"lib")

set(
	priv_dirs
	"lib/basic"
	"lib/hal"
	"lib/crypto"
	"lib/crypto/hashes"
	"lib/atcacert")

idf_component_register(
	SRCS "${srcs}"
	INCLUDE_DIRS "${dirs}"
	PRIV_INCLUDE_DIRS "${priv_dirs}")

target_compile_options(
	${COMPONENT_LIB} PRIVATE -DESP32 -DATCA_HAL_I2C -DATCA_PRINTF)
