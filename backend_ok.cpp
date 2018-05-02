#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

//int
//PosFlags(int index){
//	/* Fake up flags for now, as we aren't keeping track of castling
//	availability yet */
//	//int flags = F_ALL_CASTLE_OK;
//	int flags = 0;
//	if ((index % 2) == 0){
//		flags |= F_WHITE_ON_MOVE;				//当前是白棋要走
//	}
//	switch (DIS.GGQJ.variant) {
//		case VariantSuicide:
//		case VariantGiveaway:
//			flags |= F_IGNORE_CHECK;
//			flags &= ~F_ALL_CASTLE_OK;
//			break;
//		case VariantAtomic:
//			flags |= F_IGNORE_CHECK | F_ATOMIC_CAPTURE;
//			break;
//		case VariantKriegspiel:
//			flags |= F_KRIEGSPIEL_CAPTURE;
//			break;
//		case VariantNoCastle:
//			flags &= ~F_ALL_CASTLE_OK;
//			break;
//		default:
//			break;
//	}
//	return flags;
//}

