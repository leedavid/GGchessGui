#include "stdafx.h"
#include "chess.h"
#include "preGen.h"

uint64 Zobrist[BPAWN+1][256], ZobColour;


void init_zobrist(void) {
    int i, j;

    for(i = 0; i < BPAWN+1; i++){
        for(j = 0; j < 256; j++){
            Zobrist[i][j] = genrand_int64();
        }
    }
    //ZobEP[0] = 0ULL;
    //for(i=1; i<64; i++) ZobEP[i] = genrand_int64();
    //for(i=0; i<16; i++) ZobCastle[i] = genrand_int64();
    ZobColour = genrand_int64();
}

//得到当前局面的hash
uint64 compute_hash_key(const position_t *pos) {
    uint64 result = 0ULL;
    //int side;
    int sq;

    //int num = 0;

    //for(side = WHITE; side <= BLACK; side++) 
    //    for(sq=KingSquare(pos, side); sq!=PieceListEnd; sq=NextPiece(pos, sq)) 
    //        if(sq <= H8) result ^= ZOBRIST(pos->b256[sq], sq);
    //result ^= ZOB_EP(pos->ep_square);
    //result ^= ZOB_CASTLE(pos->castle_flags);
    //if(pos->side == BLACK) result ^= ZobColour;

    //for(side = WHITE; side <= BLACK; side++){
        for(sq = PieceListStart(pos,RPAWN); sq != PieceListEnd; sq = NextPiece(pos,sq)){
            if(inBoard(sq)){
                result ^= ZOBRIST(pos->b256[sq],sq);
                
                //num ++;
            }
        }

        for(sq = PieceListStart(pos,BPAWN); sq != PieceListEnd; sq = NextPiece(pos,sq)){
            if(inBoard(sq)){
                result ^= ZOBRIST(pos->b256[sq],sq);

                //num ++;
            }
        }
    //}

    if(pos->side == BLACK) result ^= ZobColour;

    return result;
}


#ifdef USE_PAWN_HASH 
//得到当前局面的兵士相将hash
hashkey_t compute_phash_key(const position_t *pos) {

    hashkey_t result = 0ULL;
    //int side;
    int sq;

    //int num = 0;

    //for(side = WHITE; side <= BLACK; side++) {
    //    for(sq = PawnListStart(pos, side); sq <= H8; sq = NextPiece(pos, sq)){
    //        result ^= ZOBRIST(pos->b256[sq], sq);
    //    }
    //}

    for(sq = PieceListStart(pos,RPAWN); sq != PieceListEnd; sq = NextPiece(pos,sq)){
        if(inBoard(sq) && PawnShiXiangKing14(pos->b256[sq])){
            result ^= ZOBRIST(pos->b256[sq],sq);

            //num ++;
        }
    }

    for(sq = PieceListStart(pos,BPAWN); sq != PieceListEnd; sq = NextPiece(pos,sq)){
        if(inBoard(sq) && PawnShiXiangKing14(pos->b256[sq])){
            result ^= ZOBRIST(pos->b256[sq],sq);

            //num ++;
        }
    }
    return result;
}
#endif

//ZobEP[64], ZobCastle[16];