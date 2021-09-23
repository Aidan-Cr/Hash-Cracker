//include librarys
#include <iostream>

#include "cryptopp/cryptlib.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

//include files
#include "cryptopp/md5.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"
#include "Hash.h"

using namespace std;
using namespace CryptoPP;
using namespace Weak1;

void HashTask::run() {

    HexEncoder encoder(new FileSink(std::cout));
    std::string digest;

    //hash input into MD5
    Weak1::MD5 hash;
    hash.Update((const byte*)line.data(), line.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);

    //compare hashs'
    if (Correct_password == digest) {
        //If found then output and set flag
        cout << line << '\n';
        cout << "Password found" << '\n';
        mx.lock();
        done = true;
        Correct_password = line;
        mx.unlock();
    }
}