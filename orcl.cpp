//orcl     

//#include "stdafx.h"    
#include "crypto++/dll.h"    
#include "crypto++/default.h"    
#include "crypto++/osrng.h"    
using CryptoPP::AutoSeededRandomPool;    

#include <iostream>    
#include <string>    
#include "crypto++/cryptlib.h"    
using CryptoPP::Exception;        

#include "crypto++/hex.h"    
using CryptoPP::HexEncoder;    
using CryptoPP::HexDecoder;        

#include "crypto++/filters.h"    
using CryptoPP::StringSink;    
using CryptoPP::StringSource;    
using CryptoPP::StreamTransformationFilter;        

#include "crypto++/aes.h"    
using CryptoPP::AES;       

#include "crypto++/ccm.h"    
using CryptoPP::CBC_Mode;       

//#include "assert.h"        
using namespace std;
int main()    
{    
     unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                   0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                   0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                   0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    unsigned char iv[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   // assert(sizeof(key) == 32);  // AES256 key size
    //assert(sizeof(iv) == 16);   // IV is always the AES block size       

    string plain = "CBC Mode Test";    
    string cipher, encoded, recovered;       

    // Pretty print key    
    encoded.clear();    
    StringSource( key, sizeof(key), true,    
                  new HexEncoder(new StringSink( encoded )) // HexEncoder    
    ); // StringSource

    cout << "key: " << encoded << endl;        

    // Pretty print iv    
    encoded.clear();

    StringSource( iv, sizeof(iv), true,    
        new HexEncoder(new StringSink( encoded )) // HexEncoder    
    ); // StringSource

    cout << "iv: " << encoded << endl;       

    /*********************************\
    \*********************************/

    try    
    {    
        cout << "plain text: " << plain << endl;            
        CBC_Mode< AES >::Encryption e;    
        e.SetKeyWithIV( key, sizeof(key), iv );     

        // The StreamTransformationFilter adds padding    
        //  as required. ECB and CBC Mode must be padded    
        //  to the block size of the cipher.    
        StringSource( plain, true,     
            new StreamTransformationFilter( e,    
                new StringSink( cipher )    
            ) // StreamTransformationFilter          
        ); // StringSource    
    }    
    catch( CryptoPP::Exception& e )    
    {    
        cerr << "Caught Exception..." << endl;    
        cerr << e.what() << endl;    
        cerr << endl;    
    }    

    /*********************************\    
    \*********************************/    

    // Pretty print    
    encoded.clear();    
    StringSource( cipher, true,    
        new HexEncoder(    
            new StringSink( encoded )    
        ) // HexEncoder    
    ); // StringSource    
    cout << "cipher text: " << encoded << endl;    

    /*********************************\    
    \*********************************/    

    try    
    {    
        CBC_Mode< AES >::Decryption d;    
        d.SetKeyWithIV( key, sizeof(key), iv );    

        // The StreamTransformationFilter removes    
        //  padding as required.    
        StringSource s( cipher, true,     
            new StreamTransformationFilter( d,    
                new StringSink( recovered )    
            ) // StreamTransformationFilter    
        ); // StringSource    

        cout << "recovered text: " << recovered << endl;    
    }    
    catch( /*CryptoPP::*/Exception& e )    
    {    
        cerr << "Caught Exception..." << endl;    
        cerr << e.what() << endl;    
        cerr << endl;    
    }    

    /*********************************\    
    \*********************************/    

    assert( plain == recovered );    

    return 0;    
}
