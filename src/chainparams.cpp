// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"
#include "uint256.h"


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
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("04c5788ca1e268a7474763fa965210b6fa6b04a45f52d21056c62fb19a2de991aa15aa1d1c516f34d2a0016f51a87959c89f51a148db30c839f71bc525dde8c480");
        nDefaultPort = 12994;
        nRPCPort = 12995;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 700800; // 2 years
        nMasternodePortForkHeight = 1246400 - 1000; // ~end sep 2017
        nRewardForkHeight1 = 1246400; // ~end sep 2017
        nRewardForkHeight2 = 1275200; // ~end oct 2017

        // Genesis block
        const char* pszTimestamp = "18-03-22 - Most profitable coin";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 32 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1521784627;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 2100232723;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000801b39fbd4478decc849bcced1d8e8f283667a74586c84b3c06b4d04e11"));
        assert(genesis.hashMerkleRoot == uint256("0xdf94ef24198752cc9134ce585c4a42578d4e234d32717301eee69e9a8a815c77"));

        vSeeds.push_back(CDNSSeedData("seed1.mabtcoin.com", "seed1.mabtcoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2.mabtcoin.com", "seed2.mabtcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,4);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,28 + 128);
//        base58Prefixes[EXT_PUBLIC_KEY] = {0x02, 0xFE, 0x52, 0xF8};
//        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0xFE, 0x52, 0xCC};

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
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x02;

        vAlertPubKey = ParseHex("040d3090a194381599d0f53f89ec60b9ec77f0e7b61978ef445142c8a4f1e154ca3441a5e46e12910540352edbd8af43fc1ee1da9a935c1c252fe7426c323d3d32");

        nDefaultPort = 21994;
        nRPCPort = 21995;
        strDataDir = "testnet3";

        nMasternodePortForkHeight = 400;
        nRewardForkHeight1 = 500;
        nRewardForkHeight2 = 1000;

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1521784627;
        genesis.nNonce = 423949192;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000008f67d53fd15b2a03ff411602637bf8fc5cc1bc0cdea3839109cc28578fa"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,44);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,88 + 128);
//        base58Prefixes[EXT_PUBLIC_KEY] = new int[4] {0x3a, 0x80, 0x61, 0xa0};
//        base58Prefixes[EXT_SECRET_KEY] = new int[4] {0x3a, 0x80, 0x58, 0x37};
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
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x56;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        nDefaultPort = 18444;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        // assert(hashGenesisBlock == uint256("0x000008ca1832a4baf228eb1553c03d3a2c8e02399550dd6ea8d65cec3ef23d2e"));

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
