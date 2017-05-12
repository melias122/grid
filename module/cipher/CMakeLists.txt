list(APPEND cipher_src
    Monoalphabetic.cpp
)

add_library(libCipher ${cipher_src})
