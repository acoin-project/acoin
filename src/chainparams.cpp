// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0x05;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("0498288f9bc78ea9d9aeb73a7c5136538af11d24533826af034e6ee1728cc683e5e0927a0e395a84a5f1a53c53c45c2d1e3a12ac944e9b2303683cf7c085bbc1e5");
        nDefaultPort = 17883;
        nRPCPort = 8832;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 388800;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "170814-DN Egypt-China and Israel present alternatives to Suez Canal";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 1 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("043e5fd19808f21e14e195e5bd6cbf884d31d29816de6f4649d8c258a5cc01bbd5c853d56bb99e427c1bdc3690ef3cb268c855caebecfb813ec63bfe2b8afd6") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = TimeGenesisMain;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 2090606798;

        hashGenesisBlock = genesis.GetHash();
        
        // debug
        /*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }
        printf("MAIN: %s\n", hashGenesisBlock.ToString().c_str());
        printf("MAIN: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
            genesis.GetHash().ToString().c_str(),
            genesis.nVersion,
            genesis.hashPrevBlock.ToString().c_str(),
            genesis.hashMerkleRoot.ToString().c_str(),
            genesis.nTime, genesis.nBits, genesis.nNonce,
            genesis.vtx.size());
        */
        
        assert(hashGenesisBlock == HashGenesisMain);
        assert(genesis.hashMerkleRoot == uint256("0x01fe7bbb147e50de0dfa5b1ab6fc395f48faabecdb2a4e85a1a0207f21735a63"));

        vSeeds.push_back(CDNSSeedData("seed1.a-coin.info", "seed1.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed2.a-coin.info", "seed2.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed3.a-coin.info", "seed3.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed4.a-coin.info", "seed4.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed5.a-coin.info", "seed5.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed6.a-coin.info", "seed6.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed7.a-coin.info", "seed7.a-coin.info"));
        vSeeds.push_back(CDNSSeedData("seed8.a-coin.info", "seed8.a-coin.info"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(23);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(10);
        base58Prefixes[SECRET_KEY]     = list_of(230);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x0d;
        vAlertPubKey = ParseHex("04008f443ff94075f465b35a58705da4b8884a910916b2906be8092a762e4a496555d0abe51b8cea8196a1b7521eeb017ad9aebf281954d5e75d93ae7c0a7faa6a");
        nDefaultPort = 27883;
        nRPCPort = 18832;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = TimeGenesisTest;
        genesis.nNonce = 415697184;
        
        hashGenesisBlock = genesis.GetHash();
        
        // debug
        /*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }
        printf("TEST: %s\n", hashGenesisBlock.ToString().c_str());
        printf("TEST: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
            genesis.GetHash().ToString().c_str(),
            genesis.nVersion,
            genesis.hashPrevBlock.ToString().c_str(),
            genesis.hashMerkleRoot.ToString().c_str(),
            genesis.nTime, genesis.nBits, genesis.nNonce,
            genesis.vtx.size());
        */
        
        assert(hashGenesisBlock == HashGenesisTest);

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(87);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(187);
        base58Prefixes[SECRET_KEY]     = list_of(238);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        // assert(hashGenesisBlock == uint256("0x13d8d31dde96874006da503dd2b63fa68c698dc823334359e417aa3a92f80433"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
