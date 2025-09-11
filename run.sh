SCRIPT_DIR=$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")
DYLD_INSERT_LIBRARIES=$SCRIPT_DIR/build/libseculib.dylib $SCRIPT_DIR/build/secufile