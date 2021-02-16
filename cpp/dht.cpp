//main.cpp

#include <iostream>
#include <vector>
#include <sstream> //for ostringstream
#include <iomanip> //for setw, hex, and setfill
#include <openssl/evp.h> //for all other OpenSSL function calls
#include <openssl/sha.h> //for SHA224_DIGEST_LENGTH
using namespace std;
string bytes_to_dec_string(const vector<uint8_t>& bytes)
{
    ostringstream stream;
    for (uint8_t b : bytes)
    {
        stream << setw(2) << setfill('0') << dec << static_cast<int>(b);
    }
    return stream.str();
}

//perform the SHA3-224 hash
string sha3_224(const string& input)
{
    uint32_t digest_length = SHA224_DIGEST_LENGTH;
    const EVP_MD* algorithm = EVP_sha3_224();
    uint8_t* digest = static_cast<uint8_t*>(OPENSSL_malloc(digest_length));
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, input.c_str(), input.size());
    EVP_DigestFinal_ex(context, digest, &digest_length);
    EVP_MD_CTX_destroy(context);
    string output = bytes_to_dec_string(vector<uint8_t>(digest, digest + digest_length));
    OPENSSL_free(digest);
    return output;
}

string dht(vector<string> servers, string key)
{
    const string dec = sha3_224(key);
    const char *num = dec.c_str();
    int remainder = 0;
    for (int i = 0; dec[i] != '\0'; ++i) {
        remainder = (remainder * 10 + dec[i] - '0') % servers.size();
    }
    return servers[remainder];
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "USAGE: dht <key>" << endl;
        return 1;
    }
    vector<string> servers;
    servers.push_back("alpha");
    servers.push_back("beta");
    servers.push_back("gamma");
    const string key(argv[1]);
    printf("%s\n", dht(servers, key).c_str());

    return 0;
}
